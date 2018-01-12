package kr.ac.korea.media.opengles;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;

public class ListActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);

        try {
            // get list view
            ListView listView = findViewById(R.id.example_list);

            // get json object from asset
            JSONObject jsonObject = readJSONFromAsset("list");
            if (jsonObject == null) return;

            // get json array example list
            JSONArray examples = jsonObject.getJSONArray("examples");

            // set adapter of list view
            listView.setAdapter(new ListAdapter(getApplicationContext(), examples));

            // set listener of list view
            listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
                @Override
                public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                    // create intent with extra example ID
                    Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                    intent.putExtra("ExampleID", i);

                    // start main activity
                    getApplicationContext().startActivity(intent);
                }
            });
        } catch (JSONException e) {
            // print error log
            Log.e("OpenGL ES 3.0", "Fail to get examples from JSON object");
            e.printStackTrace();
        }
    }

    private JSONObject readJSONFromAsset(String filename) {
        try {
            // read file from asset
            InputStream inputStream = getAssets().open(filename + ".json");
            int size = inputStream.available();
            byte[] buffer = new byte[size];
            inputStream.read(buffer);
            inputStream.close();

            // create and return json object
            return new JSONObject(new String(buffer, "UTF-8"));
        } catch (IOException | JSONException e) {
            // print error log
            Log.e("OpenGL ES 3.0", "Fail to read JSON from asset");
            e.printStackTrace();

            // return null
            return null;
        }
    }

    private class ListAdapter extends BaseAdapter {
        private JSONArray examples = null;
        private LayoutInflater inflater = null;

        ListAdapter(Context context, JSONArray examples) {
            // set example list and inflater
            this.examples = examples;
            this.inflater = LayoutInflater.from(context);
        }

        @Override
        public int getCount() {
            // return length of example list
            return examples.length();
        }

        @Override
        public Object getItem(int i) {
            // return null
            return null;
        }

        @Override
        public long getItemId(int i) {
            // return zero
            return 0;
        }

        @SuppressLint({"ViewHolder", "InflateParams"})
        @Override
        public View getView(int i, View view, ViewGroup viewGroup) {
            // get views
            view = inflater.inflate(R.layout.list_item, null);
            TextView title = view.findViewById(R.id.title);
            TextView desc = view.findViewById(R.id.desc);

            try {
                // get example json object
                JSONObject jsonObject = examples.getJSONObject(i);

                // set title and description
                title.setText(jsonObject.getString("title"));
                desc.setText(jsonObject.getString("desc"));
            } catch (JSONException e) {
                // print error log
                Log.e("OpenGL ES 3.0", "Fail to get JSON object from examples");
                e.printStackTrace();
            }

            // return view
            return view;
        }
    }
}
