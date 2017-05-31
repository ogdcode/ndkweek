#include <jni.h>
#include <string.h>
#include <android/log.h>
#include "com_example_app_DoctorWho.h"

#define LOG_TAG "doctorwho.c"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

jstring JNICALL Java_com_example_app_DoctorWho_invokeNativeFunction
  (JNIEnv * env, jobject obj) {
    int n, c;
    char* budgets[n];
    const char* pb;
    sscanf(pb, "%d", &n);
    pb = strpbrk(pb, "\n") + 1;
    sscanf(pb, "%d", &c);
    pb = strpbrk(pb, "\n") + 1;

    int i = 0;
    for (; i < n; ++i) {
      char* budget;
      pb = sscanf(pb, "%s", budget);
      pb = strpbrk(pb, "\n") + 1;
      budgets[i] = budget;
      LOGD("budget of participant %d is %s", i, budget);
    }
  }
