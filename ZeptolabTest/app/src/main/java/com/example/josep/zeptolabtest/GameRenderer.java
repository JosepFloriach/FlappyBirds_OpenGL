package com.example.josep.zeptolabtest;

import android.content.res.Resources;
import android.opengl.GLSurfaceView;
import android.util.DisplayMetrics;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;


public class GameRenderer implements GLSurfaceView.Renderer {

    private native void DrawFrame();
    private native void CreateGame(String sceneName, int displayWidth, int displayHeight);
    private String mSceneName;

    GameRenderer(String sceneName){
        mSceneName = sceneName;
    }

    public void onDrawFrame(GL10 gl) {
        DrawFrame();
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config){
        DisplayMetrics metrics = Resources.getSystem().getDisplayMetrics();
        int width = metrics.widthPixels;
        int height = metrics.heightPixels;
        CreateGame(mSceneName, width, height);
    }

    public void onSurfaceChanged(GL10 gl, int width, int height){
    }
}
