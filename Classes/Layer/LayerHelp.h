//
//  LayerHelp.h
//  GalaxyInvaders
//
//  Created by Limin on 12-6-3.
//  Copyright (c) 2012年 HappyBluefin. All rights reserved.
//

#ifndef _LayerHelp_H_
#define _LayerHelp_H_

class LayerHelp : public CCLayer
{	
	CCLabelTTF* labelHelp1_;
	CCLabelTTF* labelHelp2_;
	CCLabelTTF* labelHelp3_;
	
	CCLabelTTF* labelContinue_;
	CCAction* actionContinue_;
	
	bool help1Finished_;
	bool help2Finished_;
	bool help3Finished_;
	
	int curStep_;
	
	bool isGameLoad_;
	
	void _help1Finish();
	void _help2Finish();
	void _help3Finish();
	
public:
    virtual ~LayerHelp() {};
	virtual bool init();
	
	static CCScene* scene(bool isInGame);
	
	CREATE_FUNC(LayerHelp);
	
	void loadInGame();
    
    void onEnter() {};
    void onExit() {};
	
	bool ccTouchBegan(CCTouch* touch, CCEvent *event);
};

#endif
