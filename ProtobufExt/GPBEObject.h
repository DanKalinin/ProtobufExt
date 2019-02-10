//
//  GPBEObject.h
//  ProtobufExt
//
//  Created by Dan Kalinin on 2/10/19.
//

#import "GPBEMain.h"



@interface NSObject (GPBE)

@property (readonly) Class gpbeOperationClass;
@property (readonly) NSEObjectOperation *gpbeOperation;

@end
