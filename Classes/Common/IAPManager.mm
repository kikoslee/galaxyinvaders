#import "IAPManager.h"
#import "DataType.h"
#import "DataSL.h"

#include "CommonHelper.h"

static NSString* sIapName[IAP_COUNT] = {
	@"com.liho.galaxyinvaders.coin1",
	@"com.liho.galaxyinvaders.coin2",
	@"com.liho.galaxyinvaders.coin3",
	@"com.liho.galaxyinvaders.coin4",
};

@implementation IAPManager

static IAPManager* _sharedManager = NULL;

+(IAPManager*)shared
{
	if(!_sharedManager)
		_sharedManager = [[IAPManager alloc] init];
	return _sharedManager;
}

- (id)init
{
	NSSet* productIdentifiers = [NSSet setWithObjects:sIapName count:IAP_COUNT];
	if ((self = [super initWithProductIdentifiers:productIdentifiers]))
	{
	}
	return self;    
}

// 购买成功
- (void)provideContent:(NSString*)productIdentifier myData:(NSData*)productData
{
	for(int i = 0; i < IAP_COUNT; i++)
	{
		if([productIdentifier isEqualToString:sIapName[i]])
		{
            hideLoadingAlert();
			SimpleAudioEngine::sharedEngine()->playEffect(EF_COIN);
            gGlobalData.gold += gIapGold[i];
            gSaveData();
			break;
		}
	}
}

// 购买失败
- (void)purchaseFailed:(NSError*)error
{
	hideLoadingAlert();
	if (error.code != SKErrorPaymentCancelled)
    {
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error!" message:error.localizedDescription delegate:nil cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
		[alert show];
        [alert release];
	}
}

- (void)purchaseItem:(int)index
{
	if([SKPaymentQueue canMakePayments])
    {
        [self buyProductIdentifier:sIapName[index]];
        showLoadingAlert("Purchasing...");
	}
    else
    {
        hideLoadingAlert();
		UIAlertView* alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"PurchaseFailed",nil)
														message:NSLocalizedString(@"PurchaseClosedMsg",nil)
													   delegate:self
											  cancelButtonTitle:@"OK"
											  otherButtonTitles:nil];
		[alert show];
		[alert release];
	}    
}

@end
