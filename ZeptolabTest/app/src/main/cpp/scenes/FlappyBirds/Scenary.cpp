//
// Created by Josep on 04/09/2018.
//

#include "Scenary.h"
#include "../../engine/scene/Scene.h"
#include "SceneFlappyBirds.h"
#include <cstdlib>

// Move speed of scenary.
float Scenary::MOVE_SPEED               = 500.0f;
// Max time since the last pipe, before we spawn a new Pipe
float Scenary::PIPE_SPAWN_MAX_FREQ      = 2.5f;
// Min time since the last pipe, before we spawn a new Pipe
float Scenary::PIPE_SPAWN_MIN_FREQ      = 1.5f;
// Max distance between pipe parts.
float Scenary::PIPE_GAP_MAX_DISTANCE    = 500.f;
// Min distance between pipe parts.
float Scenary::PIPE_GAP_MIN_DISTANCE    = 350.f;
// Pipe Width. All pipes will be of the same width.
float Scenary::PIPE_WIDTH               = 300.f;
// Max distance in Y axis between a pipe's gap and the next one.
// This parameter is useful to avoid situations where the player
// can't achieve the next pipe gap because it's to far in Y axis.
float Scenary::NEXT_PIPE_Y_OFFSET       = 700.f;

// Max Y position where a pipe can be spawned.
const float PIPE_MAX_Y                  = 400.f;
// Min Y position where a pipe can be spawned.
const float PIPE_MIN_Y                  = -400.f;


const std::string PIPE_NODE_NAME__PREFIX_BOT    = "PipeBot_";
const std::string PIPE_NODE_NAME__PREFIX_TOP    = "PipeTop_";

const utils::Color PIPE_COLOR = utils::Color(0.6f, 0.3f, 0.3f);

Scenary::Scenary(scene::Scene* aScene)
    : mScene(aScene)
    , mSecondsSinceLastPipe(0.f)
    , mSecondsUntilNextPipe(PIPE_SPAWN_MAX_FREQ)
    , mYPositionGapLastPipe(0.f)
    , mPipesCount(0)
{
}

void Scenary::Update(double aDt)
{
    auto TimeLastFrame = aDt / 1000.f;
    // Spawn a new pipe if corresponds (based on scenary parameters).
    PipeGeneration(aDt);
    // For each pipe in the scene move it horizontally to the left. If it reached the left
    // bound of the screen, we delete it. We don't need it anymore.
    for (auto It = mPipes.begin(); It != mPipes.end();)
    {
        scene::SceneNode* Node = (*It);
        Node->Move(utils::Vector3<>(-MOVE_SPEED * TimeLastFrame, 0.f, 0.f));
        if (Node->GetPosition().X < -mScene->GetWidth().value/ 2.0f - PIPE_WIDTH)
        {
            mScene->RemoveNode(Node->GetNodeName());
            mPipes.erase(It);
        }
        else
        {
            ++It;
        }
    }
}

void Scenary::PipeGeneration(double aDt)
{
    auto TimeLastFrame = aDt / 1000.f;
    mSecondsSinceLastPipe += TimeLastFrame;
    if (mSecondsSinceLastPipe >= mSecondsUntilNextPipe)
    {
        SpawnPipe();
        ResetTimeForNextPipe();
    }
}

void Scenary::ResetTimeForNextPipe()
{
    mSecondsSinceLastPipe = 0.f;
    mSecondsUntilNextPipe = utils::GetRandom<float>(PIPE_SPAWN_MIN_FREQ, PIPE_SPAWN_MAX_FREQ);
}

void Scenary::SpawnPipe()
{
    // Get some references from the scene to build the pipe.
    scene::FactoryComponent& Factory = mScene->GetComponentFactory();
    auto SceneWidth = SceneFlappyBirds::TARGET_RESOLUTION_WIDTH;
    auto SceneHeight = SceneFlappyBirds::TARGET_RESOLUTION_HEIGHT;

    // Pipe parameters generation.
    auto MinPositionY = mYPositionGapLastPipe - NEXT_PIPE_Y_OFFSET / 2.f;
    auto MaxPositionY = mYPositionGapLastPipe + NEXT_PIPE_Y_OFFSET / 2.f;
    MaxPositionY = utils::Clamp(MaxPositionY, PIPE_MIN_Y, PIPE_MAX_Y);
    MinPositionY = utils::Clamp(MinPositionY, PIPE_MIN_Y, PIPE_MAX_Y);
    auto GapSize = utils::GetRandom<float>(PIPE_GAP_MIN_DISTANCE, PIPE_GAP_MAX_DISTANCE);
    auto GapPositionY = utils::GetRandom<float>(MinPositionY, MaxPositionY);

    // Pipe parameters calculation.
    auto Width = utils::Width(PIPE_WIDTH);
    auto DistanceFromBotToGap = SceneHeight / 2.f + GapPositionY;
    auto HeightTop = utils::Height(SceneHeight - (GapSize/2.f + GapPositionY + DistanceFromBotToGap));
    auto HeightBot = utils::Height(SceneHeight - (GapSize + HeightTop.value));
    auto YPositionBot = -SceneHeight / 2.0f + HeightBot.value / 2.f;
    auto YPositionTop = SceneHeight / 2.0f - HeightTop.value / 2.f;
    auto PositionBot = utils::Vector3<>(SceneWidth / 2.0f + Width.value, YPositionBot, 75.f);
    auto PositionTop = utils::Vector3<>(SceneWidth / 2.0f + Width.value, YPositionTop, 75.f);

    // Pipe creation.
    auto NodeNameBot = PIPE_NODE_NAME__PREFIX_BOT + std::to_string(mPipesCount);
    auto NodeNameTop = PIPE_NODE_NAME__PREFIX_TOP + std::to_string(mPipesCount);
    auto& NodeBot = mScene->CreateNode(NodeNameBot);
    auto& NodeTop = mScene->CreateNode(NodeNameTop);

    // Pipe position.
    NodeBot.SetPosition(PositionBot);
    NodeTop.SetPosition(PositionTop);

    // Pipe bot components.
    NodeBot.AddComponent<scene::RendererRectangle>(std::move(
            Factory.CreateComponentRendererRectangle(
                    Width,
                    HeightBot)));
    NodeBot.AddComponent<scene::ColliderBox>(std::move(
            Factory.CreateComponentColliderBox(
                    Width,
                    HeightBot)));
    NodeBot.GetComponent<scene::RendererRectangle>()->SetColor(PIPE_COLOR);

    // Pipe top components.
    NodeTop.AddComponent<scene::RendererRectangle>(std::move(
            Factory.CreateComponentRendererRectangle(
                    Width,
                    HeightTop)));
    NodeTop.AddComponent<scene::ColliderBox>(std::move(
            Factory.CreateComponentColliderBox(
                    Width,
                    HeightTop)));
    NodeTop.GetComponent<scene::RendererRectangle>()->SetColor(PIPE_COLOR);

    mPipesCount++;
    mPipes.push_back(&NodeTop);
    mPipes.push_back(&NodeBot);
    mYPositionGapLastPipe = GapPositionY;
}

