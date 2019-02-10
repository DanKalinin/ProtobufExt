//
//  GPBERPC.m
//  ProtobufExt
//
//  Created by Dan Kalinin on 7/26/18.
//  Copyright © 2018 Dan Kalinin. All rights reserved.
//

#import "GPBERPC.h"
#import "Payload.pbobjc.h"










@interface GPBERPCI ()

@property NSEInputStreamReading *lengthReading;
@property NSEInputStreamReading *payloadReading;

@end



@implementation GPBERPCI

@dynamic delegates;

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates gpbeRPCIDidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates gpbeRPCIDidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates gpbeRPCIDidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates gpbeRPCIDidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates gpbeRPCIDidUpdateProgress:self];
}

#pragma mark - GPBERPCIDelegate

- (void)gpbeRPCIDidStart:(GPBERPCI *)rpcI {
    self.lengthReading = [self.parent.streams.inputStream.nseOperation readDataOfLength:4 timeout:0.0];
    [self.lengthReading.delegates addObject:self];
}

#pragma mark - NSEInputStreamReadingDelegate

- (void)nseInputStreamReadingDidFinish:(NSEInputStreamReading *)reading {
    if ([reading isEqual:self.lengthReading]) {
        if (reading.error) {
            self.error = reading.error;
            [self finish];
        } else if (reading.isCancelled) {
        } else {
            uint32_t length = *(uint32_t *)reading.data.bytes;
            self.payloadReading = [self.parent.streams.inputStream.nseOperation readDataOfLength:length timeout:0.0];
            [self.payloadReading.delegates addObject:self];
        }
    } else if ([reading isEqual:self.payloadReading]) {
        if (reading.error) {
            self.error = reading.error;
            [self finish];
        } else if (reading.isCancelled) {
        } else {
            GPBEPayload *payload = [GPBEPayload parseFromData:reading.data error:nil];
            self.type = payload.type;
            self.serial = payload.serial;
            self.responseSerial = payload.responseSerial;
            if (payload.error.length > 0) {
                NSArray<NSString *> *components = [payload.error componentsSeparatedByString:@"."];
                self.responseError = [NSError errorWithDomain:components.firstObject code:components.lastObject.integerValue userInfo:nil];
            } else {
                NSString *name = [payload.message.typeURL.lastPathComponent stringByReplacingOccurrencesOfString:@"." withString:@""];
                Class class = NSClassFromString(name);
                if (self.type == NSERPCIOTypeReturn) {
                    self.response = [payload.message unpackMessageClass:class error:nil];
                } else {
                    self.message = [payload.message unpackMessageClass:class error:nil];
                }
                
                [self finish];
            }
        }
    }
}

@end










@interface GPBERPCO ()

@property NSEOutputStreamWriting *lengthWriting;
@property NSEOutputStreamWriting *payloadWriting;
@property NSMutableData *payloadData;

@end



@implementation GPBERPCO

@dynamic delegates;

- (void)updateState:(NSEOperationState)state {
    [super updateState:state];
    
    [self.delegates gpbeRPCODidUpdateState:self];
    if (state == NSEOperationStateDidStart) {
        [self.delegates gpbeRPCODidStart:self];
    } else if (state == NSEOperationStateDidCancel) {
        [self.delegates gpbeRPCODidCancel:self];
    } else if (state == NSEOperationStateDidFinish) {
        [self.delegates gpbeRPCODidFinish:self];
    }
}

- (void)updateProgress:(int64_t)completedUnitCount {
    [super updateProgress:completedUnitCount];
    
    [self.delegates gpbeRPCODidUpdateProgress:self];
}

#pragma mark - GPBERPCODelegate

- (void)gpbeRPCODidStart:(GPBERPCO *)rpcO {
    GPBEPayload *payload = GPBEPayload.message;
    payload.type = self.type;
    payload.serial = self.serial;
    payload.responseSerial = self.responseSerial;
    if (self.responseError) {
        payload.error = [NSString stringWithFormat:@"%@.%i", self.responseError.domain, (int)self.responseError.code];
    } else if (self.type == NSERPCIOTypeReturn) {
        [payload.message packWithMessage:self.response error:nil];
    } else {
        [payload.message packWithMessage:self.message error:nil];
    }
    
    NSData *payloadData = payload.data.mutableCopy;
    
    uint32_t length = (uint32_t)payloadData.length;
    NSMutableData *lengthData = [NSMutableData dataWithBytes:&length length:4];
    
    self.lengthWriting = [self.parent.streams.outputStream.nseOperation writeData:lengthData timeout:0.0];
    [self.lengthWriting.delegates addObject:self];
}

#pragma mark - NSEOutputStreamWritingDelegate

- (void)nseOutputStreamWritingDidFinish:(NSEOutputStreamWriting *)writing {
    if ([writing isEqual:self.lengthWriting]) {
        if (writing.error) {
            self.error = writing.error;
            [self finish];
        } else if (writing.isCancelled) {
        } else {
            self.payloadWriting = [self.parent.streams.outputStream.nseOperation writeData:self.payloadData timeout:0.0];
            [self.payloadWriting.delegates addObject:self];
        }
    } else if ([writing isEqual:self.payloadWriting]) {
        if (writing.error) {
            self.error = writing.error;
            [self finish];
        } else if (writing.isCancelled) {
        } else {
            [self finish];
        }
    }
}

@end










@interface GPBERPC ()

@end



@implementation GPBERPC

- (Class)iClass {
    return GPBERPCI.class;
}

- (Class)oClass {
    return GPBERPCO.class;
}

@end
