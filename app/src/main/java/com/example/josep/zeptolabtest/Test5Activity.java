package com.example.josep.zeptolabtest;

import android.app.Activity;
import android.os.Bundle;

public class Test5Activity extends TestActivity {

    private GameSurfaceView mSurfaceView = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.test5_scene);

        String sceneName = "Test5";

        mSurfaceView = findViewById(R.id.surface_view);
        mSurfaceView.SetName(sceneName);
        mSurfaceView.InitOpenGlContext();
    }
}
