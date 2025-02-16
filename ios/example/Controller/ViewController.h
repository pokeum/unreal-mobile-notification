#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, TableAction) {
    TableAction_RegisterForRemoteNotifications,
    TableAction_GetDeviceToken,
    TableAction_GetRegistrationToken,
    TableAction_DeleteToken,
    TableAction_Count // Keeps track of the total number of actions
};

@interface ViewController : UIViewController<UITableViewDelegate, UITableViewDataSource>

@property (strong, nonatomic) IBOutlet UITableView *TableView;

- (void)showDialogWithTitle: (NSString*) title
                    message: (NSString*) message;

- (void) copyToClipboard: (NSString *) text;

@end
