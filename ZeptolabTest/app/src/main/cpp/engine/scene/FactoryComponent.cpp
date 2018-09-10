//
// Created by Josep on 14/08/2018.
//

#include "FactoryComponent.h"

#include "SceneNode.h"
#include "components/RendererRectangle.h"
#include "components/RendererCircle.h"
#include "components/PhysicsBody.h"
#include "components/ColliderBox.h"
#include "components/ColliderCircle.h"

#include "../graphics/shaders/Shader.h"

namespace scene
{
    FactoryComponent::FactoryComponent(
            const graphics::ShaderController &aShaderController,
            const graphics::CameraController& aCameraController,
            physics::WorldPhysics& aPhysics)
        : mShaderController(aShaderController)
        , mCameraController(aCameraController)
        , mPhysics(aPhysics)
    {
    }

    std::unique_ptr<ColliderBox> FactoryComponent::CreateComponentColliderBox(
            utils::Width aWidth,
            utils::Height aHeight)
    {
        auto Component = std::make_unique<ColliderBox>(aWidth, aHeight);
        mPhysics.AddCollider(Component.get());
        return std::move(Component);
    }

    std::unique_ptr<ColliderCircle> FactoryComponent::CreateComponentColliderCircle(
            utils::Radius aRadius)
    {
        auto Component = std::make_unique<ColliderCircle>(aRadius);
        mPhysics.AddCollider(Component.get());
        return std::move(Component);
    }

    std::unique_ptr<RendererRectangle> FactoryComponent::CreateComponentRendererRectangle(
            utils::Width aWidth,
            utils::Height aHeight) const
    {
        auto Component = std::make_unique<RendererRectangle>(aWidth, aHeight);
        auto* DefaultShader = mShaderController.GetShader("Default");
        Component->SetShader(DefaultShader);

        return std::move(Component);
    }

    std::unique_ptr<RendererCircle> FactoryComponent::CreateComponentRendererCircle(
            utils::Radius aRadius,
            unsigned aVertexCount) const
    {
        auto Component = std::make_unique<RendererCircle>(aRadius, aVertexCount);
        auto* DefaultShader = mShaderController.GetShader("Default");
        Component->SetShader(DefaultShader);

        return std::move(Component);
    }

    std::unique_ptr<PhysicsBody> FactoryComponent::CreateComponentPhysicsBody() const
    {
        auto Component = std::make_unique<PhysicsBody>();
        return std::move(Component);
    }
}
