#import "SGToast.h"

@implementation SGToast

- (instancetype)init
{
    self = [super init];    
    return self;
}

+ (SGToast *)singleton
{
    static SGToast *instance;
    static dispatch_once_t once;
    dispatch_once(&once, ^ {
        instance = [[self alloc] init];
    });
    return instance;
}

-(void)message:(NSString *)msg duration:(float)time
{
    dispatch_async(dispatch_get_main_queue(), ^ {

        UIAlertController *alert = [UIAlertController alertControllerWithTitle:nil
                                                                       message:msg
                                                                preferredStyle:UIAlertControllerStyleAlert];
        UIViewController *top = [[UIApplication sharedApplication] delegate].window.rootViewController;
        [top presentViewController:alert animated:YES completion: nil];        

        dispatch_after(
            dispatch_time(DISPATCH_TIME_NOW, time *NSEC_PER_SEC), dispatch_get_main_queue(), ^ {
                [alert dismissViewControllerAnimated:YES completion:nil];
            }
        );
	});
}

@end