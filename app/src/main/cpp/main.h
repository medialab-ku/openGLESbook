#ifndef OPENGLES_MAIN_H
#define OPENGLES_MAIN_H

#include "global.h"
#include "utility/asset.h"
#include "utility/input.h"
#include "utility/scene.h"
#include "example/list.h"

extern Scene* scene;

void surfaceCreated(const AAssetManager* aAssetManager, const int id);
void surfaceChanged(const int width, const int height);
void drawFrame(const float deltaTime);
void touchEvent(const int motion, const float x, const float y);

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_surfaceCreated(JNIEnv *env, jobject instance,
                                                            jobject assetManager, jint id) {
    surfaceCreated(AAssetManager_fromJava(env, assetManager), id);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_surfaceChanged(JNIEnv *env, jobject instance,
                                                            jint width, jint height) {
    surfaceChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_drawFrame(JNIEnv *env, jobject instance,
                                                       jfloat deltaTime) {
    drawFrame(deltaTime);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_touchEvent(JNIEnv *env, jobject instance, jint motion,
                                                        jfloat x, jfloat y) {
    touchEvent(motion, x, y);
}

#endif // OPENGLES_MAIN_H
