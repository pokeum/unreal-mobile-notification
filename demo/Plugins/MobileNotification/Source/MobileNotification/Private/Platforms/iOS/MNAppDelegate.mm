#import "MNAppDelegate.h"
#import "MNPlugin.h"

#import <UserNotifications/UserNotifications.h>

#import <objc/runtime.h>

typedef void (*DidReceiveRemoteNotificationMethod)(id, SEL, UIApplication *, NSDictionary *, void (^)(UIBackgroundFetchResult));

@implementation MNAppDelegate

static MNAppDelegate *MNAppDelegateInstance = nil;

static DidReceiveRemoteNotificationMethod originalDidReceiveRemoteNotification = nil;

- (id) init
{
    if (self = [super init]) { }
    return (self);
}

// NSObject 클래스의 load() 클래스 메서드는 해당 클래스가 메모리에 로드될 때 호출됩니다.
// 이러한 동작 방식으로, load()가 AppDelegate 의 application(_:didFinishLaunchingWithOptions:) 함수보다 먼저 호출된다.
+ (void) load
{
    [super load];
    if (MNAppDelegateInstance == nil)
    {
        MNAppDelegateInstance = [[MNAppDelegate alloc] init];
        [MNAppDelegateInstance registerLifeCycleListener];
        
        [MNAppDelegateInstance swizzleDidReceiveRemoteNotification];
    }
}

+ (MNAppDelegate *) getInstance
{
    return (MNAppDelegateInstance);
}

- (void) registerLifeCycleListener
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didFinishLaunching:)
                                                 name:UIApplicationDidFinishLaunchingNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didBecomeActive:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(willResignActive:)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(willTerminate:)
                                                 name:UIApplicationWillTerminateNotification
                                               object:nil];
    
}

+ (void) unregisterLifeCycleListener
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void) didFinishLaunching:(NSNotification *)notification
{
    NSLog(@"[MNAppDelegate] App did finish launching");
    
    // Configure Firebase
    [FIRApp configure];
    
    // Set the messaging delegate
    [FIRMessaging messaging].delegate = self;
    
#ifdef AUTO_REGISTER_FOR_REMOTE_NOTIFICATIONS
    // Request permission for push notifications
    [MNPlugin registerForRemoteNotifications];
#endif
}

- (void) didBecomeActive:(NSNotification *)notification {
    NSLog(@"[MNAppDelegate] App did become active");
}

- (void) willResignActive:(NSNotification *)notification {
    NSLog(@"[MNAppDelegate] App will resign active");
}

- (void) willTerminate:(NSNotification *)notification {
    NSLog(@"[MNAppDelegate] App will terminate");
}

// Monitor token refresh
- (void) messaging:(FIRMessaging *)messaging didReceiveRegistrationToken:(NSString *)token
{
    if (token != nil) {
        NSLog(@"[MNAppDelegate] FCM registration token: %@", token);
        [MNPlugin saveFirebaseToken:token];
    }
}

// Customized method for handling remote notification
- (void) application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
{
    TMap<FString, FString> Data;
    for (NSString *key in [MNPlugin getReceiveMessage:userInfo]) {
        Data.Add(FString(key), FString(userInfo[key]));
    }
    
    // Check if module is loaded
    if (MOBILE_NOTIFICATION_MODULE_POINTER)
    {
        MOBILE_NOTIFICATION_CORE_POINTER->HandleOnMessageReceived(Data);
    }
    else
    {	// If module is not loaded
        FMobileNotificationCore::UnhandledRemoteMessageData = Data;
    }
	
    // Call the original method (if it exists)
    if (originalDidReceiveRemoteNotification) {
        originalDidReceiveRemoteNotification(self, _cmd, application, userInfo, completionHandler);
    }
}

// Swizzling method to exchange implementation
- (void) swizzleDidReceiveRemoteNotification
{
    Class appDelegateClass = NSClassFromString(@"IOSAppDelegate");
    if (!appDelegateClass) {
        NSLog(@"[MNAppDelegate] IOSAppDelegate class not found!");
        return;
    }
    
    SEL selector = @selector(application:didReceiveRemoteNotification:fetchCompletionHandler:);
    
    Method originalMethod = class_getInstanceMethod(appDelegateClass, selector);
    Method swizzledMethod = class_getInstanceMethod([self class], selector);
    
    if (!swizzledMethod) { return; }
    if (!originalMethod) {
        class_addMethod(appDelegateClass,
                        selector,
                        method_getImplementation(swizzledMethod),
                        method_getTypeEncoding(swizzledMethod));
    }
    else
    {
        // Store the original method implementation
        originalDidReceiveRemoteNotification = (DidReceiveRemoteNotificationMethod) method_getImplementation(originalMethod);
        
        // Perform method exchange
        method_exchangeImplementations(originalMethod, swizzledMethod);
    }
}

@end