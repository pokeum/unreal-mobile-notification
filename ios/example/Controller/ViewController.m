#import "ViewController.h"
#import "../MobileNotification/MNPlugin.h"

@interface ViewController ()

@end

@implementation ViewController

- (NSString *)labelForAction:(TableAction)action {
    switch (action) {
        case TableAction_RegisterForRemoteNotifications:
            return @"Register For Remote Notifications";
        case TableAction_GetDeviceToken:
            return @"Get Device Token";
        case TableAction_GetRegistrationToken:
            return @"Get FCM Registration Token";
        case TableAction_DeleteToken:
            return @"Delete FCM Registration Token";
        default:
            return @"Unknown";
    }
}

- (void) viewDidLoad {
    [super viewDidLoad];
    
    self.TableView.dataSource = self;
    self.TableView.delegate = self;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return TableAction_Count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    TableAction action = (TableAction)indexPath.row;
    [cell textLabel].text = [self labelForAction:action];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    TableAction action = (TableAction)indexPath.row;
    
    switch (action) {
        case TableAction_RegisterForRemoteNotifications:
            [MNPlugin registerForRemoteNotifications];
            break;
        case TableAction_GetDeviceToken:
            [self showDialogWithTitle:@"Device Token"
                              message:[MNPlugin getDeviceToken]];
            break;
        case TableAction_GetRegistrationToken:
            [self showDialogWithTitle:@"Firebase Registration Token"
                              message:[MNPlugin getFirebaseToken]];
            break;
        case TableAction_DeleteToken:
            [MNPlugin deleteFirebaseToken];
            break;
        default:
            break;
    }
}

- (void)showDialogWithTitle: (NSString*) title
                    message: (NSString*) message {
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title
                                                                   message:message
                                                            preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *copyAction = [UIAlertAction actionWithTitle:@"Copy"
                                                         style:UIAlertActionStyleDefault
                                                       handler:^(UIAlertAction * _Nonnull action) { [self copyToClipboard: message]; }];
    [alert addAction:copyAction];
    
    UIAlertAction *closeAction = [UIAlertAction actionWithTitle:@"Close"
                                                          style:UIAlertActionStyleCancel
                                                        handler:nil];
    [alert addAction:closeAction];
    
    // Present the alert from the current view controller
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)copyToClipboard: (NSString *) text {
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    pasteboard.string = text;
}

@end
