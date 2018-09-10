//
// Created by Josep on 13/08/2018.
//

#ifndef ZEPTOLABTEST_SCENE_H
#define ZEPTOLABTEST_SCENE_H

#include <vector>

#include "FactoryComponent.h"

/**
 * Scene is an abstract class and must be implemented to create concrete scenes.
 * This class represents a scene. A scene is a container of Nodes and represents the game world. You
 * can add nodes, remove them, modify them... The Scene is updated and drawn every frame in the app.
 */
namespace scene
{
    class SceneNode;
    class Scene
    {
    public:
        /**
         * Constructor
         * @param aDisplayWidth Width of the display where will be drawn the scene.
         * @param aDisplayHeight Height of the display where will be drawn the scene.
         */
        Scene(utils::Width aDisplayWidth, utils::Height aDisplayHeight);

        /**
         * Destructor.
         */
        virtual ~Scene();

        /**
         * Non-movable, nor copyable class.
         * @param aOther
         */
        Scene(const Scene& aOther) = delete;
        Scene(Scene&& aOther) = delete;
        Scene& operator=(const Scene& aOther) = delete;
        Scene& operator=(Scene&& aOther) = delete;

        /**
         * Inits the scene. This method must be implemented by all the concrete scenes and it must
         * initialize the camera params, nodes, components...
         */
        virtual void Init() = 0;

        /**
         * Updates the scene. This method must be implemented by all the concrete scenes.
         * @param aDt
         */
        virtual void Update(double aDt) = 0;

        /**
         * Creates a node into the scene.
         * @param aName Name of the node to be created.
         * @return Reference to the node just created.
         */
        SceneNode& CreateNode(const std::string& aName);

        /**
         * Removes a node specified by its name.
         * @param aName Name of the node to be deleted.
         */
        void RemoveNode(const std::string& aName);

        /**
         * Returns a reference to the list with all nodes.
         * @return Reference to vector with unique_ptr to nodes.
         */
        std::vector<std::unique_ptr<SceneNode>>& GetAllNodes();

        /**
         * Draws the whole scene.
         * @param aDt Time in milliseconds since last frame.
         */
        virtual void Draw(double aDt);

        /**
         * This method is call when the user performs a Touch on the screen. By default, it does
         * nothing.
         * @param aX X position in display where the user has touched.
         * @param aY Y position in display where the user has touched.
         */
        virtual void OnTouch(float aX, float aY);

        /**
         * Gets the width of display where is being drawn the scene.
         * @return Utils::Width
         */
        utils::Width GetWidth() const;

        /**
         * Gets the height of display where is being drawn the scene.
         * @return Utils::Height
         */
        utils::Height GetHeight() const;

        /**
         * Gets a reference to the shader controller.
         * @return Reference to shader controller.
         */
        graphics::ShaderController& GetShaderController();

        /**
         * Gets a reference to the cam controller
         * @return Reference to the cam controller.
         */
        graphics::CameraController& GetCameraController();

        /**
         * Gets a reference to the components factory.
         * @return Reference to the components factory.
         */
        FactoryComponent& GetComponentFactory();

        /**
         * Gets a reference to the physics world object.
         * @return Reference to the physics world object.
         */
        physics::WorldPhysics& GetWorldPhysics();

    private:

        // Shader controller.
        graphics::ShaderController mShaderController;

        // Scene width
        utils::Width mWidth;

        // Scene height.
        utils::Height mHeight;

        // World physics.
        physics::WorldPhysics mWorldPhysics;

        // Cam controller
        graphics::CameraController mCameraController;

        // Component factory.
        FactoryComponent mFactoryComponent;

        // List with all nodes in the scene.
        std::vector<std::unique_ptr<SceneNode>> mSceneNodes;
    };

}
#endif //ZEPTOLABTEST_SCENE_H
