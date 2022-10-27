//
// Created by Josep on 13/08/2018.
//
#include "SceneFlappyBirds.h"

#include "../../engine/graphics/camera/Camera.h"
#include "../../engine/scene/SceneNode.h"

#include "../../engine/common/events/EventDispatcher.h"



const float SceneFlappyBirds::TARGET_RESOLUTION_WIDTH = 1440.f;
const float SceneFlappyBirds::TARGET_RESOLUTION_HEIGHT = 2392.f;

const std::string NODE_NAME_PLAYER          = "Player";
const std::string NODE_NAME_BACKGROUND      = "Background";
const std::string NODE_NAME_FLOOR           = "Floor";
const std::string NODE_NAME_ROOF            = "Roof";

SceneFlappyBirds::SceneFlappyBirds(utils::Width aDisplayWidth, utils::Height aDisplayHeight)
    : Scene(aDisplayWidth, aDisplayHeight)
    , mScenary(this)
    , mPlayer(nullptr)
{
}

void SceneFlappyBirds::Init()
{
    // Set world gravity.
    physics::WorldPhysics::Gravity = utils::Vector3<>(0.f, -90.81f, 0.f);

    // Subscribe on collision events.
    events::EventDispatcher::StartListening(events::EnterCollisionEvent::Descriptor,
                                            std::bind(&SceneFlappyBirds::OnCollision,
                                                      this,
                                                      std::placeholders::_1));

    // Resolution and camera properties.
    GetCameraController().SetTargetResolution(utils::Width(TARGET_RESOLUTION_WIDTH),
                                              utils::Height(TARGET_RESOLUTION_HEIGHT));
    GetCameraController().GetCurrentCamera().SetProjectionMode(graphics::Camera::PM_ORTHO);
    GetCameraController().GetCurrentCamera().EnableZDepth(true);
    GetCameraController().GetCurrentCamera().SetNear(-1000.f);
    GetCameraController().GetCurrentCamera().SetFar(1000.f);

    // Create nodes in the scene.
    CreateBackground();
    CreatePlayer();
    CreateFloor();
    CreateRoof();
}

void SceneFlappyBirds::CreateBackground()
{
    auto Color = utils::Color(0.5f, 1.f, 1.f);
    auto Position = utils::Vector3<>(0.f, 0.f, 0.f);
    auto Width = utils::Width(1440.f);
    auto Height = utils::Height(2392.f);
    auto& Node = CreateNode(NODE_NAME_BACKGROUND);
    Node.AddComponent<scene::RendererRectangle>(std::move(
            GetComponentFactory().CreateComponentRendererRectangle(Width,Height)));
    Node.GetComponent<scene::RendererRectangle>()->SetColor(Color);
    Node.SetPosition(Position);
}

void SceneFlappyBirds::CreatePlayer()
{
    auto Color = utils::Color(0.0f, 0.7f, 0.0f);
    auto Position = utils::Vector3<>(-350.f, 0.f, 500.f);
    auto Radius = utils::Radius(50.f);
    auto Quality = 30;
    mPlayer = dynamic_cast<Player*>(&CreateNode<Player>(NODE_NAME_PLAYER));
    mPlayer->AddComponent<scene::RendererCircle>(std::move(
            GetComponentFactory().CreateComponentRendererCircle(
                    Radius,
                    Quality)));
    mPlayer->AddComponent<scene::PhysicsBody>(std::move(
            GetComponentFactory().CreateComponentPhysicsBody()));
    mPlayer->AddComponent<scene::ColliderCircle>(std::move(
            GetComponentFactory().CreateComponentColliderCircle(
                    Radius)));
    mPlayer->GetComponent<scene::RendererCircle>()->SetColor(Color);
    mPlayer->SetPosition(Position);
}

void SceneFlappyBirds::CreateRoof()
{
    auto Color = utils::Color(0.6f, 0.3f, 0.3f);
    auto Position = utils::Vector3<>(0.f, TARGET_RESOLUTION_HEIGHT/2.f , 50.f);
    auto Width = utils::Width(TARGET_RESOLUTION_WIDTH);
    auto Height = utils::Height(250.f);
    auto& Node = CreateNode(NODE_NAME_ROOF);
    Node.AddComponent<scene::RendererRectangle>(std::move(
            GetComponentFactory().CreateComponentRendererRectangle(
                    Width,
                    Height)));
    Node.AddComponent<scene::ColliderBox>(std::move(
            GetComponentFactory().CreateComponentColliderBox(
                    Width,
                    Height)));
    Node.GetComponent<scene::RendererRectangle>()->SetColor(Color);
    Node.SetPosition(Position);
}

void SceneFlappyBirds::CreateFloor()
{
    auto Color = utils::Color(0.6f, 0.3f, 0.3f);
    auto Position = utils::Vector3<>(0.f, -TARGET_RESOLUTION_HEIGHT/2.f, 50.f);
    auto Width = utils::Width(TARGET_RESOLUTION_WIDTH);
    auto Height = utils::Height(250.f);
    auto& Node = CreateNode(NODE_NAME_FLOOR);
    Node.AddComponent<scene::RendererRectangle>(std::move(
            GetComponentFactory().CreateComponentRendererRectangle(
                    Width,
                    Height)));
    Node.AddComponent<scene::ColliderBox>(std::move(
            GetComponentFactory().CreateComponentColliderBox(
                    Width,
                    Height)));
    Node.GetComponent<scene::RendererRectangle>()->SetColor(Color);
    Node.SetPosition(Position);
}

void SceneFlappyBirds::OnTouch(float aX, float aY)
{
    if (!mPlayer->IsDead())
    {
        mPlayer->Awake();
        mPlayer->Jump();
    }
}

void SceneFlappyBirds::Update(double aDt)
{
    if (!mPlayer->IsDead() && mPlayer->IsAwake())
    {
        mScenary.Update(aDt);
    }
}

void SceneFlappyBirds::OnCollision(const events::Event &aEvent)
{
    const auto* EnterCollisionEvent = dynamic_cast<const events::EnterCollisionEvent*>(&aEvent);
    scene::SceneNode* FirstNode = nullptr;
    scene::SceneNode* SecondNode = nullptr;
    EnterCollisionEvent->GetNodes(FirstNode, SecondNode);

    if (FirstNode->GetNodeName() == NODE_NAME_PLAYER ||
        SecondNode->GetNodeName() == NODE_NAME_PLAYER)
    {
        mPlayer->Kill();
    }

}
