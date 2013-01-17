//
//  tapburstfreeAppController.h
//  tapburstfree
//
//  Created by Limin on 12-9-4.
//  Copyright HappyBluefin 2012年. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AdMoGoDelegateProtocol.h"
#import "AdMoGoView.h"
#import "AdMoGoWebBrowserControllerUserDelegate.h"

@interface BannerAdViewController : UIViewController<AdMoGoDelegate,AdMoGoWebBrowserControllerUserDelegate> {
    AdMoGoView *adView;
    AdMoGoView *adFullView;
}
@property (nonatomic, retain) AdMoGoView *adView;
@end