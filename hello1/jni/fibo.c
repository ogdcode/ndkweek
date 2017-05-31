#include <jni.h>
#include "com_example_app_Main.h"

int fibonacci(int n) {
  return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

void callMethod(JNIEnv* env, jobject thiz, int val) {
  jclass c = (*env)->GetObjectClass(env, thiz);
  jmethodID mid = (*env)->GetMethodID(env, c, "callback", "(I)V");
  if (mid == 0) {
    return;
  }
  (*env)->CallVoidMethod(env, thiz, mid, val);
}

jint JNICALL Java_com_example_app_Main_invokeNativeFibo
  (JNIEnv * env, jobject obj, jint n) {
  return n <= 1 ?
  n :
  Java_com_example_app_Main_invokeNativeFibo(env, obj, n - 1) +
  Java_com_example_app_Main_invokeNativeFibo(env, obj, n - 2);
}

jint JNICALL Java_com_example_app_Main_invokeCallbackFibo
  (JNIEnv * env, jobject obj, jint n){
  int val = fibonacci(n);
  callMethod(env, obj, val);
  return val;
}
