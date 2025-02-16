#import "MNPlugin.h"

#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>

#import <FirebaseCore/FirebaseCore.h>
#import <FirebaseMessaging/FirebaseMessaging.h>

@implementation MNPlugin

static NSString * const kFirebaseToken = @"MNPLUGIN_FIREBASE_TOKEN_KEY";

+ (void) registerForRemoteNotifications
{
    // Request permission for push notifications
    UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
    [center requestAuthorizationWithOptions:(UNAuthorizationOptionAlert | UNAuthorizationOptionSound | UNAuthorizationOptionBadge)
                          completionHandler:^(BOOL granted, NSError * _Nullable error) {
        if (granted) {
            NSLog(@"[MNPlugin] Permission granted for push notifications");
            
            // Request is sent to APNs for a device token via registerForRemoteNotifications
            dispatch_async(dispatch_get_main_queue(), ^{
                [[UIApplication sharedApplication] registerForRemoteNotifications];
            });
        } else {
            NSLog(@"[MNPlugin] Permission denied for push notifications");
        }
    }];
}

+ (NSString *) getDeviceToken
{
    NSData *deviceToken = [[FIRMessaging messaging] APNSToken];
    const unsigned char *data = (const unsigned char*)([deviceToken bytes]);
    
    if (!data) { return nil; }
    
    NSMutableString *token = [NSMutableString string];
    for (NSUInteger i = 0; i < [deviceToken length]; i++) {
        [token appendFormat : @"%02.2hhX", data[i]];
    }
    
    NSLog(@"[MNPlugin] Device Token: %@", token);
    return token;
}

+ (void) setFirebaseToken: (NSString *)token
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setObject:token forKey:kFirebaseToken];
}

+ (NSString *) getFirebaseToken
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    return [defaults objectForKey:kFirebaseToken];
}

+ (void) retrieveFirebaseToken
{
    NSString *senderId = [[FIRApp defaultApp] options].GCMSenderID;
    [[FIRMessaging messaging] retrieveFCMTokenForSenderID:senderId completion:^(NSString * _Nullable token, NSError * _Nullable error) {
        if (error != nil) {
            NSLog(@"[MNPlugin] Error getting FCM registration token: %@", error);
        } else if (token != nil) {
            NSLog(@"[MNPlugin] Get FCM registration token: %@", token);
            [MNPlugin saveFirebaseToken:token];
        }
    }];
}

+ (void) saveFirebaseToken: (NSString *)token
{
    NSLog(@"[MNPlugin] Save FCM registration token: %@", token);
    
    NSString *fcmRegistrationToken = [self getFirebaseToken];
    if (fcmRegistrationToken == nil ||
        ![token isEqualToString:fcmRegistrationToken]) {
        // onNewToken
        NSLog(@"[MNPlugin] FCM registration token is refreshed!");

        // OnTokenRefresh...
    }
    [self setFirebaseToken:token];
}

+ (void) deleteFirebaseToken
{
    NSString *senderId = [[FIRApp defaultApp] options].GCMSenderID;
    [[FIRMessaging messaging] deleteFCMTokenForSenderID:senderId completion:^(NSError * _Nullable error) {
        if (error) {
            NSLog(@"[MNPlugin] Error deleting FCM registration token: %@", error);
        } else {
            NSLog(@"[MNPlugin] Successfully deleted the FCM registration token.");
            // Get new token
            [MNPlugin retrieveFirebaseToken];
        }
    }];
}

+ (NSDictionary *) getReceiveMessage: (NSDictionary *)userInfo
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    
    for (NSString *key in userInfo) {
        if ([key hasPrefix:@"gcm."] || [key hasPrefix:@"google."]) continue;
        
        id value = userInfo[key];
        if ([value isKindOfClass:[NSString class]]) {
            dict[key] = value;
        }
    }
    return [dict copy];
}

@end
