#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MNPlugin : NSObject

+ (void) registerForRemoteNotifications;

+ (NSString *) getDeviceToken;

+ (NSString *) getFirebaseToken;

+ (void) retrieveFirebaseToken;

+ (void) saveFirebaseToken: (NSString *)token;

+ (void) deleteFirebaseToken;

+ (NSDictionary *) getReceiveMessage: (NSDictionary *)userInfo;

@end

NS_ASSUME_NONNULL_END
