//
//  GPBERPC.h
//  ProtobufExt
//
//  Created by Dan Kalinin on 7/26/18.
//  Copyright © 2018 Dan Kalinin. All rights reserved.
//

#import "GPBEMain.h"

@class GPBERPCI;
@class GPBERPCO;
@class GPBERPC;

@protocol GPBERPCIDelegate;
@protocol GPBERPCODelegate;
@protocol GPBERPCDelegate;










@protocol GPBERPCIDelegate <NSERPCIDelegate>

@optional
- (void)gpbeRPCIDidUpdateState:(GPBERPCI *)rpcI;
- (void)gpbeRPCIDidStart:(GPBERPCI *)rpcI;
- (void)gpbeRPCIDidCancel:(GPBERPCI *)rpcI;
- (void)gpbeRPCIDidFinish:(GPBERPCI *)rpcI;

- (void)gpbeRPCIDidUpdateProgress:(GPBERPCI *)rpcI;

@end



@interface GPBERPCI : NSERPCI <GPBERPCIDelegate>

@property (readonly) NSMutableOrderedSet<GPBERPCIDelegate> *delegates;
@property (readonly) NSEInputStreamReading *lengthReading;
@property (readonly) NSEInputStreamReading *payloadReading;

@end










@protocol GPBERPCODelegate <NSERPCODelegate>

@optional
- (void)gpbeRPCODidUpdateState:(GPBERPCO *)rpcO;
- (void)gpbeRPCODidStart:(GPBERPCO *)rpcO;
- (void)gpbeRPCODidCancel:(GPBERPCO *)rpcO;
- (void)gpbeRPCODidFinish:(GPBERPCO *)rpcO;

- (void)gpbeRPCODidUpdateProgress:(GPBERPCO *)rpcO;

@end



@interface GPBERPCO : NSERPCO <GPBERPCODelegate>

@property (readonly) NSMutableOrderedSet<GPBERPCODelegate> *delegates;
@property (readonly) NSEOutputStreamWriting *lengthWriting;
@property (readonly) NSEOutputStreamWriting *payloadWriting;

@end










@protocol GPBERPCDelegate <NSERPCDelegate, NSERPCIDelegate, GPBERPCODelegate>

@optional
- (void)gpbeRPCDidUpdateState:(GPBERPC *)rpc;
- (void)gpbeRPCDidStart:(GPBERPC *)rpc;
- (void)gpbeRPCDidCancel:(GPBERPC *)rpc;
- (void)gpbeRPCDidFinish:(GPBERPC *)rpc;

- (void)gpbeRPCDidUpdateProgress:(GPBERPC *)rpc;

@end



@interface GPBERPC : NSERPC <GPBERPCDelegate>

@property (readonly) NSMutableOrderedSet<GPBERPCDelegate> *delegates;

@end
