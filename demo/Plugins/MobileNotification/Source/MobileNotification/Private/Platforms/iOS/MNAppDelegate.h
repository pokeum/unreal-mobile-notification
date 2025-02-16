#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <FirebaseCore/FirebaseCore.h>
#import <FirebaseMessaging/FirebaseMessaging.h>

NS_ASSUME_NONNULL_BEGIN

@interface MNAppDelegate : UIResponder <UIApplicationDelegate, FIRMessagingDelegate>

+ (void) unregisterLifeCycleListener;

@end

NS_ASSUME_NONNULL_END