//
//  GPBEStreams.h
//  ProtobufExt
//
//  Created by Dan Kalinin on 2/10/19.
//

#import "GPBEObject.h"

@class GPBEStreams;
@class GPBEStreamsOperation;

@protocol GPBEStreamsDelegate;










@interface NSEStreams (GPBE)

@end










@interface GPBEStreams : NSEStreams

@end










@protocol GPBEStreamsDelegate <NSEStreamsDelegate>

@end



@interface GPBEStreamsOperation : NSEObjectOperation <GPBEStreamsDelegate>

@end
