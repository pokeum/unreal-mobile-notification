#pragma once

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface SGToast : UIViewController

+(SGToast *)singleton;

-(void)message:(NSString *)msg duration:(float)time;

@end