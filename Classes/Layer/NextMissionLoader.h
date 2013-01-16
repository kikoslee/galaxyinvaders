#ifndef _NextMissionLoader_H_
#define _NextMissionLoader_H_

#include "NextMission.h"

class CCBReader;

class NextMissionLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(NextMissionLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(NextMission);
};

#endif
