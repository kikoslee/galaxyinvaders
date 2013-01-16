#ifndef _BuyItemLoader_H_
#define _BuyItemLoader_H_

#include "BuyItem.h"

class CCBReader;

class BuyItemLoader : public CCNodeLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BuyItemLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BuyItem);
};

#endif
