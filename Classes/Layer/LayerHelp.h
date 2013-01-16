//
//  LayerHelp.h
//  GalaxyInvaders
//
//  Created by Limin on 12-6-3.
//  Copyright (c) 2012年 HappyBluefin. All rights reserved.
//

#ifndef _LayerHelp_H_
#define _LayerHelp_H_

#include "HBCommon.h"

class LayerHelp
: public CCLayer
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    LayerHelp();
    virtual ~LayerHelp();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LayerHelp, create);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

	void setInGame(bool isInGame) { mIsInGame = isInGame; }

    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent *event);

private:
	CCLabelTTF* mLabelHelp[3];
	CCLabelTTF* mLabelContinue;
	CCSprite* mBg;
    CCAction* mActionHelp;
	
	bool mHelpFinished[3];
	
	int mCurStep;
	
	bool mIsInGame;
	
	void _helpFinish();
};

#endif
