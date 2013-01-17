#ifndef _DlgReviewLoader_H_
#define _DlgReviewLoader_H_

#include "DlgReview.h"

class CCBReader;

class DlgReviewLoader : public CCLayerLoader
{
    public:
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DlgReviewLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(DlgReview);
};

#endif
