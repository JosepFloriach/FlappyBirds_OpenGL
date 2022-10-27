package com.example.josep.zeptolabtest;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class FlappyBirdActivity extends TestActivity {
    private GameSurfaceView mSurfaceView = null;
    private native void CreateFlappyBirdsParams(float playerJumpForce,
                                                float scenarySpeed,
                                                float pipeSpawnMaxFreq,
                                                float pipeSpawnMinFreq,
                                                float pipeGapMaxDistance,
                                                float pipeGapMinDistance,
                                                float pipeWidth,
                                                float nextPipeYOffset);
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.flappy_birds_scene);

        String sceneName = "FlappyBirds";

        mSurfaceView = findViewById(R.id.surface_view);
        mSurfaceView.SetName(sceneName);
        mSurfaceView.InitOpenGlContext();

        // Load flappy birds game params.
        Intent intent = getIntent();
        float scenarySpeed = intent.getFloatExtra(
                GameMainActivity.INTENT_EXTRA_NAME_SCENARY_MOVE_SPEED, 0.f);
        float playerJumpForce = intent.getFloatExtra(
                GameMainActivity.INTENT_EXTRA_NAME_JUMP_FORCE, 0.f);
        float pipeSpawnMaxFreq = intent.getFloatExtra(
                GameMainActivity.INTENT_EXTRA_NAME_PIPE_SPAWN_MAX_FREQ, 0.f);
        float pipeSpawnMinFreq = intent.getFloatExtra(
                GameMainActivity.INTENT_EXTRA_NAME_PIPE_SPAWN_MIN_FREQ, 0.f);
        float pipeGapMaxDistance = intent.getFloatExtra(
                GameMainActivity.INTENT_EXTRA_NAME_PIPE_GAP_MAX_DISTANCE, 0.f);
        float pipeGapMinDistance = intent.getFloatExtra(
                GameMainActivity.INTENT_EXTRA_NAME_PIPE_GAP_MIN_DISTANCE, 0.f);
        float pipeWidth = intent.getFloatExtra(
                GameMainActivity.INTENT_EXTRA_NAME_PIPE_WIDTH, 0.f);
        float nextPipeYOffset = intent.getFloatExtra(
                GameMainActivity.INTENT_EXTRA_NAME_NEXT_PIPE_Y_OFFSET, 0.f);

        CreateFlappyBirdsParams(
                playerJumpForce,
                scenarySpeed,
                pipeSpawnMaxFreq,
                pipeSpawnMinFreq,
                pipeGapMaxDistance,
                pipeGapMinDistance,
                pipeWidth,
                nextPipeYOffset);
    }
}
