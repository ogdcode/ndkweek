#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include "com_doctorwho_ood_TheGift.h"

#define LOG_TAG "thegift.c"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

static int compare(const void* a, const void* b) {
  const int* aa = a;
  const int* bb = b;

  return *aa - *bb;
}

static void display(const int* array, const size_t count) {
  size_t i;

  for (i = 0; i < count; ++i) {
    LOGD("%d ", array[i]);
  }
}

void JNICALL Java_com_doctorwho_ood_TheGift_invokeNativeFunction
  (JNIEnv * env, jobject obj, jstring ipt) {
    const char* input = (*env)->GetStringUTFChars(env, ipt, 0);
    int n; // The number of participants.
    int c; // The price of the gift;

    // Read n in input and cut it out.
    sscanf(input, "%d", &n);
    input = strpbrk(input, "\n") + 1;

    // Read c in input and cut it out.
    sscanf(input, "%d", &c);
    input = strpbrk(input, "\n") + 1;

    LOGD("%d Oods gathered to give a gift of cost %d\n", n, c);
    int budgets[n]; // The budgets of all the participants;
    int total = 0; // The total budget of all the participants.
    size_t i;
    for (i = 0; i < n; ++i) {
      int budget; // The budget for each participant, given in input.
      sscanf(input, "%d", &budget);
      input = strpbrk(input, ",") + 1;
      budgets[i] = budget;
      total += budget;
    }

    // If all the participants do not have enough to pay, then do not go further.
    if (total < c) {
      LOGD("All the Oods do not have enough to pay the gift...");
      return;
    }

    // Divide the amount of the gift between each participant.
    // If a participant's budget is less than or equal to the average, then
    //  they give the entirety of their budget.
    // In the case where their budget is inferior, the difference between what
    //  could be paid and the average is added to the average for each remaining
    //  participant.
    // If a participant's budget is greater than the average, then they give
    //  exactly the amount of the average, and eventually a remainder in case
    //  the initial average was not rounded well.
    int average = c / n;
    int remainder = c % n;
    int contributions[n]; // The contributions of each participant are stored here.
    i = 0;
    for (; i < n; ++i) {
      if (budgets[i] <= average) {
        c -= budgets[i];
        contributions[i] = budgets[i];
        if (budgets[i] < average) {
          average += ((average - budgets[i]) / (n - (i + 1)));
        }
        budgets[i] = 0;
      } else {
        c -= average;
        budgets[i] -= average;
        contributions[i] = average;
        if (remainder > 0 && budgets[i] - remainder > 0) {
          c -= remainder;
          budgets[i] -= remainder;
          contributions[i] = average + remainder;
          remainder = 0;
        }
      }
    }

    // Sort remaining budgets and contributions to display them.
    qsort(budgets, sizeof(budgets) / sizeof(*budgets), sizeof(*budgets), compare);
    qsort(contributions, sizeof(contributions) / sizeof(*contributions), sizeof(*contributions), compare);

    LOGD("The remaining budgets of the Oods are:");
    display(budgets, sizeof(budgets) / sizeof(*budgets));

    LOGD("The contributions of each Ood are:");
    display(contributions, sizeof(contributions) / sizeof(*contributions));
}
