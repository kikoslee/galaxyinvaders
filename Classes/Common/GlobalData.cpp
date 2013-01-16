
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "GlobalData.h"
#include "LayerBuyLoader.h"

GlobalData::GlobalData()
{
    mPurchaseItem.push_back("com.liho.galaxyinvaders.coin1");
    mPurchaseItem.push_back("com.liho.galaxyinvaders.coin2");
    mPurchaseItem.push_back("com.liho.galaxyinvaders.coin3");
    mPurchaseItem.push_back("com.liho.galaxyinvaders.coin4");
    mPurchaseItem.push_back("com.liho.galaxyinvaders.coin5");
    mPurchaseItem.push_back("com.liho.galaxyinvaders.coin6");
    
    mPurchaseGold.push_back(1000);
    mPurchaseGold.push_back(2000);
    mPurchaseGold.push_back(3000);
    mPurchaseGold.push_back(4000);
    mPurchaseGold.push_back(5000);
    mPurchaseGold.push_back(6000);
    
    mDefaultPurchaseFee.push_back("$0.99");
    mDefaultPurchaseFee.push_back("$4.99");
    mDefaultPurchaseFee.push_back("$9.99");
    mDefaultPurchaseFee.push_back("$19.99");
    mDefaultPurchaseFee.push_back("$49.99");
    mDefaultPurchaseFee.push_back("$99.99");
}

GlobalData::~GlobalData()
{
}

void GlobalData::loadConfigFile(const char* file)
{
	const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(file);
	xmlDocPtr doc = xmlReadFile(pszPath, "utf-8", XML_PARSE_RECOVER);
	
	xmlNodePtr rootNode;
	xmlNodePtr curNode = NULL;
	
	rootNode = xmlDocGetRootElement(doc);
	if (NULL == rootNode)
	{
		CCLOG("%s read error", file);
		return;
	}

	curNode = rootNode->children;
	while (NULL != curNode)
	{
		if (!xmlStrcmp(curNode->name, BAD_CAST "objectives"))
		{
            /*
             <!--
             id    序号
             名称和说明利用序号从多语言文件中取得 objective_name_xx, objective_desc_xx
             type  类型
             score   分数
             last    生存时间
             green   吃到绿色的数量
             yellow  吃到红色的数量
             total   吃到的总数
             avoid   什么都没吃到持续时间
             value 检测值
             -->  
             */
			xmlNodePtr elem = curNode->children;
			while (NULL != elem)
			{
				if (!xmlStrcmp(elem->name, BAD_CAST "obj"))
				{
					Objective obj;
						
					xmlChar* type = xmlGetProp(elem, BAD_CAST "type");
					if (!xmlStrcmp(type, BAD_CAST "score"))
						obj.type = otScore;
					else if (!xmlStrcmp(type, BAD_CAST "last"))
						obj.type = otLast;
					else if (!xmlStrcmp(type, BAD_CAST "green"))
						obj.type = otGreen;
					else if (!xmlStrcmp(type, BAD_CAST "yellow"))
						obj.type = otYellow;
					else if (!xmlStrcmp(type, BAD_CAST "total"))
						obj.type = otTotal;
					xmlFree(type);
							
					xmlChar* index = xmlGetProp(elem, BAD_CAST "index");
					obj.index = atoi((char*)index);
					xmlFree(index);

					xmlChar* value1 = xmlGetProp(elem, BAD_CAST "value");
					obj.value = atoi((char*)value1);
					xmlFree(value1);

					xmlChar* reward = xmlGetProp(elem, BAD_CAST "reward");
					obj.reward = atoi((char*)reward);
					xmlFree(reward);
							
					mObjectives.push_back(obj);
				}							
				elem = elem->next;
			}
		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "invaders"))
		{
            /*
             <invaders>
             <inv type="normal1" score="10" filename="normal1.png" frame="2" />
             type - 侵略者类型
             score - 基础分数
             filename - 图像文件名
             frame - 动画帧数
             */
			xmlNodePtr elem = curNode->children;
			while (NULL != elem)
			{
				if (!xmlStrcmp(elem->name, BAD_CAST "inv"))
				{
					InvaderData inv;
                    
					xmlChar* item = xmlGetProp(elem, BAD_CAST "type");
					if (!xmlStrcmp(item, BAD_CAST "normal1"))
						inv.type = IT_Normal_1;
					else if (!xmlStrcmp(item, BAD_CAST "normal2"))
						inv.type = IT_Normal_2;
					else if (!xmlStrcmp(item, BAD_CAST "normal3"))
						inv.type = IT_Normal_3;
					else if (!xmlStrcmp(item, BAD_CAST "normal4"))
						inv.type = IT_Normal_4;
					else if (!xmlStrcmp(item, BAD_CAST "bad"))
						inv.type = IT_Bad;
					else if (!xmlStrcmp(item, BAD_CAST "gold"))
						inv.type = IT_Gold;
					else if (!xmlStrcmp(item, BAD_CAST "gold2"))
						inv.type = IT_Gold2;
					xmlFree(item);
                    
					item = xmlGetProp(elem, BAD_CAST "score");
					inv.baseScore = atoi((char*)item);
					xmlFree(item);
                    
					item = xmlGetProp(elem, BAD_CAST "filename");
					inv.fileName = (char*)item;
					xmlFree(item);
                    
					item = xmlGetProp(elem, BAD_CAST "frame");
					inv.frameCount = atoi((char*)item);
					xmlFree(item);
                    
					mInvadersData.push_back(inv);
				}							
				elem = elem->next;
			}
		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST "spells"))
		{
            /*
            <spells>
            <sp type="freeze" filename="spell_freeze.png" iconname="icon_freeze.png" duration="15" cd1="30" cd2="25" cd3="20" cd4="15" equipCost="500" upgradeCost1="3000" upgradeCost2="6000" upgradeCost3="9000" upgradeCost4="0" />
             type - 魔法类型
             filename - 魔法图片
             iconname - 图标图片
             duration - 持续时间
             cd1~cd4 - 冷却时间
             equipCost - 装备花费
             upgradeCost1~4 - 升级花费
            */
			xmlNodePtr elem = curNode->children;
			while (NULL != elem)
			{
				if (!xmlStrcmp(elem->name, BAD_CAST "sp"))
				{
					SpellData sp;
                    
					xmlChar* item = xmlGetProp(elem, BAD_CAST "type");
					if (!xmlStrcmp(item, BAD_CAST "freeze"))
						sp.type = ST_Freeze;
					else if (!xmlStrcmp(item, BAD_CAST "shield"))
						sp.type = ST_Shield;
					else if (!xmlStrcmp(item, BAD_CAST "bomb"))
						sp.type = ST_Bomb;
					xmlFree(item);
                    
					item = xmlGetProp(elem, BAD_CAST "filename");
					sp.fileName = (char*)item;
					xmlFree(item);
                    
					item = xmlGetProp(elem, BAD_CAST "iconname");
					sp.iconName = (char*)item;
					xmlFree(item);
                    
                    item = xmlGetProp(elem, BAD_CAST "duration");
                    sp.duration = atof((char*)item);
                    xmlFree(item);
                    
                    item = xmlGetProp(elem, BAD_CAST "cd1");
                    sp.cdTime[0] = atof((char*)item);
                    xmlFree(item);

                    item = xmlGetProp(elem, BAD_CAST "cd2");
                    sp.cdTime[1] = atof((char*)item);
                    xmlFree(item);

                    item = xmlGetProp(elem, BAD_CAST "cd3");
                    sp.cdTime[2] = atof((char*)item);
                    xmlFree(item);

                    item = xmlGetProp(elem, BAD_CAST "cd4");
                    sp.cdTime[3] = atof((char*)item);
                    xmlFree(item);

                    item = xmlGetProp(elem, BAD_CAST "equipCost");
                    sp.equipCost = atoi((char*)item);
                    xmlFree(item);

                    item = xmlGetProp(elem, BAD_CAST "upgradeCost1");
                    sp.upgradeCost[0] = atoi((char*)item);
                    xmlFree(item);
                    
                    item = xmlGetProp(elem, BAD_CAST "upgradeCost2");
                    sp.upgradeCost[1] = atoi((char*)item);
                    xmlFree(item);

                    item = xmlGetProp(elem, BAD_CAST "upgradeCost3");
                    sp.upgradeCost[2] = atoi((char*)item);
                    xmlFree(item);

                    item = xmlGetProp(elem, BAD_CAST "upgradeCost4");
                    sp.upgradeCost[3] = atoi((char*)item);
                    xmlFree(item);

                    mSpellsData.push_back(sp);
				}
				elem = elem->next;
			}
		}
        
		curNode = curNode->next;
	}
	
	xmlFreeDoc(doc);
}

const char* GlobalData::getCurObjName()
{
	const Objective& obj = getCurObj();
	if (obj.type == otScore)
		return fcs(gls("Objective_Name_Score"), obj.index);
	else if (obj.type == otLast)
		return fcs(gls("Objective_Name_Last"), obj.index);
	else if (obj.type == otGreen)
		return fcs(gls("Objective_Name_Green"), obj.index);
	else if (obj.type == otYellow)
		return fcs(gls("Objective_Name_Yellow"), obj.index);
	else // (obj.type == otTotal)
		return fcs(gls("Objective_Name_Total"), obj.index);
}

const char* GlobalData::getCurObjDesc()
{
	const Objective& obj = getCurObj();
	if (obj.type == otScore)
		return fcs(gls("Objective_Desc_Score"), obj.value);
	else if (obj.type == otLast)
		return fcs(gls("Objective_Desc_Last"), obj.value);
	else if (obj.type == otGreen)
		return fcs(gls("Objective_Desc_Green"), obj.value);
	else if (obj.type == otYellow)
		return fcs(gls("Objective_Desc_Yellow"), obj.value);
	else // (obj.type == otTotal)
		return fcs(gls("Objective_Desc_Total"), obj.value);
}

void GlobalData::saveUserData()
{
	CCUserDefault* ud = CCUserDefault::sharedUserDefault();
	
	ud->setBoolForKey("alreadySaved", true);
	ud->setStringForKey("version", "1.0");
    
	ud->setBoolForKey("musicOn", isMusicOn);
	ud->setIntegerForKey("gold", gold);
	ud->setBoolForKey("isReview", isReview);
	ud->setIntegerForKey("curObj", curObj);
	ud->setIntegerForKey("multiplier", multiplier);
	ud->setBoolForKey("firstTime", isFirstTime);
    ud->setIntegerForKey("startTimes", startTimes);
    
	for(int i = 0; i < SPELL_TYPE_COUNT; i++)
	{
		ud->setIntegerForKey(fcs("spellCount%d", i), spellCount[i]);
		ud->setIntegerForKey(fcs("spellLevel%d", i), spellLevel[i]);
	}
	ud->setIntegerForKey("maxLife", maxLife);
    
	ud->flush();
}

void GlobalData::loadUserData()
{
	CCUserDefault* ud = CCUserDefault::sharedUserDefault();
    
	bool alreadySaved = ud->getBoolForKey("alreadySaved");
	if(alreadySaved)
	{
		// 已经有存盘数据了，读取之
		string ver = ud->getStringForKey("version");
        
        isMusicOn = ud->getBoolForKey("musicOn");
		gold = ud->getIntegerForKey("gold");
		isReview = ud->getBoolForKey("isReview");
		curObj = ud->getIntegerForKey("curObj");
		multiplier = ud->getIntegerForKey("multiplier");
		isFirstTime = ud->getBoolForKey("firstTime");
        startTimes = ud->getIntegerForKey("startTimes");
			
        for(int i = 0; i < SPELL_TYPE_COUNT; i++)
        {
            spellCount[i] = ud->getIntegerForKey(fcs("spellCount%d", i));
			spellLevel[i] = ud->getIntegerForKey(fcs("spellLevel%d", i));
		}
        maxLife = ud->getIntegerForKey("maxLife");
	}
	else
	{
		initUserData();
		saveUserData();
	}
}

void GlobalData::initUserData()
{
	// 初始化数据
	isMusicOn = true;
	gold = 20000;
	isReview = false;
	curObj = 0;
	multiplier = 1;
	isFirstTime = true;
    startTimes = 0;
	
	for(int i = 0; i < SPELL_TYPE_COUNT; i++)
	{
		spellCount[i] = 1;
		spellLevel[i] = 0;
	}
	maxLife = 1;
}

void GlobalData::clearCurGameData()
{
    memset(curInvadersCount, 0, sizeof(int) * INVADERS_COUNT);
	memset(curGenerateCount, 0, sizeof(int) * INVADERS_COUNT);
	curScore = 0;
	curLastTime = 0;
	curSpeedFactor = 1;
}

void GlobalData::showLayerBuy()
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	scene->addChild(HBLayerLoader("LayerBuy", LayerBuyLoader::loader()), 50000);
}

void GlobalData::addPurchaseGold(const char* itemName)
{
    for (int i = 0; i < mPurchaseItem.size(); ++i)
    {
        if (mPurchaseItem[i] == itemName)
        {
            gold += mPurchaseGold[i];
            saveUserData();
            break;
        }
    }
}