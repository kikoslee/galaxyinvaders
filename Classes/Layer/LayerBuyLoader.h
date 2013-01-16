#ifndef _LayerBuyLoader_H_
#define _LayerBuyLoader_H_

#include "LayerBuy.h"

class CCBReader;

class LayerBuyLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerBuyLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerBuy);
};

#endif
