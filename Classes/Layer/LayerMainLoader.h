#ifndef _LayerMainLoader_H_
#define _LayerMainLoader_H_

#include "LayerMain.h"

class CCBReader;

class LayerMainLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerMainLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerMain);
};

#endif
