//
// Created by Josep on 14/08/2018.
//

#ifndef ZEPTOLABTEST_FACTORYCOMPONENT_H
#define ZEPTOLABTEST_FACTORYCOMPONENT_H

#include "../graphics/shaders/ShaderController.h"
#include "../graphics/camera/CameraController.h"
#include "../physics/WorldPhysics.h"

#include <memory>


/**
 * This class is used to build components. Components are code blocks that allows specific behaviours
 * for the nodes.
 */
namespace scene
{
    class RendererCircle;
    class RendererRectangle;
    class ColliderBox;
    class ColliderCircle;
    class PhysicsBody;
    class FactoryComponent final
    {
    public:
        /**
         * Constructor.
         * @param aShaderController Reference to the shader controller.
         * @param aCameraController Reference to the camera controller.
         * @param aPhysics Reference to the world physics object.
         */
        FactoryComponent(const graphics::ShaderController& aShaderController,
                         const graphics::CameraController& aCameraController,
                         physics::WorldPhysics& aPhysics);

        /**
         * Non movable, nor copyable class.
         */
        FactoryComponent(FactoryComponent&& aOther) = delete;
        FactoryComponent(const FactoryComponent& aOther) = delete;
        FactoryComponent& operator=(FactoryComponent&& aOther) = delete;
        FactoryComponent& operator=(FactoryComponent& aOther) = delete;

        /**
         * Create a box collider component. This component allows the node to collide with other
         * colliders in the world.
         * @param aWidth Width of the box collider.
         * @param aHeight Height of the box collider.
         * @return Unique pointer to the created component.
         */
        std::unique_ptr<ColliderBox> CreateComponentColliderBox(utils::Width aWidth,
                                                                utils::Height aHeight);

        /**
         * Create a circle collider component. This component allows the node to collide with other
         * colliders in the world.
         * @param aRadius Radius of the circle collider.
         * @return Unique pointer to the created component.
         */
        std::unique_ptr<ColliderCircle> CreateComponentColliderCircle(utils::Radius aRadius);

        /**
         * Create a renderer rectangle component. This component allows the node to be drawn as a
         * rectangle.
         * @param aWidth Width of the circle.
         * @param aHeight Height of the circle.
         * @return Unique pointer to the created component.
         */
        std::unique_ptr<RendererRectangle> CreateComponentRendererRectangle(utils::Width aWidth,
                                                                            utils::Height aHeight) const;

        /**
         * Create a renderer circle component. This component allows the node to be drawn as a
         * circle.
         * @param aRadius Radius of the circle.
         * @param aVertexCount The larger vertexCount, more expensive to draw the circle.
         * @return Unique pointer to the created component.
         */
        std::unique_ptr<RendererCircle> CreateComponentRendererCircle(utils::Radius aRadius,
                                                                      unsigned aVertexCount) const;

        /**
         * Create a physics body component. This component allows the node to be affected by
         * the world forces (i.e gravity).
         * @return Unique pointer to the created component.
         */
        std::unique_ptr<PhysicsBody> CreateComponentPhysicsBody() const;

    private:
        // Reference to shader controller.
        const graphics::ShaderController& mShaderController;
        // Reference to camera controller.
        const graphics::CameraController& mCameraController;
        // Reference to physics world, so we can push physic nodes and colliders into it.
        physics::WorldPhysics& mPhysics;
    };
}


#endif //ZEPTOLABTEST_FACTORYCOMPONENT_H
