#include "tradition.h"
#include "HiarSiFunction.h"
#include "HiarSiTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int image_height;
int image_width;

jobject HiarDectect(JNIEnv * env, const HiarSiImage* image)
{
    // get the result
    process_image(image);
    std::vector<HiarSiRect> bHeadCount = getHeadCountBox();
    std::vector<HiarSiRect> bHand = getHandBox();
    int headCount_size = bHeadCount.size();
    int hand_size = bHand.size();

    // create the return Object
    jclass event_cls = env->FindClass("hiscene/com/hiscenegesture/base/HisceneEvent");
    jmethodID event_construct = env->GetMethodID(event_cls, "<init>", "()V");
    jobject eventObject = env->NewObject(event_cls,event_construct);

    // arrayList
    jclass list_cls = env->FindClass("java/util/ArrayList");
    jmethodID list_construct = env->GetMethodID(list_cls,"<init>","()V");
    jobject list_head = env->NewObject(list_cls,list_construct);
    jobject list_hand = env->NewObject(list_cls,list_construct);
    jmethodID list_add = env->GetMethodID(list_cls, "add", "(Ljava/lang/Object;)Z");

    // basebox
    jclass basebox_cls = env->FindClass("hiscene/com/hiscenegesture/base/BaseBox");
    jmethodID basebox_construct=env->GetMethodID(basebox_cls, "<init>", "()V");

    // setting the HeadCount list
    for(int i = 0; i < headCount_size; ++i)
    {
        jobject box = env->NewObject(basebox_cls,basebox_construct);
        jfieldID x= env->GetFieldID(basebox_cls,"m_x","I");
        jfieldID y= env->GetFieldID(basebox_cls,"m_y","I");
        jfieldID height= env->GetFieldID(basebox_cls,"m_height","I");
        jfieldID width= env->GetFieldID(basebox_cls,"m_width","I");
        env->SetIntField(box,x,bHeadCount[i].x);
        env->SetIntField(box,y,bHeadCount[i].y);
        env->SetIntField(box,height,bHeadCount[i].height);
        env->SetIntField(box,width,bHeadCount[i].width);
        env->CallBooleanMethod(list_head,list_add,box);
    }
    // setting the handCount list
    for (int i = 0; i < hand_size; ++i)
    {
        jobject box = env->NewObject(basebox_cls,basebox_construct);
        jfieldID x= env->GetFieldID(basebox_cls,"m_x","I");
        jfieldID y= env->GetFieldID(basebox_cls,"m_y","I");
        jfieldID height= env->GetFieldID(basebox_cls,"m_height","I");
        jfieldID width= env->GetFieldID(basebox_cls,"m_width","I");
        env->SetIntField(box,x,bHand[i].x);
        env->SetIntField(box,y,bHand[i].y);
        env->SetIntField(box,height,bHand[i].height);
        env->SetIntField(box,width,bHand[i].width);
        // add the object to the arrayList
        env->CallBooleanMethod(list_hand,list_add,box);
    }
    // setting the event field
    jfieldID headlist = env->GetFieldID(event_cls,"m_HeadList","java/util/ArrayList");
    jfieldID handlist = env->GetFieldID(event_cls,"m_HandList","java/util/ArrayList");
    env->SetObjectField(eventObject,headlist,list_head);
    env->SetObjectField(eventObject,handlist,list_hand);

    return eventObject;
}

JNIEXPORT void JNICALL Java_hiscene_com_hiscenegesture_JNI_tradition_TraditionManager_init
        (JNIEnv *env, jobject thiz, jstring assetFolder)
{
    init_HiarSi();
}

JNIEXPORT void JNICALL Java_hiscene_com_hiscenegesture_JNI_tradition_TraditionManager_setParam
        (JNIEnv *env, jobject thiz, jint height, jint width)
{
    image_height = height;
    image_width = width;
}

JNIEXPORT void JNICALL Java_hiscene_com_hiscenegesture_JNI_tradition_TraditionManager_destory
        (JNIEnv *env, jobject thiz)
{
    exit_HiarSi();
}

JNIEXPORT jobject JNICALL Java_hiscene_com_hiscenegesture_JNI_tradition_TraditionManager_detect
        (JNIEnv *env, jobject thiz, jbyteArray data)
{
    jboolean isCopy = JNI_FALSE;
    jbyte *buff = env->GetByteArrayElements(data, &isCopy);
    HiarSiImage   image;
    image.width = image_width;
    image.height= image_height;
    image.data = (unsigned char *)buff;
    image.type = HiarSiImageType::HIARSI_IMAGE_TYPE_NV21;
    image.stride = image_width;
    timeval time;
    jobject event = HiarDectect(env,&image);
    env->ReleaseByteArrayElements(data, buff, JNI_ABORT);
    return event;
}