//
// Created by Josep on 08/09/2018.
//

#include "SceneTest5.h"
#include "../engine/scene/SceneNode.h"
#include "../engine/scene/components/RendererRectangle.h"
#include "../engine/scene/components/RendererCircle.h"

const std::string NODE_NAME_BACKGROUND  = "Background";
const std::string NODE_NAME_CIRCLE      = "Circle";
const std::string NODE_NAME_RECTANGLE   = "Rectangle";

const float MOVE_SPEED = 50.f;

SceneTest5::SceneTest5(utils::Width aDisplayWidth,
                       utils::Height aDisplayHeight)
        : Scene(aDisplayWidth, aDisplayHeight)
        , mRectangle(nullptr)
{
}

void SceneTest5::Init()
{
    // Resolution and camera properties.
    GetCameraController().SetTargetResolution(utils::Width(1440.0f), utils::Height(2392.0f));
    GetCameraController().GetCurrentCamera().SetProjectionMode(graphics::Camera::PM_ORTHO);
    GetCameraController().GetCurrentCamera().EnableZDepth(false);
    GetCameraController().GetCurrentCamera().SetNear(-1000.f);
    GetCameraController().GetCurrentCamera().SetFar(1000.f);

    // Create nodes in the scene.
    CreateNodeBackground();
    mRectangle = &CreateRectangle();
    CreateCircleChild(*mRectangle);
}

void SceneTest5::Update(double aDt)
{
    if (mRectangle)
    {
        float SecondsSinceLastFrame = aDt / 1000.f;
        mRectangle->Move(utils::Vector3<float>(MOVE_SPEED * SecondsSinceLastFrame, 0.f, 0.f));
    }
}

scene::SceneNode& SceneTest5::CreateRectangle()
{
    auto Color = utils::Color(0.6f, 0.3f, 0.3f);
    auto Position = utils::Vector3<>(0.f, 0.f , 50.f);
    auto Width = utils::Width(250.f);
    auto Height = utils::Height(250.f);
    auto& Node = CreateNode(NODE_NAME_RECTANGLE);
    Node.AddComponent<scene::RendererRectangle>(std::move(
            GetComponentFactory().CreateComponentRendererRectangle(
                    Width,
                    Height)));
    Node.GetComponent<scene::RendererRectangle>()->SetColor(Color);
    Node.SetPosition(Position);

    return Node;
}

void SceneTest5::CreateCircleChild(scene::SceneNode &aParent)
{
    auto Color = utils::Color(1.0f, 0.0f, 0.0f);
    auto Position = utils::Vector3<>(-100.f, 500.f, 250.f);
    auto Radius = utils::Radius(50.f);
    auto Quality = 30;
    auto& Node = aParent.CreateChild(NODE_NAME_CIRCLE);
    Node.AddComponent<scene::RendererCircle>(std::move(
            GetComponentFactory().CreateComponentRendererCircle(
                    Radius,
                    Quality)));
    Node.GetComponent<scene::RendererCircle>()->SetColor(Color);
    Node.SetRelativePosition(Position);
}

void SceneTest5::CreateNodeBackground()
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