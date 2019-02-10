//
//  GPBEStreams.h
//  ProtobufExt
//
//  Created by Dan Kalinin on 2/10/19.
//

#import "GPBEObject.h"
#import "GPBERPC.h"

@class GPBEStreams;
@class GPBEStreamsOperation;

@protocol GPBEStreamsDelegate;










@interface NSEStreams (GPBE)

@property (readonly) GPBEStreamsOperation *gpbeOperation;

@end










@interface GPBEStreams : NSEStreams

@end










@protocol GPBEStreamsDelegate <NSEStreamsDelegate>

@end



@interface GPBEStreamsOperation : NSEObjectOperation <GPBEStreamsDelegate>

@property (readonly) GPBERPC *rpc;

@property (weak, readonly) NSEStreams *object;

@end
