/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class Device */

#ifndef _Included_Device
#define _Included_Device
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     Device
 * Method:    createDevice
 * Signature: ()LDevice;
 */
JNIEXPORT jobject JNICALL Java_Device_createDevice
  (JNIEnv *, jclass);

/*
 * Class:     Device
 * Method:    createDeviceInternal
 * Signature: (Ljava/lang/String;)LDevice;
 */
JNIEXPORT jobject JNICALL Java_Device_createDeviceInternal
  (JNIEnv *, jclass, jstring);

/*
 * Class:     Device
 * Method:    getName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Device_getName
  (JNIEnv *, jobject);

/*
 * Class:     Device
 * Method:    getMemorySize
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_Device_getMemorySize
  (JNIEnv *, jobject);

/*
 * Class:     Device
 * Method:    getMaxBlock
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_Device_getMaxBlock
  (JNIEnv *, jobject);

/*
 * Class:     Device
 * Method:    getMaxGrid
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_Device_getMaxGrid
  (JNIEnv *, jobject);

/*
 * Class:     Device
 * Method:    getMultiprocessorCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_Device_getMultiprocessorCount
  (JNIEnv *, jobject);

/*
 * Class:     Device
 * Method:    getClockRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_Device_getClockRate
  (JNIEnv *, jobject);

/*
 * Class:     Device
 * Method:    getMemoryClockRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_Device_getMemoryClockRate
  (JNIEnv *, jobject);

/*
 * Class:     Device
 * Method:    getBusWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_Device_getBusWidth
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif