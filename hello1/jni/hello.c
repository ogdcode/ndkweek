#include <string.h>
#include <jni.h>

jstring Java_com_example_app_Main_invokeNativeFunction( JNIEnv* env, jobject thiz ) {
  return (*env)->NewStringUTF(env, "HELLO FROM NDK");
}
