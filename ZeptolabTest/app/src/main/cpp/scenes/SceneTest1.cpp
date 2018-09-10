//
// Created by Josep on 26/08/2018.
//

#include "SceneTest1.h"
#include "../engine/scene/SceneNode.h"

const float TARGET_RESOLUTION_WIDTH = 1440.f;
const float TARGET_RESOLUTION_HEIGHT = 2392.f;

const float RECTANGLES_SIDE_SIZE = 100.f;
const float HEART_BEAT_SPEED = 3.0f;
const float HEART_BEAT_MAX_SCALE = 2.f;
const float HEART_BEAT_MIN_SCALE = 0.5f;
const float PING_PONG_MAX_X = 700.f;
const float PING_PONG_MIN_X = -700.f;
const float PING_PONG_SPEED = 800.0f;
const float SPIN_LOCAL_SPEED = 250.f;
const float SPIN_SPEED = 50.f;

const std::string NODE_NAME_BACKGROUND  = "Background";
const std::string NODE_NAME_RED_RECT    = "RedRectangle";
const std::string NODE_NAME_GREEN_RECT  = "GreenRectangle";
const std::string NODE_NAME_BLUE_RECT   = "BlueRectangle";

SceneTest1::SceneTest1(utils::Width aDisplayWidth,
                       utils::Height aDisplayHeight)
    : Scene(aDisplayWidth, aDisplayHeight)
    , mMovingDirection(1.0f)
    , mScaleDirection(1.f)
{
}

void SceneTest1::Init()
{
    // Resolution and camera properties.
    GetCameraController().SetTargetResolution(utils::Width(TARGET_RESOLUTION_WIDTH),
                                              utils::Height(TARGET_RESOLUTION_HEIGHT));
    GetCameraController().GetCurrentCamera().SetProjectionMode(graphics::Camera::PM_ORTHO);
    GetCameraController().GetCurrentCamera().EnableZDepth(true);
    GetCameraController().GetCurrentCamera().SetNear(-1000.f);
    GetCameraController().GetCurrentCamera().SetFar(1000.f);

    // Background
    CreateRectangle(NODE_NAME_BACKGROUND,
                    utils::Width(TARGET_RESOLUTION_WIDTH),
                    utils::Height(TARGET_RESOLUTION_HEIGHT),
                    utils::Color(0.5f, 1.f, 1.f),
                    utils::Vector3<>(0.f, 0.f, 0.f));
    // Red Rectangle
    mRectangleRed = CreateRectangle(NODE_NAME_RED_RECT,
                                    utils::Width(RECTANGLES_SIDE_SIZE),
                                    utils::Height(RECTANGLES_SIDE_SIZE),
                                    utils::Color(1.0f, 0.f, 0.0f),
                                    utils::Vector3<float>(-200.f, 200.f, 100.f));
    // Green Rectangle
    mRectangleGreen = CreateRectangle(NODE_NAME_GREEN_RECT,
                                      utils::Width(RECTANGLES_SIDE_SIZE),
                                      utils::Height(RECTANGLES_SIDE_SIZE),
                                      utils::Color(0.f, 1.f, 0.f),
                                      utils::Vector3<float>(0.f, 0.f, 100.f));
    // Blue Rectangle
    mRectangleBlue = CreateRectangle(NODE_NAME_BLUE_RECT,
                                     utils::Width(RECTANGLES_SIDE_SIZE),
                                     utils::Height(RECTANGLES_SIDE_SIZE),
                                     utils::Color(0.f, 0.f, 1.f),
                                     utils::Vector3<float>(0.f, -400.f, 100.f));
}

scene::SceneNode* SceneTest1::CreateRectangle(const std::string &aName,
                                               utils::Width aWidth,
                                               utils::Height aHeight,
                                               utils::Color aColor,
                                               utils::Vector3<float> aPosition)
{
    auto& Node = CreateNode(aName);
    Node.AddComponent<scene::RendererRectangle>(std::move(
            GetComponentFactory().CreateComponentRendererRectangle(
                    aWidth,
                    aHeight)));
    Node.GetComponent<scene::RendererRectangle>()->SetColor(aColor);
    Node.SetPosition(aPosition);

    return &Node;
}

void SceneTest1::Update(double aDt)
{
    Spin(*mRectangleRed, aDt);
    HeartBeat(*mRectangleGreen, aDt);
    PingPong(*mRectangleBlue, aDt);
}

void SceneTest1::HeartBeat(scene::SceneNode& aNode, double aDt)
{
    auto SecondsSinceLastFrame = float(aDt / 1000.f);
    if (mScaleDirection == 1.0f && aNode.GetScale().X > HEART_BEAT_MAX_SCALE)
    {
        mScaleDirection = -1.0f;
    }
    else if(mScaleDirection == -1.f && aNode.GetScale().X < HEART_BEAT_MIN_SCALE)
    {
        mScaleDirection = 1.0f;
    }

    aNode.Scale(utils::Vector3<>(mScaleDirection * HEART_BEAT_SPEED * SecondsSinceLastFrame,
                                  mScaleDirection * HEART_BEAT_SPEED * SecondsSinceLastFrame,
                                  0.f));
}

void SceneTest1::PingPong(scene::SceneNode& aNode, double aDt)
{
    auto SecondsSinceLastFrame = float(aDt / 1000.f);
    if (mMovingDirection == 1.0f && aNode.GetPosition().X > PING_PONG_MAX_X)
    {
        mMovingDirection = -1.0f;
    }
    else if(mMovingDirection == -1.f && aNode.GetPosition().X < PING_PONG_MIN_X)
    {
        mMovingDirection = 1.0f;
    }

    aNode.Move(utils::Vector3<>(mMovingDirection * PING_PONG_SPEED * SecondsSinceLastFrame,
                                0.f, 0.f));
}

void SceneTest1::Spin(scene::SceneNode& aNode, double aDt)
{
    auto SecondsSinceLastFrame = float(aDt / 1000.f);
    aNode.Rotate(utils::Degrees(SPIN_SPEED * SecondsSinceLastFrame),
                 utils::Vector3<>(0.f, 0.f, 1.f));

    aNode.RotateLocal(utils::Degrees(SPIN_LOCAL_SPEED * SecondsSinceLastFrame),
                      utils::Vector3<>(0.f, 0.f, 1.f));
}