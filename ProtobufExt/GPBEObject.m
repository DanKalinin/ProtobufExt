//
//  GPBEObject.m
//  ProtobufExt
//
//  Created by Dan Kalinin on 2/10/19.
//

#import "GPBEObject.h"



@implementation NSObject (GPBE)

- (Class)gpbeOperationClass {
    return NSEObjectOperation.class;
}

- (NSEObjectOperation *)gpbeOperation {
    NSEObjectOperation *operation = [self nseOperationForKey:@selector(gpbeOperation) ofClass:self.gpbeOperationClass];
    return operation;
}

@end
