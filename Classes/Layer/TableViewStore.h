#ifndef _TableViewStore_H_
#define _TableViewStore_H_

#include "HBCommon.h"

class TableViewStore
: public CCLayer
, public CCTableViewDataSource
, public CCTableViewDelegate
{
public:
    CREATE_FUNC(TableViewStore);
    
	TableViewStore();
	virtual ~TableViewStore();
    
    virtual bool init();
    
    // pure virtual function
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    void createTable(CCSize size);
    
    CCTableView* mTableView;
};

#endif
