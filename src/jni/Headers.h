/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class Headers */

#ifndef _Included_Headers
#define _Included_Headers
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     Headers
 * Method:    createHeaders
 * Signature: ()LHeaders;
 */
JNIEXPORT jobject JNICALL Java_Headers_createHeaders
  (JNIEnv *, jclass);

/*
 * Class:     Headers
 * Method:    insertInternal
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_Headers_insertInternal
  (JNIEnv *, jobject, jobjectArray);

/*
 * Class:     Headers
 * Method:    getSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_Headers_getSize
  (JNIEnv *, jobject);

/*
 * Class:     Headers
 * Method:    names
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_Headers_names
  (JNIEnv *, jobject);

/*
 * Class:     Headers
 * Method:    content
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_Headers_content
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif