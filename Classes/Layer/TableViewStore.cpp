#include "TableViewStore.h"
#include "StoreItem.h"
#include "StoreItemLoader.h"
#include "GlobalData.h"

TableViewStore::TableViewStore()
{
}

TableViewStore::~TableViewStore(void)
{
}

bool TableViewStore::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	setTouchEnabled(true);

    return true;
}

void TableViewStore::createTable(CCSize size)
{
    setContentSize(size);
	mTableView = CCTableView::create(this, CCSizeMake(size.width, size.height));
    //    tableView->setTouchPriority(0);
	mTableView->setDirection(kCCScrollViewDirectionVertical);
    //	tableView->setPosition(ccp(0,54));
	mTableView->setDelegate(this);
	mTableView->setAnchorPoint(ccp(0.0, 1.0));
	addChild(mTableView);
	mTableView->reloadData();
}

void TableViewStore::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
//    CCLOG("cell touched at index: %i", cell->getIdx());
//    if (((GOEMapItem*)gameBoard->_globalData.mapArr->objectAtIndex(cell->getIdx()))->status)
//    {
//        gameBoardViewDelegate->keypressedMapItem(cell->getIdx());
//    }
}

CCSize TableViewStore::cellSizeForTable(CCTableView *table)
{
	  return CCSizeMake(getContentSize().width, 130);
}

CCTableViewCell* TableViewStore::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    StoreItem* item;
    CCTableViewCell *cell = table->dequeueCell();
    
    if (!cell)
    {
        cell = new CCTableViewCell;
        cell->autorelease();

        item = (StoreItem*)HBLayerLoader("StoreItem", StoreItemLoader::loader());
        item->setTag(100);
        cell->addChild(item);
    }
    else
    {
        item = (StoreItem*)cell->getChildByTag(100);
		//index_map++;
// 		CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
// 		label->setString(string->getCString());
//		TableViewCellMapItem * tvcm_ = (TableViewCellMapItem *)cell->getChildByTag(102);
//		tvcm_->ShowDungeonMapView(idx,gameBoard);
		//CCLOG("2.  Cell is  not null , idx : %d , index : %d", idx , index_map);
    }
	
    item->updateItem(idx);
        
    return cell;
}

unsigned int TableViewStore::numberOfCellsInTableView(CCTableView *table)
{
    return 7;//gameBoard->_globalData.mapItemCount;
}