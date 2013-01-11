#ifndef _LayerStoreLoader_H_
#define _LayerStoreLoader_H_

#include "LayerStore.h"

class CCBReader;

class LayerStoreLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerStoreLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerStore);
};

#endif
