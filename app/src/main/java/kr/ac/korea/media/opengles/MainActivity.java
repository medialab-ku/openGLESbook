package kr.ac.korea.media.opengles;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends Activity {

    // Used to load the 'opengles' library on application startup.
    static {
        System.loadLibrary("opengles");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // set content view to OpenGL ES surface view
        setContentView(new SurfaceView(this));
    }

    /**
     * A native method that is implemented by the 'opengles' native library,
     * which is packaged with this application.
     */
    public native void surfaceCreated(AssetManager assetManager, int id);
    public native void surfaceChanged(int width, int height);
    public native void drawFrame(float deltaTime);
    public native void touchEvent(int motion, float x, float y);

    private class SurfaceRenderer implements GLSurfaceView.Renderer {

        // define last time
        private long lastTime = System.currentTimeMillis();

        @Override
        public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
            // call native method with asset manager and example ID
            surfaceCreated(getAssets(), getIntent().getIntExtra("ExampleID", -1));
        }

        @Override
        public void onSurfaceChanged(GL10 gl10, int width, int height) {
            // call native method
            surfaceChanged(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl10) {
            // get current time
            long currentTime = System.currentTimeMillis();

            // compute delta time
            float deltaTime = (float) (currentTime - lastTime) / 1000.0f;

            // call native method
            drawFrame(deltaTime);

            // update last time
            lastTime = currentTime;
        }
    }

    private class SurfaceView extends GLSurfaceView {

        public SurfaceView(Context context) {
            super(context);

            // set context client version to 3.x
            setEGLContextClientVersion(3);

            // set surface renderer
            setRenderer(new SurfaceRenderer());
        }

        @Override
        public boolean onTouchEvent(MotionEvent event) {
            // get action and call native method accordingly
            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    touchEvent(0, event.getX(), event.getY());
                    break;
                case MotionEvent.ACTION_MOVE:
                    touchEvent(1, event.getX(), event.getY());
                    break;
                case MotionEvent.ACTION_UP:
                    touchEvent(2, event.getX(), event.getY());
                    break;
            }

            // return true
            return true;
        }
    }
}
