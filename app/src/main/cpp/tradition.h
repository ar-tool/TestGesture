//
// Created by leon on 17-3-22.
//
#include <jni.h>

#ifndef HISCENEGESTURE_TRADITION_H
#define HISCENEGESTURE_TRADITION_H
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_hiscene_com_hiscenegesture_JNI_tradition_TraditionManager_init
        (JNIEnv *, jobject, jstring);

JNIEXPORT void JNICALL Java_hiscene_com_hiscenegesture_JNI_tradition_TraditionManager_setParam
        (JNIEnv *, jobject , jint, jint);

JNIEXPORT jobject JNICALL Java_hiscene_com_hiscenegesture_JNI_tradition_TraditionManager_detect
        (JNIEnv *, jobject, jbyteArray);

JNIEXPORT void JNICALL Java_hiscene_com_hiscenegesture_JNI_tradition_TraditionManager_destory
        (JNIEnv *, jobject);



#ifdef __cplusplus
}
#endif
#endif //HISCENEGESTURE_TRADITION_H
