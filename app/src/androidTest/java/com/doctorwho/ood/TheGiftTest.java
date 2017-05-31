package com.doctorwho.ood;

import android.test.ActivityInstrumentationTestCase2;

/**
 * This is a simple framework for a test of an Application.  See
 * {@link android.test.ApplicationTestCase ApplicationTestCase} for more information on
 * how to write and extend Application tests.
 * <p/>
 * To run this test, you can type:
 * adb shell am instrument -w \
 * -e class com.doctorwho.ood.TheGiftTest \
 * com.doctorwho.ood.tests/android.test.InstrumentationTestRunner
 */
public class TheGiftTest extends ActivityInstrumentationTestCase2<TheGift> {

    public TheGiftTest() {
        super("com.doctorwho.ood", TheGift.class);
    }

}
