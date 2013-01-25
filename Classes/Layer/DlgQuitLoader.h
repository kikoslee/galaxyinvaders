#ifndef _DlgQuitLoader_H_
#define _DlgQuitLoader_H_

#include "DlgQuit.h"

class CCBReader;

class DlgQuitLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DlgQuitLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(DlgQuit);
};

#endif
