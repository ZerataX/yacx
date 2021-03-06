/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class yacx_BooleanArg */

#ifndef _Included_yacx_BooleanArg
#define _Included_yacx_BooleanArg
#ifdef __cplusplus
extern "C" {
#endif
#undef yacx_BooleanArg_SIZE_BYTES
#define yacx_BooleanArg_SIZE_BYTES 1LL
/*
 * Class:     yacx_BooleanArg
 * Method:    createValue
 * Signature: (Z)Lyacx/KernelArg;
 */
JNIEXPORT jobject JNICALL Java_yacx_BooleanArg_createValue
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     yacx_BooleanArg
 * Method:    createInternal
 * Signature: ([ZZ)Lyacx/BooleanArg;
 */
JNIEXPORT jobject JNICALL Java_yacx_BooleanArg_createInternal
  (JNIEnv *, jclass, jbooleanArray, jboolean);

/*
 * Class:     yacx_BooleanArg
 * Method:    asBooleanArray
 * Signature: ()[Z
 */
JNIEXPORT jbooleanArray JNICALL Java_yacx_BooleanArg_asBooleanArray
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
