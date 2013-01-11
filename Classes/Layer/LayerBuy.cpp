#include "LayerBuy.h"
#include "CommonHelper.h"
#include "GlobalData.h"

enum BuyMenuTag
{
	bmtBack = 1000,
	bmtLike,
	bmtFollow,
	bmtReview,
	bmtEmail,
	bmtDaily,
	bmtOffer,
	bmtVideo,
	bmtIap1,
	bmtIap2,
	bmtIap3,
	bmtIap4,
	bmtIap5,
	bmtIap6,
	bmtIap7,
};

struct BuyItemData
{
	const char* iconName;
	const char* desc;
	const char* menuName;
	BuyMenuTag tag;
};

BuyItemData sItemData[7] = {
	{ "icon_review.png", "Give us a review to get 1500 coins.", "Review", bmtReview, },
	{ "icon_email.png", "Feedback an email to get 1000 coins.", "Email", bmtEmail, },
	{ "icon_facebook.png", "Like us to get 800 coins.", "Like", bmtLike, },
	{ "icon_twitter.png", "Follow us to get 800 coins.", "Follow", bmtFollow, },
	{ "icon_video.png", "Watch a video to get 1000 coins.", "Watch", bmtVideo, },
	{ "icon_dailygift.png", "Get 1000 coins daily.", "Get", bmtDaily, },
	{ "icon_explore.png", "Explore more coins.", "Explore", bmtOffer, },
};

bool LayerBuy::init()
{
	if (!CCLayer::init())
		return false;
	
	setTouchEnabled(true);
	
	// 出现动画
	setPosition(ccp(480,0));
	runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5, CCPointZero)));
	
	CCLayerColor* bglayer;
	bglayer = CCLayerColor::create(ccc4(0,0,0,230));
	bglayer->setPosition(CCPointZero);
	addChild(bglayer);
	
	// background
	CCSprite* bg = createImage("ui_bg.jpg", 240, 160, this);
	bg->setOpacity(100);
	
	// 标题
	createLabel(getLocalizedString("More Coin"), gFontName, 30, gAnchorCenter, ccGREEN, 240, 300, this);
	
	// 金币总数
	createImageWithFrameName("icon_gold.png", 465, 305, this);
	mLabelCoin = createLabel(fcs("%s", HBCommaPrint(GDShared->gold)), gFontName, 12, gAnchorRight, ccYELLOW, 452, 305, this);
	
	createImageWithFrameName("ui_buy_frame.png", 240, 165, this);
		
	mMenuMain = createMenu(this);
    
    float cost[4] = { 0.99, 4.99, 9.99, 19.99 };

	for(int i = 0; i < 4; i++)
	{
		int x = (i % 2) * 90 + 330;
		int y = 235 - (i / 2) * 95;
		
		createImageWithFrameName(fcs("icon_buy%d.png", i+1), x, y, this);
		
		createLabel(fcs("%s - $%.2f", HBCommaPrint(gIapGold[i]), cost[i]), gFontName, 12, gAnchorCenter, gColorBtn, x, y - 25, this);
		
		// 打折图标
		if (i == 1)
			createImageWithFrameName("icon_save10.png", x+25, y+15, this);
		else if(i == 2)
			createImageWithFrameName("icon_save30.png", x+25, y+15, this);
		else if(i == 3)
			createImageWithFrameName("icon_save50.png", x+25, y+15, this);
		
		CCMenuItem* item = createMenuItemWithCache("btn_buy.png", "btn_buy_d.png", x, y - 50, bmtIap1+i, mMenuMain, this, menu_selector(LayerBuy::_menuCallback));
		addMenuLabel(item, getLocalizedString("Buy"), gFontName, 14, gColorBtn);
	}
	
	// 返回按钮
	CCMenuItem* item = createMenuItemWithCache("btn1.png", "btn1_d.png", 423, 25, bmtBack, mMenuMain, this, menu_selector(LayerBuy::_menuCallback));
	addMenuLabel(item, getLocalizedString("Close"), gFontName, 16, gColorBtn);	
	
	CCSprite* spector = createImageWithFrameName("ui_spector.png", 280, 155, this);
	spector->setRotation(90);
	spector->setScale(0.55);
	
////	LayerClip* clip = LayerClip::node();
////	clip->setPosition(ccpRatio(145, 165));
////	clip->setContentSize(CCSize(270, 200));
////	addChild(clip);
//	
//	mLayerList = new CCLayer;
//	clip->addChild(mLayerList);
//	mLayerList->autorelease();
	
	_createList();
	
	mTouch = NULL;
	
    scheduleUpdate();
	Audio->playEffect(EF_POPBUY);
    
	return true;
}

void LayerBuy::update(float dt)
{
    mLabelCoin->setString(fcs("%s", HBCommaPrint(GDShared->gold)));
}

void LayerBuy::_menuCallback(CCObject* sender)
{
	int index = ((CCMenuItem*)sender)->getZOrder();
	
	Audio->playEffect(EF_CLICK);
	
	if(index >= bmtIap1 && index <= bmtIap6)
	{
		int idx = index - bmtIap1;
//k        purchaseItem(idx);
	}
	else if(index == bmtBack)
	{
		runAction(CCSequence::create(CCScaleTo::create(0.2, 0), CCCallFunc::create(this, callfunc_selector(LayerBuy::_destroyLayer)), NULL));
	}
	else if(index == bmtReview)
	{
//k		gJumpToReview();
//		gGlobalData.gold += 1500;
		GDShared->isReview = true;
		GDShared->saveUserData();
		_createList();
	}
}

void LayerBuy::_destroyLayer()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	CCArray* layers = scene->getChildren();
	CCObject* child = NULL;
	CCARRAY_FOREACH(layers, child)
	{
		CC_BREAK_IF(!child);
		CCLayer* layer =(CCLayer*)child;
		if(!layer->isRunning())
			layer->onEnter();
	}
	scene->removeChild(this, true);
//	getParent()->removeChild(this, true);
}

void LayerBuy::_createList()
{
	int starty = 70;
	int deltay = 60;
	int startx = -110;
	
	mLayerList->removeAllChildrenWithCleanup(true);
	mMenuFree = createMenu(mLayerList);
		
	mCurListCount = 0;
	for (int i = 0; i < 5; i++)
	{
		if (i == 0 && GDShared->isReview)
			continue;
		
		mCurListCount++;
		BuyItemData& bid = sItemData[i];

		createImageWithFrameName(bid.iconName, startx, starty, mLayerList);
		
		CCLabelTTF* label = CCLabelTTF::create(getLocalizedString(bid.desc), gFontName, 12, CCSizeRatio(130, 50), kCCTextAlignmentLeft);
		label->setColor(gColorBtn);
		label->setAnchorPoint(gAnchorLeft);
		label->setPosition(ccpRatio(startx + 30, starty + 5));
		mLayerList->addChild(label);
		
		CCMenuItem* item = createMenuItemWithCache("btn_equip.png", "btn_equip_d.png", startx + 200, starty, bid.tag, mMenuFree, this, menu_selector(LayerBuy::_menuCallback));
		addMenuLabel(item, getLocalizedString(bid.menuName), gFontName, 12, gColorBtn);
        
		if (i < 4)
		{
			CCSprite* spector = createImageWithFrameName("ui_spector.png", 0, starty - 30, mLayerList);
			spector->setScale(0.8);
		}
		starty -= deltay;
	}
	
	_updateGoldCount();
}

void LayerBuy::_updateGoldCount()
{
	mLabelCoin->setString(fcs("%s", HBCommaPrint(GDShared->gold)));
}

void LayerBuy::onEnter()
{
    
}

void LayerBuy::onExit()
{
    
}

bool LayerBuy::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint pos = convertTouchToNodeSpace(touch);
	
	if (pos.x > 10 && pos.x < 280 && pos.y > 65 && pos.y < 265)
	{
		mLastPos = pos;
		mTouch = touch;
	}
	
#if 0 //del by zhaoyi
	if (mMenuFree->itemForTouch(touch))
		return false;
	if (mMenuMain->itemForTouch(touch))
		return false;
#endif
	
	return true;
	//返回yes是表明要取得该touch的权限,即吞噬该touch
	//返回NO 则不处理
}

void LayerBuy::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if (mTouch)
	{	_resetListLayer(touch);
	}
}

void LayerBuy::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (mTouch)
	{	_resetListLayer(touch);
		mTouch = NULL;
	}
}

void LayerBuy::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
	if (mTouch)
	{	_resetListLayer(touch);
		mTouch = NULL;
	}
}

void LayerBuy::_resetListLayer(CCTouch* touch)
{
	CCPoint touchPos = convertTouchToNodeSpace(touch);
	CCPoint curPos = mLayerList->getPosition();
	
	curPos.y += touchPos.y - mLastPos.y;
	if (curPos.y < 0)
		curPos.y = 0;
	if (curPos.y > MAX(0, 60 * mCurListCount - 200))
		curPos.y = MAX(0, 60 * mCurListCount - 200);
	
	mLayerList->setPosition(curPos);
	mLastPos = touchPos;
}