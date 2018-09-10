package com.example.josep.zeptolabtest;

import android.content.Intent;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

public class GameMainActivity extends Activity {

    // Default values for flappy birds parameters
    static float DEFAULT_JUMP_FORCE             = 1600;
    static float DEFAULT_MOVE_SPEED             = 700.f;
    static float DEFAULT_PIPE_SPAWN_MAX_FREQ    = 1.7f;
    static float DEFAULT_PIPE_SPAWN_MIN_FREQ    = 1.1f;
    static float DEFAULT_PIPE_MAX_GAP_DISTANCE  = 500.f;
    static float DEFAULT_PIPE_MIN_GAP_DISTANCE  = 350.f;
    static float DEFAULT_PIPE_WIDTH             = 300.f;
    static float DEFAULT_NEXT_PIPE_Y_OFFSET     = 700.f;

    // Max and min values for each parameter.
    static float MAX_JUMP_FORCE             = 5000.f;
    static float MIN_JUMP_FORCE             = 50.f;
    static float MAX_SCENARY_MOVE_SPEED     = 1500.f;
    static float MIN_SCENARY_MOVE_SPEED     = 100.f;
    static float MAX_MAX_PIPE_SPAWN_FREQ    = 3.f;
    static float MIN_MAX_PIPE_SPAWN_FREQ    = 0.5f;
    static float MAX_MIN_PIPE_SPAWN_FREQ    = 2.0f;
    static float MIN_MIN_PIPE_SPAWN_FREQ    = 0.5f;
    static float MIN_PIPE_MAX_GAP_DISTANCE  = 100.f;
    static float MAX_PIPE_MAX_GAP_DISTANCE  = 800.f;
    static float MIN_PIPE_MIN_GAP_DISTANCE  = 100.f;
    static float MAX_PIPE_MIN_GAP_DISTANCE  = 500.f;
    static float MAX_PIPE_WIDTH             = 1000.f;
    static float MIN_PIPE_WIDTH             = 50.f;
    static float MAX_NEXT_PIPE_Y_OFFSET     = 1200.f;
    static float MIN_NEXT_PIPE_Y_OFFSET     = 0.f;

    // Intent names.
    static String INTENT_EXTRA_NAME_SCENARY_MOVE_SPEED      = "ScenaryMoveSpeed";
    static String INTENT_EXTRA_NAME_JUMP_FORCE              = "PlayerJumpForce";
    static String INTENT_EXTRA_NAME_PIPE_SPAWN_MAX_FREQ     = "PipeSpawnMaxFreq";
    static String INTENT_EXTRA_NAME_PIPE_SPAWN_MIN_FREQ     = "PipeSpawnMinFreq";
    static String INTENT_EXTRA_NAME_PIPE_GAP_MAX_DISTANCE   = "PipeMaxGapDistance";
    static String INTENT_EXTRA_NAME_PIPE_GAP_MIN_DISTANCE   = "PipeMinGapDistance";
    static String INTENT_EXTRA_NAME_PIPE_WIDTH              = "PipeWidth";
    static String INTENT_EXTRA_NAME_NEXT_PIPE_Y_OFFSET      = "NextPipeYOffset";

    // Layout components.
    SeekBar mSbPlayerJumpForce;
    SeekBar mSbScenaryMoveSpeed;
    SeekBar mSbPipeSpawnFreqMax;
    SeekBar mSbPipeSpawnFreqMin;
    SeekBar mSbPipeGapDistanceMax;
    SeekBar mSbPipeGapDistanceMin;
    SeekBar mSbPipeWidth;
    SeekBar mSbNextPipeYOffset;
    TextView tvPlayerJumpForce;
    TextView tvScenaryMoveSpeed;
    TextView tvPipeSpawnFreqMax;
    TextView tvPipeSpawnFreqMin;
    TextView tvPipeGapDistanceMax;
    TextView tvPipeGapDistanceMin;
    TextView tvPipeWidth;
    TextView tvNextPipeYOffset;

    // NDK library.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.game_main_activity);

        // Init all layout components.
        InitSceneButtons();
        InitSeekBarJumpForce();
        InitSeekBarScenaryMoveSpeed();
        InitSeekBarPipeSpawnFreqMax();
        InitSeekBarPipeSpawnFreqMin();
        InitSeekBarPipeMaxDistance();
        InitSeekBarPipeMinDistance();
        InitSeekBarPipeWidth();
        InitSeekBarNextPipeYOffset();
    }

    private void InitSceneButtons(){
        final Button bTestGraphics1 = findViewById(R.id.b_test_graphics1);
        bTestGraphics1.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                try {
                    ChangeToActivity("Test1");
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        final Button bTestPhysics1 = findViewById(R.id.b_test_physics1);
        bTestPhysics1.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                try {
                    ChangeToActivity("Test2");
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        final Button bTestPhysics2 = findViewById(R.id.b_test_physics2);
        bTestPhysics2.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                try {
                    ChangeToActivity("Test3");
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        final Button bTestGraphics2 = findViewById(R.id.b_test_graphics2);
        bTestGraphics2.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                try{
                    ChangeToActivity("Test4");
                } catch (Exception e){
                    e.printStackTrace();
                }
            }
        });

        final Button bTestScene1 = findViewById(R.id.b_test_scene1);
        bTestScene1.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                try{
                    ChangeToActivity("Test5");
                } catch (Exception e){
                    e.printStackTrace();
                }
            }
        });

        final Button bFlappyBirds = findViewById(R.id.b_flappy_birds);
        bFlappyBirds.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                try {
                    ChangeToActivity("FlappyBirds");
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    private void InitSeekBarJumpForce() {
        mSbPlayerJumpForce = findViewById(R.id.sb_player_jump_force);
        tvPlayerJumpForce = findViewById(R.id.tv_player_jump_force_value);
        mSbPlayerJumpForce.setMax((int) MAX_JUMP_FORCE - (int) MIN_JUMP_FORCE);
        mSbPlayerJumpForce.setProgress((int) DEFAULT_JUMP_FORCE  - (int) MIN_JUMP_FORCE);
        tvPlayerJumpForce.setText(Float.toString(GetSelectedJumpForce()));
        mSbPlayerJumpForce.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                tvPlayerJumpForce.setText(Float.toString(GetSelectedJumpForce()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void InitSeekBarScenaryMoveSpeed(){
        mSbScenaryMoveSpeed = findViewById(R.id.sb_move_speed);
        tvScenaryMoveSpeed = findViewById(R.id.tv_move_speed_value);
        mSbScenaryMoveSpeed.setMax((int) MAX_SCENARY_MOVE_SPEED - (int) MIN_SCENARY_MOVE_SPEED);
        mSbScenaryMoveSpeed.setProgress((int) DEFAULT_MOVE_SPEED - (int) MIN_SCENARY_MOVE_SPEED);
        tvScenaryMoveSpeed.setText(Float.toString(GetSelectedMoveSpeed()));
        mSbScenaryMoveSpeed.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                tvScenaryMoveSpeed.setText(Float.toString(GetSelectedMoveSpeed()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void InitSeekBarPipeSpawnFreqMax(){
        mSbPipeSpawnFreqMax = findViewById(R.id.sb_pipe_spawn_max_freq);
        tvPipeSpawnFreqMax = findViewById(R.id.tv_pipe_spawn_max_freq_value);
        mSbPipeSpawnFreqMax.setMax((int) (MAX_MAX_PIPE_SPAWN_FREQ * 1000) -
                (int) (MIN_MAX_PIPE_SPAWN_FREQ * 1000));
        mSbPipeSpawnFreqMax.setProgress((int) (DEFAULT_PIPE_SPAWN_MAX_FREQ * 1000) -
                (int) (MIN_MAX_PIPE_SPAWN_FREQ * 1000));
        tvPipeSpawnFreqMax.setText(Float.toString(GetSelectedMaxFrequency()));
        mSbPipeSpawnFreqMax.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                tvPipeSpawnFreqMax.setText(Float.toString(GetSelectedMaxFrequency()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void InitSeekBarPipeSpawnFreqMin(){
        mSbPipeSpawnFreqMin = findViewById(R.id.sb_pipe_spawn_min_freq);
        tvPipeSpawnFreqMin = findViewById(R.id.tv_pipe_spawn_min_freq_value);
        mSbPipeSpawnFreqMin.setMax((int)(MAX_MIN_PIPE_SPAWN_FREQ * 1000) -
                (int)(MIN_MIN_PIPE_SPAWN_FREQ * 1000));
        mSbPipeSpawnFreqMin.setProgress((int) (DEFAULT_PIPE_SPAWN_MIN_FREQ * 1000) -
                (int)(MIN_MIN_PIPE_SPAWN_FREQ * 1000));
        tvPipeSpawnFreqMin.setText(Float.toString(GetSelectedMinFrequency()));
        mSbPipeSpawnFreqMin.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                tvPipeSpawnFreqMin.setText(Float.toString(GetSelectedMinFrequency()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void InitSeekBarPipeMaxDistance(){
        mSbPipeGapDistanceMax = findViewById(R.id.sb_pipe_gap_max_distance);
        tvPipeGapDistanceMax = findViewById(R.id.tv_pipe_gap_max_distance_value);
        mSbPipeGapDistanceMax.setMax((int) MAX_PIPE_MAX_GAP_DISTANCE - (int) MIN_PIPE_MAX_GAP_DISTANCE);
        mSbPipeGapDistanceMax.setProgress((int) DEFAULT_PIPE_MAX_GAP_DISTANCE - (int) MIN_PIPE_MAX_GAP_DISTANCE);
        tvPipeGapDistanceMax.setText(Float.toString(GetSelectedMaxPipeDistance()));
        mSbPipeGapDistanceMax.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                tvPipeGapDistanceMax.setText(Float.toString(GetSelectedMaxPipeDistance()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void InitSeekBarPipeMinDistance(){
        mSbPipeGapDistanceMin = findViewById(R.id.sb_pipe_gap_min_distance);
        tvPipeGapDistanceMin = findViewById(R.id.tv_pipe_gap_min_distance_value);
        mSbPipeGapDistanceMin.setMax((int) MAX_PIPE_MIN_GAP_DISTANCE - (int) MIN_PIPE_MIN_GAP_DISTANCE);
        mSbPipeGapDistanceMin.setProgress((int) DEFAULT_PIPE_MIN_GAP_DISTANCE - (int) MIN_PIPE_MIN_GAP_DISTANCE);
        tvPipeGapDistanceMin.setText(Float.toString(GetSelectedMinPipeDistance()));
        mSbPipeGapDistanceMin.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                tvPipeGapDistanceMin.setText(Float.toString(GetSelectedMinPipeDistance()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void InitSeekBarPipeWidth(){
        mSbPipeWidth = findViewById(R.id.sb_pipe_width);
        tvPipeWidth = findViewById(R.id.tv_pipe_width_value);
        mSbPipeWidth.setMax((int) MAX_PIPE_WIDTH - (int) MIN_PIPE_WIDTH);
        mSbPipeWidth.setProgress((int) DEFAULT_PIPE_WIDTH - (int) MIN_PIPE_WIDTH);
        tvPipeWidth.setText(Float.toString(GetSelectedPipeWidth()));
        mSbPipeWidth.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                tvPipeWidth.setText(Float.toString(GetSelectedPipeWidth()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private void InitSeekBarNextPipeYOffset(){
        mSbNextPipeYOffset = findViewById(R.id.sb_next_pipe_y_offset);
        tvNextPipeYOffset = findViewById(R.id.tv_next_pipe_y_offset_value);
        mSbNextPipeYOffset.setMax((int) MAX_NEXT_PIPE_Y_OFFSET - (int) MIN_NEXT_PIPE_Y_OFFSET);
        mSbNextPipeYOffset.setProgress((int) DEFAULT_NEXT_PIPE_Y_OFFSET - (int) MIN_NEXT_PIPE_Y_OFFSET);
        tvNextPipeYOffset.setText(Float.toString(GetSelectedNextPipeYOffset()));
        mSbNextPipeYOffset.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                tvNextPipeYOffset.setText(Float.toString(GetSelectedNextPipeYOffset()));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    private float GetSelectedMoveSpeed(){

        int value = mSbScenaryMoveSpeed.getProgress();
        return (float) value + MIN_SCENARY_MOVE_SPEED;
    }

    private float GetSelectedJumpForce(){
        int value = mSbPlayerJumpForce.getProgress();
        return  (float) value + MIN_JUMP_FORCE;
    }

    private float GetSelectedMaxFrequency(){
        int value = mSbPipeSpawnFreqMax.getProgress();
        return (float) (value + MIN_MAX_PIPE_SPAWN_FREQ * 1000) /1000;
    }

    private float GetSelectedMinFrequency(){
        int value = mSbPipeSpawnFreqMin.getProgress();
        return (float) (value + MIN_MIN_PIPE_SPAWN_FREQ * 1000) / 1000;
    }

    private float GetSelectedMaxPipeDistance(){
        int value = mSbPipeGapDistanceMax.getProgress();
        return (float) value + MIN_PIPE_MAX_GAP_DISTANCE;
    }

    private float GetSelectedMinPipeDistance(){
        int value = mSbPipeGapDistanceMin.getProgress();
        return (float) value + MIN_PIPE_MIN_GAP_DISTANCE;
    }

    private float GetSelectedPipeWidth(){
        int value = mSbPipeWidth.getProgress();
        return (float ) value + MIN_PIPE_WIDTH;
    }

    private float GetSelectedNextPipeYOffset(){
        int value = mSbNextPipeYOffset.getProgress();
        return (float) value + MIN_NEXT_PIPE_Y_OFFSET;
    }

    private void ChangeToActivity(String sceneName) throws Exception {
        Intent intent = null;
        switch (sceneName){
            case "FlappyBirds":
                intent = new Intent(this, FlappyBirdActivity.class);
                intent.putExtra(INTENT_EXTRA_NAME_SCENARY_MOVE_SPEED, GetSelectedMoveSpeed());
                intent.putExtra(INTENT_EXTRA_NAME_JUMP_FORCE, GetSelectedJumpForce());
                intent.putExtra(INTENT_EXTRA_NAME_PIPE_SPAWN_MAX_FREQ, GetSelectedMaxFrequency());
                intent.putExtra(INTENT_EXTRA_NAME_PIPE_SPAWN_MIN_FREQ, GetSelectedMinFrequency());
                intent.putExtra(INTENT_EXTRA_NAME_PIPE_GAP_MAX_DISTANCE, GetSelectedMaxPipeDistance());
                intent.putExtra(INTENT_EXTRA_NAME_PIPE_GAP_MIN_DISTANCE, GetSelectedMinPipeDistance());
                intent.putExtra(INTENT_EXTRA_NAME_PIPE_WIDTH, GetSelectedPipeWidth());
                intent.putExtra(INTENT_EXTRA_NAME_NEXT_PIPE_Y_OFFSET, GetSelectedNextPipeYOffset());
                break;
            case "Test1":
                intent = new Intent(this, Test1Activity.class);
                break;
            case "Test2":
                intent = new Intent(this, Test2Activity.class);
                break;
            case "Test3":
                intent = new Intent(this, Test3Activity.class);
                break;
            case "Test4":
                intent = new Intent(this, Test4Activity.class);
                break;
            case "Test5":
                intent = new Intent(this, Test5Activity.class);
                break;
            default:
                throw new Exception("Error. Trying to load unknown scene activity.");
        }
        startActivity(intent);
    }
}
