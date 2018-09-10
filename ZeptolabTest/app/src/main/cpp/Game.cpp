//
// Created by Josep on 11/08/2018.
//

#include "Game.h"
#include "scenes/SceneTest5.h"
#include "scenes/SceneTest4.h"
#include "scenes/SceneTest3.h"
#include "scenes/SceneTest2.h"
#include "scenes/SceneTest1.h"
#include "scenes/FlappyBirds/SceneFlappyBirds.h"

Game::Game(std::string aSceneName,
           utils::Width aDisplayWidth,
           utils::Height aDisplayHeight)
    : mWidth(aDisplayWidth)
    , mHeight(aDisplayHeight)
    , mScene(nullptr)
{
    mTimer.Start();
    LoadScene(aSceneName);
    InitScene();
}

Game::~Game()
{
    events::EventDispatcher::ReleaseAllListeners();
}

void Game::LoadScene(std::string aName)
{
    if (aName == "Test1")
    {
        mScene = std::make_unique<SceneTest1>(mWidth, mHeight);
    }

    if (aName == "Test2")
    {
        mScene = std::make_unique<SceneTest2>(mWidth, mHeight);
    }

    if (aName == "Test3")
    {
        mScene = std::make_unique<SceneTest3>(mWidth, mHeight);
    }

    if (aName == "Test4")
    {
        mScene = std::make_unique<SceneTest4>(mWidth, mHeight);
    }

    if (aName == "Test5")
    {
        mScene = std::make_unique<SceneTest5>(mWidth, mHeight);
    }

    if (aName == "FlappyBirds")
    {
        mScene = std::make_unique<SceneFlappyBirds>(mWidth, mHeight);
    }
}

void Game::InitScene()
{
    if (mScene)
        mScene->Init();
}

void Game::DrawScene()
{
    mTimer.Update();
    if (mScene != nullptr)
    {
        mScene->Update(mTimer.ElapsedTimeLastFrameMillis());
        mScene->Draw(mTimer.ElapsedTimeLastFrameMillis());
    }
}

void Game::OnTouch(float aX, float aY)
{
    if (mScene)
        mScene->OnTouch(aX, aY);
}