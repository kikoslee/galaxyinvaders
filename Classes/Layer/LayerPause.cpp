#include "LayerPause.h"
//#include "LayerGame.h"
#include "LayerStore.h"
//#include "LayerHelp.h"
#include "GlobalData.h"

LayerPause::LayerPause()
{
}

LayerPause::~LayerPause()
{
}

void LayerPause::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
}

SEL_MenuHandler LayerPause::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler LayerPause::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

bool LayerPause::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    return false;
}

/*
CCPoint sStartPos = ccp(70,180);

bool LayerPause::init()
{
    createLabel(getLocalizedString("Current Mission"), gFontName, 16, gAnchorCenter, gColorBtn, 240, 280, this);
    createLabel(GDShared->getCurObjName(), gFontName, 14, gAnchorLeft, ccYELLOW, 200, 260, this);
    createLabel(GDShared->getCurObjDesc(), gFontName, 10, gAnchorLeft, gColorBtn, 200, 247, this);
	
	// Enemies
	createLabel(getLocalizedString("All Invaders"), gFontName, 20, gAnchorLeft, ccYELLOW, 80, 210, this);

	for( int i = 0; i < INVADERS_COUNT - 2; i++)
	{
		const InvaderData& index = GDShared->getInvader((InvaderType)i);
		int x = sStartPos.x + (i % 3) * 120;
		int y = sStartPos.y - (i / 3) * 40;
		invader->setPosition(ccp(x,y));
		invader->setScale(0.8);
		invader->setAnchorPoint(gAnchorLeft);
		addChild(invader);

        createLabel(fcs("x %d", GDShared->curInvadersCount[i]), gFontName, 18, gAnchorLeft, ccYELLOW, x+45, y, this);
	}
	
	CCMenu* menu = createMenu(this);
	
	CCMenuItem* item;
    item = createMenuItemWithCache("btn1.png", "btn1_d.png", 420, 80, pmtQuit, menu, this, menu_selector(LayerPause::_menuCallback));
	addMenuLabel(item, getLocalizedString("Quit"), gFontName, 16, ccWHITE);
	item = createMenuItemWithCache("btn1.png", "btn1_d.png", 420, 25, pmtContinue, menu, this, menu_selector(LayerPause::_menuCallback));
	addMenuLabel(item, getLocalizedString("Continue"), gFontName, 16, ccWHITE);
	
	createMenuItemWithCache("btn-help.png", "btn-help.png", 450, 295, pmtHelp, menu, this, menu_selector(LayerPause::_menuCallback));
	
	return true;
}

void LayerPause::_menuCallback(CCObject* sender)
{
	int index = ((CCMenuItem*)sender)->getTag();

	Audio->playEffect(EF_CLICK);

	switch(index)
	{
		case pmtQuit:
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LayerStore::scene()));
			Audio->playBackgroundMusic(MUSIC_BG1, true);
			break;
		case pmtContinue:
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
			break;
		}
		case pmtHelp:
		{
			LayerHelp* layer = LayerHelp::create();
			layer->loadInGame();
			getParent()->addChild(layer, 30000);
		}
	}
}
*/