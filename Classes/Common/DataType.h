#ifndef _DataType_H_
#define _DataType_H_

#include "HBCommon.h"

#define IAP_COUNT   6
extern int gIapGold[IAP_COUNT];

extern const char* gFontHelvetica;
extern const char* gFontName;               // 普通字体名称
extern const char* gFontNumber;             // 数字字体名称

typedef enum
{
    tp_dialog = kCCMenuHandlerPriority - 1,
    tp_dialogBtn = kCCMenuHandlerPriority - 2,
} TouchPriority;

#define INVADERS_COUNT	7
enum InvaderType
{
	IT_Normal_1		= 0,
	IT_Normal_2,
	IT_Normal_3,
	IT_Normal_4,
	IT_Bad,
	IT_Gold,
	IT_Gold2,
};

struct InvaderData
{
	InvaderType				type;			// 种类
	int						baseScore;		// 基础分值
	string                  fileName;		// 文件名
	int						frameCount;		// 帧数
	CCArray*                frameArr;		// 精灵
	CCAction*               animation;		// 动画
};

#define SPELL_TYPE_COUNT 3
enum SpellType
{
	ST_Freeze,                              // 减速
	ST_Shield,                              // 护盾
	ST_Bomb,                                // 炸弹
};

// 魔法数据
struct SpellData
{
	SpellType		type;                   // 类型
	string          fileName;               // 文件名
	string          iconName;               // 图标名
	float			duration;               // 持续时间
	float			cdTime[4];              // 冷却时间
	int				equipCost;              // 装备花费
	int				upgradeCost[4];         // 升级花费
};

// 任务类型
enum ObType
{
	otScore,                                // 分数
	otLast,                                 // 生存时间
	otGreen,                                // 绿色数量
	otYellow,                               // 黄色数量
	otTotal,                                // 总数
};

// 任务结构
struct Objective
{
	ObType	type;                           // 类型
	int		index;                          // 同类内的编号
	int		value;                          // 所需目标
	int		reward;                         // 奖励金币
};

const ccColor3B gColorBtn = ccc3(221, 233, 246);

#define MUSIC_BG1		"sound/m1.m4a"
#define MUSIC_BG2		"sound/m2.m4a"
#define EF_CLICK		"sound/click.m4a"         // 按钮
#define EF_TIPS			"sound/tips.m4a"          // 帮助提示
#define EF_EQUIPSPELL	"sound/equip.m4a"         // 装配魔法
#define EF_UPSPELL		"sound/upgrade.m4a"       // 升级
#define EF_POPBUY		"sound/popbuy.m4a"        // 弹出购买界面
#define EF_COLNORMAL	"sound/colnormal.m4a"     // 碰撞普通
#define EF_COLADVANCE   "sound/coladvance.m4a"    // 碰撞高级
#define EF_COLGOLD		"sound/colgold.m4a"       // 碰撞金币
#define EF_BOMB         "sound/bomb.m4a"          // 炸弹
#define EF_COLSHIELD	"sound/shield.m4a"        // 弹开
#define EF_COLBAD		"sound/colred.m4a"        // 碰撞RED
#define EF_CAST			"sound/popbuy.m4a"        // 释放魔法
#define EF_MISS			"sound/miss.m4a"          // 漏掉
#define EF_FINISH       "sound/finish.m4a"        // 游戏结束
#define EF_TASKFINISH	"sound/taskfinish.m4a"    // 任务完成
#define EF_COIN			"sound/coin.m4a"          // 金币购买

#endif