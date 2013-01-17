#include "LayerHelp.h"
#include "GlobalData.h"
#include "LayerGameLoader.h"

LayerHelp::LayerHelp()
: mLabelContinue(NULL)
, mBg(NULL)
, mIsInGame(false)
{
    for (int i = 0; i < 3; i++)
        mLabelHelp[i] = NULL;
    
    mActionHelp = CCSequence::create(CCDelayTime::create(0.3), CCBlink::create(0.5, 3), CCCallFunc::create(this, callfunc_selector(LayerHelp::_helpFinish)), NULL);
    mActionHelp->retain();
}

LayerHelp::~LayerHelp()
{
    for (int i = 0; i < 3; i++)
        CC_SAFE_RELEASE(mLabelHelp[i]);
    CC_SAFE_RELEASE(mLabelContinue);
    CC_SAFE_RELEASE(mBg);
    
    mActionHelp->release();
}

bool LayerHelp::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelHelp1", CCLabelTTF*, mLabelHelp[0]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelHelp2", CCLabelTTF*, mLabelHelp[1]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelHelp3", CCLabelTTF*, mLabelHelp[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelContinue", CCLabelTTF*, mLabelContinue);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBg", CCSprite*, mBg);
    return false;
}

void LayerHelp::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
	setTouchEnabled(true);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    float ratiox = size.width / 960.0f;
    float ratioy = size.height / 640.0f;
    
    mBg->setScaleX(ratiox);
    mBg->setScaleY(ratioy);

    mLabelHelp[0]->setString(gls("Help1"));
    mLabelHelp[1]->setString(gls("Help2"));
    mLabelHelp[2]->setString(gls("Help3"));
    mLabelContinue->setString(gls("Tap to continue"));
    
    if (mIsInGame)
    {
        mCurStep = 2;
        for (int i = 0; i < 3; i++)
            mHelpFinished[i] = true;
        mLabelHelp[1]->setVisible(true);
        mLabelHelp[2]->setVisible(true);
    }
    else
    {
        mCurStep = 0;
        mLabelHelp[0]->runAction((CCAction*)mActionHelp->copy()->autorelease());
        for (int i = 0; i < 3; i++)
            mHelpFinished[i] = false;
    }
}

void LayerHelp::_helpFinish()
{
    Audio->playEffect(EF_TIPS);
    mLabelHelp[mCurStep]->stopAllActions();
    mHelpFinished[mCurStep] = true;
}

void LayerHelp::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, tp_dialog, true);
}

bool LayerHelp::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (mHelpFinished[mCurStep])
    {
        if(mCurStep == 2)
        {
            Audio->playEffect(EF_CLICK);
            if (mIsInGame)
                getParent()->removeChild(this, true);
            else
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HBSceneLoader("LayerGame", LayerGameLoader::loader())));
        }
        else
        {
            mCurStep ++;
            mLabelHelp[mCurStep]->setVisible(true);
            mLabelHelp[mCurStep]->runAction((CCAction*)mActionHelp->copy()->autorelease());
        }
    }

	return true;
}
