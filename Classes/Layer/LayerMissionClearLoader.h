#ifndef _LayerMissionClearLoader_H_
#define _LayerMissionClearLoader_H_

#include "LayerMissionClear.h"

class CCBReader;

class LayerMissionClearLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerMissionClearLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerMissionClear);
};

#endif
