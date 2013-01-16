#include "HBCommon.h"
#include "AppDelegate.h"

#include "GlobalData.h"
#include "InvaderBase.h"
#include "LayerMainLoader.h"
#include "LayerStoreLoader.h"
#include "LayerResultLoader.h"
#include "TotalGoldLoader.h"
#include "NextMissionLoader.h"
#include "BuyItemLoader.h"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setProjection(kCCDirectorProjection2D);
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    CCFileUtils::sharedFileUtils()->setResourceDirectory("images");
    pDirector->setContentScaleFactor(1);
    if (screenSize.height > 640)
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768, kResolutionShowAll);
    else
    {
        if (screenSize.width > 960)
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1136, 640, kResolutionShowAll);
        else
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionShowAll);
    }
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    HBScore::initScore();
    HBPurchase::shared()->init(GDShared->mPurchaseItem);
    
    GDShared->loadConfigFile("database.xml");
    GDShared->loadUserData();
    HBLocaShared->readFromFile();

	srand(time(NULL));
	gCreateInvaders();

    Audio->setBackgroundMusicVolume(GDShared->isMusicOn ? 0.7 : 0);
    Audio->setEffectsVolume(GDShared->isMusicOn ? 1 : 0);
	Audio->playBackgroundMusic(MUSIC_BG1, true);

    GDShared->startTimes += 1;
    GDShared->saveUserData();
    
    HBRegistCCBLoader("TotalGold", TotalGoldLoader::loader());
    HBRegistCCBLoader("NextMission", NextMissionLoader::loader());
    HBRegistCCBLoader("BuyItem", BuyItemLoader::loader());
    
	pDirector->runWithScene(HBSceneLoader("LayerMain", LayerMainLoader::loader()));
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();
	GDShared->saveUserData();
	Audio->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();
    
	Audio->resumeBackgroundMusic();
}
