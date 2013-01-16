//
//  StaticData.h
//  GalaxyInvaders
//
//  Created by Limin on 12-6-1.
//  Copyright (c) 2012年 HappyBluefin. All rights reserved.
//

#ifndef _StaticData_H_
#define _StaticData_H_

#include "HBCommon.h"
#include "DataType.h"

class GlobalData : public HBSingleton<GlobalData>
{
    vector<Objective> mObjectives;
    vector<InvaderData> mInvadersData;
    vector<SpellData> mSpellsData;

public:
	bool isMusicOn;                         // 是否开启声音
	bool isFirstTime;                       // 是否新手
	bool isReview;                          // 是否评论过

    int startTimes;                         // 启动次数
	int gold;                               // 当前金币
	int curObj;                             // 当前任务序号
	
	int spellLevel[SPELL_TYPE_COUNT];		// 魔法当前级别
	int spellCount[SPELL_TYPE_COUNT];		// 魔法当前数量
	int maxLife;							// 最大生命数
	int multiplier;							// 当前倍率
    
    int curInvadersCount[INVADERS_COUNT];   // 当前局侵略者数量
	int curGenerateCount[INVADERS_COUNT];   // 当前局侵略者产生数量
	int curScore;                           // 当前局分数
	int curLastTime;                        // 当前局持续时间
	float curSpeedFactor;                   // 当前局速度因子
    
    vector<string> mPurchaseItem;
    vector<int> mPurchaseGold;
    vector<string> mDefaultPurchaseFee;
    
public:
	GlobalData();
	~GlobalData();
	
	void loadConfigFile(const char* file);
	
	int getObjCount() { return mObjectives.size(); }
	const Objective& getCurObj() { return mObjectives[curObj]; }
    const char* getCurObjName();
    const char* getCurObjDesc();

    int getInvaderCount() { return mInvadersData.size(); }
    InvaderData& getInvader(InvaderType it) { return mInvadersData[it]; }
    
    int getSpellCount(SpellType st) { return spellCount[st]; }
    int getSpellLevel(SpellType st) { return spellLevel[st]; }
    const SpellData& getSpell(SpellType st) { return mSpellsData[st]; };
    
    void clearCurGameData();
    
    void initUserData();
    void saveUserData();
    void loadUserData();
    
    void showLayerBuy();
    
    void addPurchaseGold(const char* itemName);
};

#define GDShared GlobalData::shared()

#endif
