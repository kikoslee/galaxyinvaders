#ifndef _TotalGoldLoader_H_
#define _TotalGoldLoader_H_

#include "TotalGold.h"

class CCBReader;

class TotalGoldLoader : public CCNodeLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TotalGoldLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TotalGold);
};

#endif
