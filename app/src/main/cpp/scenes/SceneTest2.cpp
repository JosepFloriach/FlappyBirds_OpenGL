//
// Created by Josep on 13/08/2018.
//

#include "SceneTest2.h"
#include "../engine/graphics/camera/Camera.h"
#include "../engine/scene/SceneNode.h"
#include "../engine/scene/components/RendererRectangle.h"
#include "../engine/scene/components/PhysicsBody.h"
#include "../engine/physics/WorldPhysics.h"
#include <memory>

const float TARGET_RESOLUTION_WIDTH = 1440.f;
const float TARGET_RESOLUTION_HEIGHT = 2392.f;

const std::string NODE_NAME_BACKGROUND = "Background";
const std::string NODE_NAME_RECTANGLE = "Rectangle";

const float JUMP_FORCE_Y = 2500.f;
const float JUMP_FORCE_X = 500.f;

SceneTest2::SceneTest2(utils::Width aDisplayWidth,
                       utils::Height aDisplayHeight)
    : Scene(aDisplayWidth, aDisplayHeight)
{
}

void SceneTest2::Init()
{
    physics::WorldPhysics::Gravity = utils::Vector3<>(0.f, -90.81f, 0.f);

    // Resolution and camera properties.
    GetCameraController().SetTargetResolution(utils::Width(1440.0f), utils::Height(2392.0f));
    GetCameraController().GetCurrentCamera().SetProjectionMode(graphics::Camera::PM_ORTHO);
    GetCameraController().GetCurrentCamera().EnableZDepth(true);
    GetCameraController().GetCurrentCamera().SetNear(-1000.f);
    GetCameraController().GetCurrentCamera().SetFar(1000.f);

    // Create Nodes.
    CreateBackground();
    CreateRectangle();
}

void SceneTest2::CreateBackground()
{
    auto Width = utils::Width(TARGET_RESOLUTION_WIDTH);
    auto Height = utils::Height(TARGET_RESOLUTION_HEIGHT);
    auto Color = utils::Color(0.5f, 1.f, 1.f);
    auto Position = utils::Vector3<>(0.f, 0.f, 0.f);
    auto& Node = CreateNode(NODE_NAME_BACKGROUND);
    Node.AddComponent<scene::RendererRectangle>(std::move(
            GetComponentFactory().CreateComponentRendererRectangle(
                    Width,
                    Height)));
    Node.GetComponent<scene::RendererRectangle>()->SetColor(Color);
    Node.SetPosition(Position);
}

void SceneTest2::CreateRectangle()
{
    auto Width = utils::Width(100.f);
    auto Height = utils::Height(100.f);
    auto Color = utils::Color(1.f, 0.f, 0.f);
    auto Position = utils::Vector3<>(0.f, 0.f, 150.f);
    auto& Node = CreateNode(NODE_NAME_RECTANGLE);
    Node.AddComponent<scene::RendererRectangle>(std::move(
            GetComponentFactory().CreateComponentRendererRectangle(
                    Width,
                    Height)));
    Node.AddComponent<scene::PhysicsBody>(std::move(
            GetComponentFactory().CreateComponentPhysicsBody()));
    Node.GetComponent<scene::RendererRectangle>()->SetColor(Color);
    Node.SetPosition(Position);

    mBody = &Node;
}

void SceneTest2::Update(double aDt)
{
}

void SceneTest2::OnTouch(float aX, float aY)
{
    Jump();
}

void SceneTest2::Jump()
{
    scene::PhysicsBody* PhysicsComponent = mBody->GetComponent<scene::PhysicsBody>();
    if (PhysicsComponent)
    {
        PhysicsComponent->SetApplyGravity(true);
        PhysicsComponent->AddForce(utils::Vector3<>(JUMP_FORCE_X, JUMP_FORCE_Y, 0.f));
    }
}