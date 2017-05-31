package com.example.app;

import android.app.Activity;
import android.os.Bundle;
import android.widget.*;

public class Main extends Activity
{

    static {
      System.loadLibrary("myModule");
    }

    public native int invokeNativeFibo(int n);
    public native int invokeCallbackFibo(int n);

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        int param = 9;

        TextView textView1 = (TextView) findViewById(android.R.id.text1);
        TextView textView2 = (TextView) findViewById(android.R.id.text2);
        TextView nativeTimeTextView = (TextView) findViewById(R.id.nativeTimeTextView);
        TextView javaTimeTextView = (TextView) findViewById(R.id.javaTimeTextView);

        long nativeStart = System.nanoTime();
        String text1 = "NATIVE!F(" + param + ") = " + invokeNativeFibo(param);
        long nativeEnd = System.nanoTime();

        long javaStart = System.nanoTime();
        String text2 = "JAVA!F(" + param + ") = " + fibo(param);
        long javaEnd = System.nanoTime();

        textView1.setText(text1);
        textView2.setText(text2);
        nativeTimeTextView.setText("Native call: " + (nativeEnd - nativeStart) / 1000 + " ms");
        javaTimeTextView.setText("Java call: " + (javaEnd - javaStart) / 1000 + " ms");

        int f = invokeCallbackFibo(param);
    }

    public int fibo(int n) {
      return n <= 1 ? n : fibo(n - 1) + fibo(n - 2);
    }

    public void callback(int n) {
      Toast.makeText(this, "CALLBACK: " + n, Toast.LENGTH_SHORT).show();
    }
}
