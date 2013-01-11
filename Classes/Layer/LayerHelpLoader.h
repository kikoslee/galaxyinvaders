#ifndef _LayerResultLoader_H_
#define _LayerResultLoader_H_

#include "LayerResult.h"

class CCBReader;

class LayerResultLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerResultLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerResult);
};

#endif
