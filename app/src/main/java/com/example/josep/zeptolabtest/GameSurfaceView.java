package com.example.josep.zeptolabtest;

import android.opengl.GLException;
import android.opengl.GLSurfaceView;
import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;

public class GameSurfaceView extends GLSurfaceView {

    private native void OnTouch(float xPosition, float yPosition);

    // Renderer
    private GameRenderer mRenderer;
    private String mSceneName;
    /**
     * Constructor.
     * @param context
     */
    public GameSurfaceView(Context context, AttributeSet atts) {
       super(context, atts);
    }

    public void InitOpenGlContext(){
        try {
            // Setup of OpenGL context. Version, renderer, and render mode.
            super.setEGLConfigChooser(true);
            setEGLContextClientVersion(2);
            setEGLConfigChooser(8 , 8, 8, 8, 16, 4);
            mRenderer = new GameRenderer(mSceneName);
            setRenderer(mRenderer);
            setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
        }
        catch(GLException e) {
            Log.e("GameSurfaceView", "Could not create OpenGL context.", e);
        }
    }

    public void SetName(String sceneName){
        mSceneName = sceneName;
    }

    public boolean onTouchEvent(MotionEvent e) {
        float x = e.getX();
        float y = e.getY();

        if (e.getAction()==MotionEvent.ACTION_DOWN){
            OnTouch(x, y);
        }

        return true;
    }
}
