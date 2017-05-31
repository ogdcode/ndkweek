package com.doctorwho.ood;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class TheGift extends Activity
{
    static {
      System.loadLibrary("whosModule");
    }

    public native void invokeNativeFunction(String input);

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        invokeNativeFunction("3\n100\n3,100,100");
    }
}
