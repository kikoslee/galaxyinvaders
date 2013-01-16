#ifndef _LayerHelpLoader_H_
#define _LayerHelpLoader_H_

#include "LayerHelp.h"

class CCBReader;

class LayerHelpLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LayerHelpLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LayerHelp);
};

#endif
