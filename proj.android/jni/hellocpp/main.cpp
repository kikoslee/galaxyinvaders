#include "AppDelegate.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#include "HBCommon.h"

#define PACKAGE com_happybluefin_galaxyinvader

const char* projName = "galaxyinvader";

//这里的宏一定要这样定义，才能合成出正确的函数名称
#define NAME3(PACKAGE3, CLASS3, FUNC3) Java_##PACKAGE3##_##CLASS3##_##FUNC3
#define NAME2(PACKAGE2, CLASS2, FUNC2) NAME3(PACKAGE2, CLASS2, FUNC2)
#define NAME(CLASS, FUNC) NAME2(PACKAGE, CLASS, FUNC)

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace cocos2d;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JniHelper::setJavaVM(vm);
    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h) {
    LOGD("nativeInit() start");

    if (!CCDirector::sharedDirector()->getOpenGLView()) {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else {
        ccDrawInit();
        ccGLInvalidateStateCache();
        
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
    LOGD("nativeInit() end");

}

static char* jstringTostring(JNIEnv* env, jstring jstr) {
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");

    jstring strencode = env->NewStringUTF("utf-8");

    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");

    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char*)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }

    env->ReleaseByteArrayElements(barr, ba, 0);

    return rtn;
}

void showLeaderBoard(const char* boardName) {
    LOGD("showLeaderBoard() start");
    
    if (boardName != NULL) {
        LOGD("showLeaderBoard(): boardName: %s", boardName);
        
        JNIEnv* env = NULL;
        JavaVM *vm = NULL;
        int state;
        
        vm = JniHelper::getJavaVM();
        if (vm != NULL) {
            state = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
            if (state < 0) {
                LOGE("showLeaderBoard(): GetEnv() failed");
                LOGD("showLeaderBoard() end");
                return;
            }
            
            char clsName[512];
            sprintf(clsName, "com/happybluefin/%s/%s", projName, projName);
            jclass cls = env->FindClass(clsName);
            if (!cls) {
                LOGE("showLeaderBoard(): FindClass() failed");
                LOGD("showLeaderBoard() end");
                return;
            }
            
            jmethodID showLeaderBoard = env->GetStaticMethodID(cls, "showLeaderBoard", "(Ljava/lang/String;)V");
            if (!showLeaderBoard) {
                LOGE("showLeaderBoard(): GetStaticMethodID() failed");
                LOGD("showLeaderBoard() end");
                return;
            }
            
            jstring param = env->NewStringUTF(boardName);
            env->CallStaticObjectMethod(cls, showLeaderBoard, param);
        }
    }
    else {
        LOGD("showLeaderBoard(): boardName is NULL");
    }
    
    LOGD("showLeaderBoard() end");
}

void reportScore(const char* boardName, int score) {
    LOGD("reportScore() start");
    
    if (boardName != NULL) {
        LOGD("reportScore(): boardName: %s", boardName);
        LOGD("reportScore(): score: %i", score);
        
        JNIEnv* env = NULL;
        JavaVM *vm = NULL;
        int state;
        
        vm = JniHelper::getJavaVM();
        if (vm != NULL) {
            state = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
            if (state < 0) {
                LOGE("reportScore(): GetEnv() failed");
                LOGD("reportScore() end");
                return;
            }
            
            char clsName[512];
            sprintf(clsName, "com/happybluefin/%s/%s", projName, projName);
            jclass cls = env->FindClass(clsName);
            if (!cls) {
                LOGE("reportScore(): FindClass() failed");
                LOGD("reportScore() end");
                return;
            }
            
            jmethodID reportScore = env->GetStaticMethodID(cls, "reportScore", "(Ljava/lang/String;I)V");
            if (!reportScore) {
                LOGE("reportScore(): GetStaticMethodID() failed");
                LOGD("reportScore() end");
                return;
            }
            
            jstring param = env->NewStringUTF(boardName);
            env->CallStaticObjectMethod(cls, reportScore, param, score);
        }
    }
    else {
        LOGD("reportScore(): boardName is NULL");
    }
    
    LOGD("reportScore() end");
}

    
void gotoUrl(const char* url) {
    LOGD("gotoUrl() start");

    if (url != NULL) {
        LOGD("gotoUrl(): url: %s", url);

        JNIEnv* env = NULL;
        JavaVM *vm = NULL;
        int state;

        vm = JniHelper::getJavaVM();
        if (vm != NULL) {
            state = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
            if (state < 0) {
                LOGE("gotoUrl(): GetEnv() failed");
                LOGD("gotoUrl() end");
                return;
            }

            char clsName[512];
            sprintf(clsName, "com/happybluefin/%s/%s", projName, projName);
            jclass cls = env->FindClass(clsName);
            if (!cls) {
                LOGE("gotoUrl(): FindClass() failed");
                LOGD("gotoUrl() end");
                return;
            }

            jmethodID gotoUrl = env->GetStaticMethodID(cls, "gotoUrl", "(Ljava/lang/String;)V");
            if (!gotoUrl) {
                LOGE("gotoUrl(): GetStaticMethodID() failed");
                LOGD("gotoUrl() end");
                return;
            }

            jstring param = env->NewStringUTF(url);
            env->CallStaticObjectMethod(cls, gotoUrl, param);
        }
    }
    else {
        LOGD("gotoUrl(): url is NULL");
    }

    LOGD("gotoUrl() end");
}

void gotoReview() {
    LOGD("gotoReview() start");

    char* ret = NULL;

    JNIEnv* env = NULL;
    JavaVM *vm = NULL;
    int state;

    vm = JniHelper::getJavaVM();
    if (vm != NULL) {
        state = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
        if (state < 0) {
            LOGE("gotoReview(): GetEnv() failed");
            LOGD("gotoReview() end");
        }

        char clsName[512];
        sprintf(clsName, "com/happybluefin/%s/%s", projName, projName);
        jclass cls = env->FindClass(clsName);
        if (!cls) {
            LOGE("gotoReview(): FindClass() failed");
            LOGD("gotoReview() end");
        }

        jmethodID gotoReview = env->GetStaticMethodID(cls, "gotoReview", "()V");
        if (!gotoReview) {
            LOGE("gotoReview(): GetStaticMethodID() failed");
            LOGD("gotoReview() end");
        }

        jstring str = (jstring)env->CallStaticObjectMethod(cls, gotoReview);

        ret = jstringTostring(env, str);
    }

    LOGD("gotoReview() end");
}

void gotoMoreGame()
{	
    LOGD("gotoMoreGame() start");

    char* ret = NULL;

    JNIEnv* env = NULL;
    JavaVM *vm = NULL;
    int state;

    vm = JniHelper::getJavaVM();
    if (vm != NULL) {
        state = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
        if (state < 0) {
            LOGE("gotoMoreGame(): GetEnv() failed");
            LOGD("gotoMoreGame() end");
        }

        char clsName[512];
        sprintf(clsName, "com/happybluefin/%s/%s", projName, projName);
        jclass cls = env->FindClass(clsName);
        if (!cls) {
            LOGE("gotoMoreGame(): FindClass() failed");
            LOGD("gotoMoreGame() end");
        }

        jmethodID gotoMoreGame = env->GetStaticMethodID(cls, "gotoMoreGame", "()V");
        if (!gotoReview) {
            LOGE("gotoMoreGame(): GetStaticMethodID() failed");
            LOGD("gotoMoreGame() end");
        }

        jstring str = (jstring)env->CallStaticObjectMethod(cls, gotoMoreGame);

        ret = jstringTostring(env, str);
    }

    LOGD("gotoMoreGame() end");
}

int umengGetParamValue(const char* name) {
    LOGD("umengGetParamValue() start");

    int ret = 0;

    if (name != NULL) {
        LOGD("umengGetParamValue(): name: %s", name);

        JNIEnv* env = NULL;
        JavaVM *vm = NULL;
        int state;

        vm = JniHelper::getJavaVM();
        if (vm != NULL) {
            state = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
            if (state < 0) {
                LOGE("umengGetParamValue(): GetEnv() failed");
                LOGD("umengGetParamValue() end");
                return ret;
            }

            char clsName[512];
            sprintf(clsName, "com/happybluefin/%s/%s", projName, projName);
            jclass cls = env->FindClass(clsName);
            if (!cls) {
                LOGE("umengumengGetParamValue(): FindClass() failed");
                LOGD("umengGetParamValue() end");
                return ret;
            }

            jmethodID getParamValue = env->GetStaticMethodID(cls, "umengGetParamValue", "(Ljava/lang/String;)I");
            if (!getParamValue) {
                LOGE("umengGetParamValue(): GetStaticMethodID() failed");
                LOGD("umengGetParamValue() end");
                return ret;
            }

            jstring param = env->NewStringUTF(name);
            ret = (int)env->CallStaticObjectMethod(cls, getParamValue, param);

            LOGD("umengGetParamValue(): %s is %i", name, ret);
        }
    }
    else {
        LOGD("umengGetParamValue(): name is NULL");
    }

    LOGD("umengGetParamValue() end");

    return ret;
}

void umengCustomEvent(const char* name, const char* value) {
    LOGD("umengCustomEvent() start");

    if ((name != NULL) && (value != NULL)) {
        LOGD("umengCustomEvent(): name: %s", name);
        LOGD("umengCustomEvent(): value: %s", value);

        JNIEnv* env = NULL;
        JavaVM *vm = NULL;
        int state;

        vm = JniHelper::getJavaVM();
        if (vm != NULL) {
            state = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
            if (state < 0) {
                LOGE("umengCustomEvent(): GetEnv() failed");
                LOGD("umengCustomEvent() end");
                return;
            }

            char clsName[512];
            sprintf(clsName, "com/happybluefin/%s/%s", projName, projName);
            jclass cls = env->FindClass(clsName);
            if (!cls) {
                LOGE("umengCustomEvent(): FindClass() failed");
                LOGD("umengCustomEvent() end");
                return;
            }

            jmethodID customEvent = env->GetStaticMethodID(cls, "umengCustomEvent", "(Ljava/lang/String;Ljava/lang/String;)V");
            if (!customEvent) {
                LOGE("umengCustomEvent(): GetStaticMethodID() failed");
                LOGD("umengCustomEvent() end");
                return;
            }

            jstring param1 = env->NewStringUTF(name);
            jstring param2 = env->NewStringUTF(value);
            env->CallStaticObjectMethod(cls, customEvent, param1, param2);
        }
    }
    else {
        LOGD("umengCustomEvent(): name or value is NULL");
    }

    LOGD("umengCustomEvent() end");
}

//获取语言
jint NAME(galaxyinvader, nativeSetLang)(JNIEnv *env, jobject thiz, jstring a)
{
	char* re ;
	re = jstringTostring(env , a);

	sprintf(HBDeviceLanguage, "%s", re);

	LOGD("*****nativeSetLang****%s", re);
	LOGD("nativeSetLang :%s", HBDeviceLanguage );

	return 1;
}

//获取Admob ID
jstring NAME(galaxyinvader, getAdmobUnitID)(JNIEnv *env, jclass cls) {
    jstring ret = env->NewStringUTF("a150fd5d99ee617");
    return ret;
}

}
