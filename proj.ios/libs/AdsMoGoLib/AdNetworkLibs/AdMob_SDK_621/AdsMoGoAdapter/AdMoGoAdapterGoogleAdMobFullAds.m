//
//  AdMoGoAdapterGoogleAdMobFullAds.m
//  TestMOGOSDKAPP
//
//  Created by 孟令之 on 12-12-3.
//
//

#import "AdMoGoAdapterGoogleAdMobFullAds.h"
#import "AdMoGoAdNetworkConfig.h"
#import "AdMoGoAdNetworkAdapter+Helpers.h"
#import "AdMoGoAdNetworkRegistry.h"
#import "AdMoGoConfigDataCenter.h"
#import "AdMoGoConfigData.h"
#import "AdMoGoDeviceInfoHelper.h"

@implementation AdMoGoAdapterGoogleAdMobFullAds
+ (AdMoGoAdNetworkType)networkType {
	return AdMoGoAdNetworkTypeAdMobFullAd;
}

+ (void)load {
	[[AdMoGoAdNetworkRegistry sharedRegistry] registerClass:self];
}

- (void)getAd{
    isStop = NO;
    
    [adMoGoCore adDidStartRequestAd];
    /*
     获取广告类型
     原来代码：AdViewType type = adMoGoView.adType;
     */
    AdMoGoConfigDataCenter *configDataCenter = [AdMoGoConfigDataCenter singleton];
    
    AdMoGoConfigData *configData = [configDataCenter.config_dict objectForKey:adMoGoCore.config_key];
    
    AdViewType type =[configData.ad_type intValue];
    
	if (type == AdViewTypeFullScreen || type==AdViewTypeiPadFullScreen) {
        interstitial = [[GADInterstitial alloc] init];
        interstitial.delegate = self;
        interstitial.adUnitID = [self.ration objectForKey:@"key"];
        GADRequest *request = [GADRequest request];
        request.testDevices = [NSArray arrayWithObjects:                               // 
                               nil];
        [interstitial loadRequest:request];
    }

}

- (void)stopBeingDelegate{
    interstitial.delegate = nil;
    if (interstitial) {
        [interstitial release];
        interstitial = nil;
    }
}

- (void)stopAd{
    isStop = YES;
    [self stopBeingDelegate];
}

- (void)dealloc{
    interstitial.delegate = nil;
    if (interstitial) {
        [interstitial release];
        interstitial = nil;
    }
    [super dealloc];
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad{
    if (isStop) {
        return;
    }
    [interstitial presentFromRootViewController:[adMoGoDelegate viewControllerForPresentingModalView]];
    [self helperNotifyDelegateOfFullScreenAdModal];
    [adMoGoCore adapter:self didReceiveAdView:nil];
}

- (void)interstitial:(GADInterstitial *)ad
didFailToReceiveAdWithError:(GADRequestError *)error{
    if (isStop) {
        return;
    }
    NSLog(@"admob's fullScreen ad is failed :%@",error);
    [adMoGoCore adapter:self didFailAd:nil];
}

- (void)interstitialWillLeaveApplication:(GADInterstitial *)ad{

}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad{
    [self helperNotifyDelegateOfFullScreenAdModalDismissal];
}

@end
