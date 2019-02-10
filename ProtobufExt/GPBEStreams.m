//
//  GPBEStreams.m
//  ProtobufExt
//
//  Created by Dan Kalinin on 2/10/19.
//

#import "GPBEStreams.h"










@implementation NSEStreams (GPBE)

@dynamic gpbeOperation;

- (Class)gpbeOperationClass {
    return GPBEStreamsOperation.class;
}

@end










@interface GPBEStreams ()

@end



@implementation GPBEStreams

@end










@interface GPBEStreamsOperation ()

@property GPBERPC *rpc;

@end



@implementation GPBEStreamsOperation

@dynamic object;

- (instancetype)initWithObject:(NSEStreams *)object {
    self = [super initWithObject:object];
    
    self.rpc = [GPBERPC.alloc initWithStreams:object];
    [self.rpc.delegates addObject:self.delegates];
    
    return self;
}

@end
