#import "IAPHelper.h"
#import "MBProgressHUD.h"

@interface IAPManager : IAPHelper

+(IAPManager*) shared;

-(void)purchaseItem:(int)index;

@end

