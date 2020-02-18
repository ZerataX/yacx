/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class yacx_Device */

#ifndef _Included_yacx_Device
#define _Included_yacx_Device
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     yacx_Device
 * Method:    createDevice
 * Signature: ()Lyacx/Device;
 */
JNIEXPORT jobject JNICALL Java_yacx_Device_createDevice
  (JNIEnv *, jclass);

/*
 * Class:     yacx_Device
 * Method:    createDeviceInternal
 * Signature: (Ljava/lang/String;)Lyacx/Device;
 */
JNIEXPORT jobject JNICALL Java_yacx_Device_createDeviceInternal
  (JNIEnv *, jclass, jstring);

/*
 * Class:     yacx_Device
 * Method:    getName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_yacx_Device_getName
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getMemorySize
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_yacx_Device_getMemorySize
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getMaxBlock
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_yacx_Device_getMaxBlock
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getMaxGrid
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_yacx_Device_getMaxGrid
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getMultiprocessorCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_yacx_Device_getMultiprocessorCount
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getClockRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_yacx_Device_getClockRate
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getMemoryClockRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_yacx_Device_getMemoryClockRate
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getBusWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_yacx_Device_getBusWidth
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getMinorVersion
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_yacx_Device_getMinorVersion
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Device
 * Method:    getMajorVersion
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_yacx_Device_getMajorVersion
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
