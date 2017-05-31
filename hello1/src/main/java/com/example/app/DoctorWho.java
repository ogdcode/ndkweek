package com.example.app;

import java.util.*;

import android.widget.*;

public class DoctorWho extends Activity {

    private ListView mList;

    public native String invokeNativeFunction();

    static {
      System.loadLibrary("whovianModule");
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.doctorwho);

      int n, c;
      String budgets;
      invokeNativeFunction(n, c, budgets);
      String[] results = parts.split(",");

      mList = (ListView) findViewById(android.R.id.list);
      ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, Arrays.asList(results));
      mList.setAdapter(adapter);
    }
}
