#include <jni.h>
#include <memory>
#include <string>

#include "Game.h"
#include "scenes/FlappyBirds/SceneFlappyBirds.h"
#include "scenes/FlappyBirds/Player.h"
#include "engine/common/Utils.h"
#include <android/log.h>

extern "C"
{
    std::unique_ptr<Game> mGame= nullptr;

    JNIEXPORT void JNICALL
    Java_com_example_josep_zeptolabtest_GameRenderer_CreateGame(JNIEnv *env,
                                                                jobject instance,
                                                                jstring aSceneName,
                                                                jint aDisplayWidth,
                                                                jint aDisplayHeight)
    {
        // First, we parse the input parameters.
        const char *cSceneName = env->GetStringUTFChars(aSceneName, JNI_FALSE);
        std::string sSceneName(cSceneName);
        utils::Width Width((unsigned) aDisplayWidth);
        utils::Height Height((unsigned) aDisplayHeight);

        __android_log_print(ANDROID_LOG_DEBUG,"ZEPTOLAB_TEST_GAME_CREATION", "Creating new game...");
        mGame.reset();
        mGame = std::make_unique<Game>(sSceneName, Width, Height);
        __android_log_print(ANDROID_LOG_DEBUG,"ZEPTOLAB_TEST_GAME_CREATION", "Game created...");
        env->ReleaseStringUTFChars(aSceneName, cSceneName);
    }

    JNIEXPORT void JNICALL
    Java_com_example_josep_zeptolabtest_GameRenderer_DrawFrame(JNIEnv *env,
                                                               jobject instance)
    {
        if (mGame)
            mGame->DrawScene();
    }

    JNIEXPORT void JNICALL
    Java_com_example_josep_zeptolabtest_GameSurfaceView_OnTouch(JNIEnv *env,
                                                                jobject instance,
                                                                jfloat xPosition,
                                                                jfloat yPosition)
    {
        if (mGame)
            mGame->OnTouch((float) xPosition, (float) yPosition);

    }

    JNIEXPORT void JNICALL
    Java_com_example_josep_zeptolabtest_FlappyBirdActivity_CreateFlappyBirdsParams(JNIEnv *env,
                                                                                   jobject instance,
                                                                                   jfloat playerJumpForce,
                                                                                   jfloat scenarySpeed,
                                                                                   jfloat pipeSpawnMaxFreq,
                                                                                   jfloat pipeSpawnMinFreq,
                                                                                   jfloat pipeGapMaxDistance,
                                                                                   jfloat pipeGapMinDistance,
                                                                                   jfloat pipeWidth,
                                                                                   jfloat nextPipeYOffset)
    {
        Player::JUMP_FORCE = playerJumpForce;
        Scenary::MOVE_SPEED = scenarySpeed;
        Scenary::PIPE_SPAWN_MAX_FREQ = pipeSpawnMaxFreq;
        Scenary::PIPE_SPAWN_MIN_FREQ = pipeSpawnMinFreq;
        Scenary::PIPE_GAP_MAX_DISTANCE = pipeGapMaxDistance;
        Scenary::PIPE_GAP_MIN_DISTANCE = pipeGapMinDistance;
        Scenary::PIPE_WIDTH = pipeWidth;
        Scenary::NEXT_PIPE_Y_OFFSET = nextPipeYOffset;
    }
}