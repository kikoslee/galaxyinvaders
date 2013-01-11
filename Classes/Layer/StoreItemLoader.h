#ifndef _StoreItemLoader_H_
#define _StoreItemLoader_H_

#include "StoreItem.h"

class CCBReader;

class StoreItemLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StoreItemLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StoreItem);
};

#endif
