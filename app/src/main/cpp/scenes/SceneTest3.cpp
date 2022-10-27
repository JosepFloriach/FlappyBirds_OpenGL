//
// Created by Josep on 13/08/2018.
//

#include "SceneTest3.h"
#include "../engine/graphics/camera/Camera.h"
#include "../engine/scene/SceneNode.h"
#include "../engine/scene/components/RendererRectangle.h"
#include "../engine/scene/components/RendererCircle.h"

#include "../engine/common/events/EventDispatcher.h"
#include "../engine/common/events/EventPool.h"

#include <memory>

const std::string NODE_NAME_BACKGROUND  = "Background";
const std::string NODE_NAME_BIG_CIRCLE  = "BigCircle";
const std::string NODE_NAME_BIG_SQUARE  = "BigSquare";
const std::string NODE_NAME_RECTANGLE1  = "Rectangle1";
const std::string NODE_NAME_RECTANGLE2  = "Rectangle2";
const std::string NODE_NAME_CIRCLE_1    = "Circle1";

SceneTest3::SceneTest3(utils::Width aDisplayWidth,
                       utils::Height aDisplayHeight)
    : Scene(aDisplayWidth, aDisplayHeight)
{
}

void SceneTest3::Init()
{
    // Subscribe on collision events.
    events::EventDispatcher::StartListening(events::EnterCollisionEvent::Descriptor,
                                            std::bind(&SceneTest3::OnEnterCollision,
                                                      this,
                                                      std::placeholders::_1));
    events::EventDispatcher::StartListening(events::ExitCollisionEvent::Descriptor,
                                            std::bind(&SceneTest3::OnExitCollision,
                                                      this,
                                                      std::placeholders::_1));

    // Resolution and camera properties.
    GetCameraController().SetTargetResolution(utils::Width(1440.0f), utils::Height(2392.0f));
    GetCameraController().GetCurrentCamera().SetProjectionMode(graphics::Camera::PM_ORTHO);
    GetCameraController().GetCurrentCamera().EnableZDepth(true);
    GetCameraController().GetCurrentCamera().SetNear(-1000.f);
    GetCameraController().GetCurrentCamera().SetFar(1000.f);

    // Create nodes in the scene.
    CreateNodeBackground();
    CreateNodeBigCircle();
    CreateNodeBigRectangle();
    CreateNodeCircle();
    CreateNodeRectangle1();
    CreateNodeRectangle2();
}

void SceneTest3::CreateNodeBackground()
{
    auto Color = utils::Color(0.5f, 1.f, 1.f);
    auto Position = utils::Vector3<>(0.f, 0.f, 100.f);
    auto Width = utils::Width(1440.f);
    auto Height = utils::Height(2392.f);
    auto& Node = CreateNode(NODE_NAME_BACKGROUND);
    Node.AddComponent<scene::RendererRectangle>(std::move(
            GetComponentFactory().CreateComponentRendererRectangle(
                    Width,
                    Height)));
    Node.GetComponent<scene::RendererRectangle>()->SetColor(Color);
    Node.SetPosition(Position);
}

void SceneTest3::CreateNodeBigCircle()
{
    auto Color = utils::Color(1.f, 0.f, 0.f);
    auto Position = utils::Vector3<>(0.f, 250.f, 150.f);
    auto Radius = utils::Radius(250.f);
    auto Quality = 30;
    auto& Node = CreateNode(NODE_NAME_BIG_CIRCLE);
    Node.AddComponent<scene::RendererCircle>(std::move(
            GetComponentFactory().CreateComponentRendererCircle(
                    Radius,
                    Quality)));
    Node.AddComponent<scene::ColliderCircle>(std::move(
            GetComponentFactory().CreateComponentColliderCircle(
                    Radius)));
    Node.GetComponent<scene::RendererCircle>()->SetColor(Color);
    Node.SetPosition(Position);
}

void SceneTest3::CreateNodeBigRectangle()
{
    auto Color = utils::Color(1.f, 0.f, 0.f);
    auto Position = utils::Vector3<>(0.f, -500, 150.f);
    auto Width = utils::Width(500.f);
    auto Height = utils::Height(500.f);
    auto& Node = CreateNode(NODE_NAME_BIG_SQUARE);
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

void SceneTest3::CreateNodeCircle()
{
    auto Color = utils::Color(0.f, 1.f, 0.f);
    auto Position = utils::Vector3<>(0.f, 700.f, 200.f);
    auto Radius = utils::Radius(100.f);
    auto Quality = 30;
    auto& Node = CreateNode(NODE_NAME_CIRCLE_1);
    Node.AddComponent<scene::RendererCircle>(std::move(
            GetComponentFactory().CreateComponentRendererCircle(
                    Radius,
                    Quality)));
    Node.AddComponent<scene::ColliderCircle>(std::move(
            GetComponentFactory().CreateComponentColliderCircle(
                    Radius)));
    Node.GetComponent<scene::RendererCircle>()->SetColor(Color);
    Node.SetPosition(Position);

    mMovingCircle = &Node;
}

void SceneTest3::CreateNodeRectangle1()
{
    auto Color = utils::Color(0.f, 1.f, 0.f);
    auto Position = utils::Vector3<>(-500.f, -500, 200.f);
    auto Width = utils::Width(100.f);
    auto Height = utils::Height(100.f);
    auto& Node = CreateNode(NODE_NAME_RECTANGLE1);
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

    mMovingRectangle1 = &Node;
}

void SceneTest3::CreateNodeRectangle2()
{
    auto Color = utils::Color(0.f, 1.f, 0.f);
    auto Position = utils::Vector3<>(-500.f, 150.f, 200.f);
    auto Width = utils::Width(100.f);
    auto Height = utils::Height(100.f);
    auto& Node = CreateNode(NODE_NAME_RECTANGLE2);
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

    mMovingRectangle2 = &Node;
}

void SceneTest3::Update(double aDt)
{
    if (mMovingRectangle1)
        mMovingRectangle1->Move(utils::Vector3<>(90.f * (float) aDt / 1000.f, 0.f, 0.f));
    if (mMovingRectangle2)
        mMovingRectangle2->Move(utils::Vector3<>(70.f * (float) aDt / 1000.f, 0.f, 0.f));
    if (mMovingCircle)
        mMovingCircle->Move(utils::Vector3<>(0.f, -150.f * (float) aDt / 1000.f, 0.f));
}

void SceneTest3::OnEnterCollision(const events::Event &aEvent)
{
    const auto* EnterEvent = dynamic_cast<const events::EnterCollisionEvent*>(&aEvent);
    scene::SceneNode* FirstNode = nullptr;
    scene::SceneNode* SecondNode = nullptr;
    EnterEvent->GetNodes(FirstNode, SecondNode);


    if (FirstNode->GetNodeName() == NODE_NAME_CIRCLE_1 ||
        SecondNode->GetNodeName() == NODE_NAME_CIRCLE_1 )
    {
        scene::RendererCircle* Renderer = mMovingCircle->GetComponent<scene::RendererCircle>();
        if (Renderer)
            Renderer->SetColor(utils::Color(0.f, 0.f, 1.0f));
    }

    if (FirstNode->GetNodeName() == NODE_NAME_RECTANGLE1 ||
        SecondNode->GetNodeName() == NODE_NAME_RECTANGLE1)
    {
        scene::RendererRectangle* Renderer = mMovingRectangle1->GetComponent<scene::RendererRectangle>();
        if (Renderer)
            Renderer->SetColor(utils::Color(0.f, 0.f, 1.0f));
    }

    if (FirstNode->GetNodeName() == NODE_NAME_RECTANGLE2 ||
        SecondNode->GetNodeName() == NODE_NAME_RECTANGLE2)
    {
        scene::RendererRectangle* Renderer = mMovingRectangle2->GetComponent<scene::RendererRectangle>();
        if (Renderer)
            Renderer->SetColor(utils::Color(0.f, 0.f, 1.0f));
    }
}

void SceneTest3::OnExitCollision(const events::Event &aEvent)
{
    const auto* ExitEvent = dynamic_cast<const events::ExitCollisionEvent*>(&aEvent);
    scene::SceneNode* FirstNode;
    scene::SceneNode* SecondNode;
    ExitEvent->GetNodes(FirstNode, SecondNode);

    if (FirstNode->GetNodeName() == NODE_NAME_CIRCLE_1 ||
        SecondNode->GetNodeName() == NODE_NAME_CIRCLE_1 )
    {
        scene::RendererCircle* Renderer = mMovingCircle->GetComponent<scene::RendererCircle>();
        if (Renderer)
            Renderer->SetColor(utils::Color(0.f, 1.f, 0.0f));
    }

    if (FirstNode->GetNodeName() == NODE_NAME_RECTANGLE1 ||
        SecondNode->GetNodeName() == NODE_NAME_RECTANGLE1)
    {
        scene::RendererRectangle* Renderer = mMovingRectangle1->GetComponent<scene::RendererRectangle>();
        if (Renderer)
            Renderer->SetColor(utils::Color(0.f, 1.f, 0.0f));
    }

    if (FirstNode->GetNodeName() == NODE_NAME_RECTANGLE2 ||
        SecondNode->GetNodeName() == NODE_NAME_RECTANGLE2)
    {
        scene::RendererRectangle* Renderer = mMovingRectangle2->GetComponent<scene::RendererRectangle>();
        if (Renderer)
            Renderer->SetColor(utils::Color(0.f, 1.f, 0.0f));
    }
}