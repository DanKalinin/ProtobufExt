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

@end



@interface GPBERPC : NSERPC <GPBERPCDelegate>

@end













//@class PB3RPCPayloadReading, PB3RPCPayloadWriting, PB3RPC;
//
//
//
//
//
//
//
//
//
//
//@interface PB3RPCPayloadReading : HLPRPCPayloadReading
//
//@property (readonly) HLPStreamReading *lengthReading;
//@property (readonly) HLPStreamReading *payloadReading;
//
//@end
//
//
//
//
//
//
//
//
//
//
//@interface PB3RPCPayloadWriting : HLPRPCPayloadWriting
//
//@property (readonly) HLPStreamWriting *lengthWriting;
//@property (readonly) HLPStreamWriting *payloadWriting;
//
//@end
//
//
//
//
//
//
//
//
//
//
//@interface PB3RPC : HLPRPC
//
//@end
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//@class GPBERPCReading;
//@class GPBERPCWriting;
//@class GPBERPC;
//
//
//
//
//
//
//
//
//
//
//@protocol GPBERPCReadingDelegate <NSERPCReadingDelegate>
//
//@end
//
//
//
//@interface GPBERPCReading : NSERPCReading <GPBERPCReadingDelegate>
//
//@property (readonly) NSEStreamReading *lengthReading;
//@property (readonly) NSEStreamReading *reading;
//
//@end
//
//
//
//
//
//
//
//
//
//
//@protocol GPBERPCWritingDelegate <NSERPCWritingDelegate>
//
//@end
//
//
//
//@interface GPBERPCWriting : NSERPCWriting <GPBERPCWritingDelegate>
//
//@property (readonly) NSEStreamWriting *lengthWriting;
//@property (readonly) NSEStreamWriting *writing;
//
//@end
//
//
//
//
//
//
//
//
//
//
//@protocol GPBERPCDelegate <NSERPCDelegate>
//
//@end
//
//
//
//@interface GPBERPC : NSERPC <GPBERPCDelegate>
//
//@end
