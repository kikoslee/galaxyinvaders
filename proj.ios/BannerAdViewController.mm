//
//  BannerAdViewController.h
//  tapburstfree
//
//  Created by Limin on 12-9-4.
//  Copyright HappyBluefin 2012年. All rights reserved.
//

#import "BannerAdViewController.h"
#import "AppController.h"
#import "HBKeys.h"
#import "HBCommon.h"

@implementation BannerAdViewController

@synthesize adView;

- (void)dealloc {
    adView.delegate = nil;
    adView.adWebBrowswerDelegate = nil;
    [super dealloc];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];

    AdViewType type;
    AdViewType fullType;
    NSString* key;
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        type = AdViewTypeLargeBanner;
        fullType = AdViewTypeFullScreen;
        key = [NSString stringWithFormat:@"%s", kAdsMogoKey_iPad];
    }
    else
    {
        type = AdViewTypeNormalBanner;
        fullType = AdViewTypeiPadFullScreen;
        key = [NSString stringWithFormat:@"%s", kAdsMogoKey];
    }
    
    adView = [[AdMoGoView alloc] initWithAppKey:key
                                         adType:type
                                    expressMode:YES
                             adMoGoViewDelegate:self];
    adView.adWebBrowswerDelegate = self;
    adView.frame = CGRectZero;
    [self.view addSubview:adView];
    [adView release];
    
    if (HBUmeng::getParamValue("isAdFullEnable") == 1)
    {
        adFullView = [[AdMoGoView alloc] initWithAppKey:key
                                             adType:fullType
                                            expressMode:YES
                                     adMoGoViewDelegate:self];
        adFullView.adWebBrowswerDelegate = self;
        adFullView.frame = CGRectZero;
        [self.view addSubview:adFullView];
        [adFullView release];
    }
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - Ads delegate 
- (UIViewController *)viewControllerForPresentingModalView {
    return self;
}

- (void)adMoGoDidStartAd:(AdMoGoView *)adMoGoView {
//    NSLog(@"广告开始请求回调");
}

- (void)adMoGoDidReceiveAd:(AdMoGoView *)adMoGoView {
//    NSLog(@"广告接收成功回调");
//    CGRect bounds = [[UIScreen mainScreen] applicationFrame];
    CGRect rc = adMoGoView.frame;
//    rc.origin.x = (bounds.size.width - rc.size.width) / 2;
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        rc.origin.x = 40;
        rc.origin.y = (768 - rc.size.height);
    }
    else
    {
        rc.origin.x = 10;
        rc.origin.y = (320 - rc.size.height);
    }
    
    adMoGoView.frame = rc;
}

- (void)adMoGoDidFailToReceiveAd:(AdMoGoView *)adMoGoView didFailWithError:(NSError *)error {
//    NSLog(@"广告接收失败回调");
}

- (void)adMoGoClickAd:(AdMoGoView *)adMoGoView {
//    NSLog(@"点击广告回调");
}

- (void)adMoGoDeleteAd:(AdMoGoView *)adMoGoView {
//    NSLog(@"广告关闭回调");
}

#pragma mark - Full Screen
/*Full Screen Notifications*/
- (void)adMoGoFullScreenAdReceivedRequest
{
    NSLog(@"全屏广告 接收成功");
}

- (void)adMoGoFullScreenAdFailedWithError:(NSError *) error
{
    NSLog(@"全屏广告 接收失败");
}

- (void)adMoGoWillPresentFullScreenAdModal
{
    NSLog(@"全屏广告展示");
}

- (void)adMoGoDidDismissFullScreenAdModal
{
    NSLog(@"全屏广告消失");
}

#pragma mark - AdMoGoWebBrowserControllerUserDelegate delegate

- (void)webBrowserWillAppear {
//    NSLog(@"浏览器将要展示");
}

- (void)webBrowserDidAppear {
//    NSLog(@"浏览器已经展示");
}

- (void)webBrowserWillClosed {
//    NSLog(@"浏览器将要关闭");
}

- (void)webBrowserDidClosed {
//    NSLog(@"浏览器已经关闭");
}

- (void)webBrowserShare:(NSString *)url {
    
}

#if __IPAD_OS_VERSION_MAX_ALLOWED >= __IPAD_6_0
- (NSUInteger) supportedInterfaceOrientations{
    return UIInterfaceOrientationMaskLandscape;
}

- (BOOL) shouldAutorotate {
    return YES;
}
#endif

@end
