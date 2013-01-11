#include "LayerHelp.h"
#include "LayerGame.h"
//#include "CommonHelper.h"

CCScene* LayerHelp::scene(bool isInGame)
{
	CCScene *scene = CCScene::create();
	LayerHelp* layer = LayerHelp::create();
	if (isInGame)
		layer->loadInGame();
	scene->addChild(layer);
	
	return scene;
}

bool LayerHelp::init()
{
	if ( !CCLayer::init() )
		return false;
	
	setTouchEnabled(true);
	
	CCSprite* bg = createImage("ui_bg_help.jpg", 240, 160, this);
    HBSetRatioScale(bg);

	labelHelp1_ = CCLabelTTF::create(getLocalizedString("1.Drag white hole to absorb these invaders."), gFontName, 12,  CCSizeRatio(105, 60), kCCTextAlignmentCenter);
	labelHelp1_->setColor(ccYELLOW);
	labelHelp1_->setPosition(ccpRatio(402, 215));
	addChild(labelHelp1_);
	
	labelHelp1_->runAction(CCSequence::create(CCDelayTime::create(0.3), CCBlink::create(0.5, 3), CCCallFunc::create(this, callfunc_selector(LayerHelp::_help1Finish)), NULL));
	
	labelHelp2_ = CCLabelTTF::create(getLocalizedString("2.Miss any \"GREEN\" or \"YELLOW\" invader, or hit the \"RED\" invader will lose 1 life."), gFontName, 12, CCSizeRatio(125, 85), kCCTextAlignmentCenter);
	labelHelp2_->setColor(ccYELLOW);
	labelHelp2_->setPosition(ccpRatio(190, 85));
	labelHelp2_->setVisible(false);
	addChild(labelHelp2_);
	
	labelHelp3_ = CCLabelTTF::create(getLocalizedString("3.You can use spell to boost scores."), gFontName, 12, CCSizeRatio(106, 42), kCCTextAlignmentCenter);
	labelHelp3_->setColor(ccYELLOW);
	labelHelp3_->setPosition(ccpRatio(134, 250));
	labelHelp3_->setVisible(false);
	addChild(labelHelp3_);
	
	labelContinue_ = createLabel(getLocalizedString("Tap screen to continue"), gFontName, 12, gAnchorRight, ccYELLOW, 460, 20, this);
	
	help1Finished_ = help2Finished_ = help3Finished_ = false;
	curStep_ = 0;

	return true;
}

void LayerHelp::_help1Finish()
{
    SimpleAudioEngine::sharedEngine()->playEffect(EF_TIPS);
	labelHelp1_->stopAllActions();
	help1Finished_ = true;
}

void LayerHelp::_help2Finish()
{
    SimpleAudioEngine::sharedEngine()->playEffect(EF_TIPS);
	labelHelp2_->stopAllActions();
	help2Finished_ = true;
}

void LayerHelp::_help3Finish()
{
    SimpleAudioEngine::sharedEngine()->playEffect(EF_TIPS);
	labelHelp3_->stopAllActions();
	help3Finished_ = true;
}

bool LayerHelp::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (curStep_ == 0 && help1Finished_)
	{
		curStep_ = 1;
		labelHelp2_->setVisible(true);
		labelHelp2_->runAction(CCSequence::create(CCBlink::create(0.5, 3), CCCallFunc::create(this, callfunc_selector(LayerHelp::_help2Finish)), NULL));
	}
	else if(curStep_ == 1 && help2Finished_)
	{
		curStep_ = 2;
		labelHelp3_->setVisible(true);
		labelHelp3_->runAction(CCSequence::create(CCBlink::create(0.5, 3), CCCallFunc::create(this, callfunc_selector(LayerHelp::_help3Finish)), NULL));
	}
	else if(curStep_ == 2 && help3Finished_)
	{
		Audio->playEffect(EF_CLICK);
		if (isGameLoad_)
		{
			getParent()->removeChild(this, true);
		}
		else
        {
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, LayerGame::scene()));
        }
	}
	return true;
}

//k
//void LayerHelp::registerWithTouchDispatcher()
//{
//	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, kCCMenuTouchPriority-1, true);
//}

void LayerHelp::loadInGame()
{
	curStep_ = 2;
	help3Finished_ = true;
	labelHelp1_->stopAllActions();
	labelHelp2_->setVisible(true);
	labelHelp3_->setVisible(true);
	isGameLoad_ = true;
}