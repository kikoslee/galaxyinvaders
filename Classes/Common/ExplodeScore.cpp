#include "ExplodeScore.h"

ExplodeScore::ExplodeScore(CCPoint pos, int score, InvaderType type)
{
	initWithString("", gFontNumber, 20);
	
	float destScale = 1;
	float destMove = 100;
	float time = 1;

    const char* sc = fcs("%d", score);

	switch(type)
	{
		case IT_Normal_1:
		case IT_Normal_2:
		case IT_Normal_3:
		case IT_Normal_4:
			destScale = 2;
			setColor(ccc3(0, 0xFF, 0xFF));
			break;
		case IT_Gold:
            sc = fcs("GOLD +%d", score);
			destScale = 5;
			setColor(ccc3(255,215,0));
			break;
		default:
			break;
	}

	setString(sc);
	setPosition(pos);
	runAction(CCSequence::create(CCSpawn::create(CCMoveBy::create(time, ccp(0, destMove)), CCScaleTo::create(time, destScale), CCFadeOut::create(time), NULL), CCCallFunc::create(this, callfunc_selector(ExplodeScore::destroy)), NULL));

	autorelease();
}

void ExplodeScore::destroy()
{
	stopAllActions();
	getParent()->removeChild(this, true);
}
