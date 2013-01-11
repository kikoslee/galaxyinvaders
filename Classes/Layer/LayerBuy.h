#ifndef _LayerBuy_H_
#define _LayerBuy_H_

#include "DataType.h"

class LayerBuy : public CCLayer
{
	CCLabelTTF* mLabelCoin;		// 总金币数
	
	CCLayer* mParentLayer;		// 调用者所在Layer
	CCLayer* mLayerList;		// 列表层

	CCMenu* mMenuMain;			// 全局按钮
	CCMenu* mMenuFree;			// 列表按钮

	CCPoint mLastPos;			// 上次点击位置
	CCTouch* mTouch;			// 点击指针
	
	int mCurListCount;			// 当前列表中的数量

	// 更新总金币数
	void _updateGoldCount();
	// 创建列表
	void _createList();
	// 更新列表位置
	void _resetListLayer(CCTouch* touch);
	// 菜单按钮回调
	void _menuCallback(CCObject* sender);
	// 销毁层
	void _destroyLayer();

public:
	bool init();
	CREATE_FUNC(LayerBuy);

	void update(float dt);
    
    void onEnter();
    void onExit();

	bool ccTouchBegan(CCTouch* touch, CCEvent *event);
	void ccTouchMoved(CCTouch* touch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch* touch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch* touch, CCEvent *pEvent);
};

#endif