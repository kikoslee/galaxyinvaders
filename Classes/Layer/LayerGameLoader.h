#ifndef _LayerGameLoader_H_
#define _LayerGameLoader_H_

#include "LayerGame.h"

class CCBReader;

class LayerGameLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerGameLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerGame);
};

#endif
