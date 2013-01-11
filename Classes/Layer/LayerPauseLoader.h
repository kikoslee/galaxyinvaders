#ifndef _LayerPauseLoader_H_
#define _LayerPauseLoader_H_

#include "LayerPause.h"

class CCBReader;

class LayerPauseLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerPauseLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerPause);
};

#endif
