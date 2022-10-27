//
// Created by Josep on 08/09/2018.
//

#include "SceneTest4.h"
#include "../engine/scene/SceneNode.h"
#include "../engine/scene/components/RendererRectangle.h"
#include "../engine/scene/components/RendererCircle.h"

const std::string NODE_NAME_BACKGROUND  = "Background";
const std::string NODE_NAME_CIRCLE      = "Circle";
const std::string NODE_NAME_RECTANGLE   = "Rectangle";

SceneTest4::SceneTest4(utils::Width aDisplayWidth,
                       utils::Height aDisplayHeight)
        : Scene(aDisplayWidth, aDisplayHeight)
{
}

void SceneTest4::Init()
{
    // Resolution and camera properties.
    GetCameraController().SetTargetResolution(utils::Width(1440.0f), utils::Height(2392.0f));
    GetCameraController().GetCurrentCamera().SetProjectionMode(graphics::Camera::PM_ORTHO);
    GetCameraController().GetCurrentCamera().EnableZDepth(false);
    GetCameraController().GetCurrentCamera().SetNear(-1000.f);
    GetCameraController().GetCurrentCamera().SetFar(1000.f);

    // Create nodes in the scene.
    CreateNodeBackground();
    CreateNodeCircle();
    CreateNodeRectangle();
}

void SceneTest4::Update(double aDt)
{
    // Nothing to do.
}

void SceneTest4::CreateNodeCircle()
{
    auto Color = utils::Color(0.0f, 0.7f, 0.0f);
    auto Position = utils::Vector3<>(0.f, 0.f, 250.f);
    auto Radius = utils::Radius(250.f);
    auto Quality = 30;
    auto& Node = CreateNode(NODE_NAME_CIRCLE);
    Node.AddComponent<scene::RendererCircle>(std::move(
            GetComponentFactory().CreateComponentRendererCircle(
                    Radius,
                    Quality)));
    Node.GetComponent<scene::RendererCircle>()->SetColor(Color);
    Node.SetPosition(Position);
}

void SceneTest4::CreateNodeRectangle()
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
}

void SceneTest4::CreateNodeBackground()
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