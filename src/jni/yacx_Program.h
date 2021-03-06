/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class yacx_Program */

#ifndef _Included_yacx_Program
#define _Included_yacx_Program
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     yacx_Program
 * Method:    createInternal
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Lyacx/Program;
 */
JNIEXPORT jobject JNICALL Java_yacx_Program_createInternal__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     yacx_Program
 * Method:    createInternal
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lyacx/Headers;)Lyacx/Program;
 */
JNIEXPORT jobject JNICALL Java_yacx_Program_createInternal__Ljava_lang_String_2Ljava_lang_String_2Lyacx_Headers_2
  (JNIEnv *, jclass, jstring, jstring, jobject);

/*
 * Class:     yacx_Program
 * Method:    instantiateInternal
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_yacx_Program_instantiateInternal
  (JNIEnv *, jobject, jstring);

/*
 * Class:     yacx_Program
 * Method:    compile
 * Signature: ()Lyacx/Kernel;
 */
JNIEXPORT jobject JNICALL Java_yacx_Program_compile
  (JNIEnv *, jobject);

/*
 * Class:     yacx_Program
 * Method:    compileInternal
 * Signature: (Lyacx/Options;)Lyacx/Kernel;
 */
JNIEXPORT jobject JNICALL Java_yacx_Program_compileInternal
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
