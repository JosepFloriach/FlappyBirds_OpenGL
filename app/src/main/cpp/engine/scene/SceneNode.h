//
// Created by Josep on 13/08/2018.
//

#ifndef ZEPTOLABTEST_SCENE_NODE_H
#define ZEPTOLABTEST_SCENE_NODE_H

#include "Transform.h"

#include "components/Component.h"
#include "components/RendererRectangle.h"
#include "components/RendererCircle.h"
#include "components/PhysicsBody.h"
#include "components/ColliderBox.h"
#include "components/ColliderCircle.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <android/log.h>


/**
 * This class represents a node in the scene. A node is just a empty entity that have a place in the
 * world. It just can be moved, scaled or rotated, but it can't do anything else by itself. To add
 * behaviour to a node, some component must be added into it.
 */
namespace scene
{
    class Component;
    class SceneNode: public Transform<SceneNode>
    {
    public:
        /**
         * Constructor
         * @param aName Name of the node.
         */
        explicit SceneNode(const std::string& aName);

        /**
         * Destructor
         */
        virtual ~SceneNode();

        /**
         * Copy constructor.
         * @param aOther
         */
        SceneNode(const SceneNode& aOther);

        /**
         * Copy assignment operator.
         * @param aOther
         * @return
         */
        SceneNode& operator=(const SceneNode& aOther);

        /**
         * Move constructor
         * @param aOther
         */
        SceneNode(SceneNode&& aOther);

        /**
         * Move assignment operator.
         * @param aOther
         * @return
         */
        SceneNode& operator=(SceneNode&& aOther);

        /**
         * Updates the node and its components. If the node have children they are updated as well.
         * @param aDt Delta Time since last frame. In milliseconds.
         */
        virtual void Update(double aDt);

        /**
         * Get node name.
         * @return const reference std::string to node name.
         */
        const std::string& GetNodeName() const;

        /**
         * Get a reference to the parent's node.
         * @return
         */
        SceneNode& GetParent() const;

        /**
         * Creates a child node into the node.
         * @param aName Name of the child node.
         * @return Reference to the child node.
         */
        SceneNode& CreateChild(const std::string& aName);

        /**
         * Move the node over time, in a specific speed vector. Also, it moves all its childs and
         * components.
         * @param aMovement Speed Vector.
         */
        void Move(utils::Vector3<float> aMovement);

        /**
         * Sets the node absolute position. If the node has a parent, this method will not perform
         * any transform, because a child node only can be placed by SetRelativePosition method.
         * @param aPosition Absolute position to be set.
         */
        void SetPosition(utils::Vector3<float> aPosition);

        /**
         * Sets the local position of the node. This transform is applied to the local matrix.
         * @param aPosition Position relative to the center of the own node.
         */
        void SetLocalPosition(utils::Vector3<float> aPosition);

        /**
         * Sets the relative position of the node to its parent. If there is no parent, this method
         * will not perform any transform.
         * @param aPosition Position relative to the parent.
         */
        void SetRelativePosition(utils::Vector3<float> aPosition);

        /**
         * Rotate the node over time, taking the axis the center of the world.
         * @param aRotation Rotation speed in degrees.
         * @param aRotationAxis Axis of rotation.
         */
        void Rotate(utils::Degrees aRotation, utils::Vector3<float> aRotationAxis);

        /**
         * Rotate the node over time, taking the axis the center of the own node.
         * @param aRotation Rotation speed in degrees.
         * @param aRotationAxis Axis of rotation.
         */
        void RotateLocal(utils::Degrees aRotation, utils::Vector3<float> aRotationAxis);

        /**
         * Sets the absolute rotation of the node taking the axis the center of the world. These
         * transform is also applied to children of the node. If the node has a parent, this method
         * will not perform any transform, because the only way to change the rotation of a child
         * node, is with the method SetRelativeRotation.
         * @param aRotation Rotation in degrees.
         * @param aRotationAxis Axis of rotation.
         */
        void SetRotation(utils::Degrees aRotation, utils::Vector3<float> aRotationAxis);

        /**
         * Sets the local rotation of the node. This transform is applied over the local matrix.
         * @param aRotation Rotation in degrees.
         * @param aRotationAxis Axis of rotation.
         */
        void SetLocalRotation(utils::Degrees aRotation, utils::Vector3<float> aRotationAxis);

        /**
         * Sets the relative rotation of the node to its parent. If there is no parent, this method
         * will not perform any transform.
         * @param aRotation Rotation in degrees.
         * @param aRotationAxis Axis of rotation.
         */
        void SetRelativeRotation(utils::Degrees aRotation, utils::Vector3<float> aRotationAxis);

        /**
         * Scales the node over time. Scalation transform can only be applied to the local matrix.
         * @param aScaleFactor Scalation factor over time.
         */
        void Scale(utils::Vector3<float> aScaleFactor);

        /**
         * Sets the scale of the node. Scalation transform can only be applied to the local matrix.
         * However, all child will be applied with this transform also. If node is child of another
         * node, this method will not take any effect. Because the only way to scale a child node is
         * setting the relative scale to its parent with method SetRelativeScale.
         * @param aScale Scale to be applied.
         */
        void SetScale(utils::Vector3<float> aScale);

        /**
         * Sets the scale of the node. Scalation transform can only be applied to the local matrix.
         * Children of node will not be transformed. This transformation is only applied to the own
         * node.
         * @param aScale Scale to be applied.
         */
        void SetLocalScale(utils::Vector3<float> aScale);

        /**
         * Sets the relative scale of the node. If the node has no parent, this method will not take
         * any effect.
         * @param aScale Scale to be applied.
         */
        void SetRelativeScale(utils::Vector3<float> aScale);

        /***
         * Updates position in all components and children.
         */
        void UpdatePosition();

        /**
         * Updates scale in all components and children.
         */
        void UpdateScale();

        /**
         * Updates rotation in all components and children.
         */
        void UpdateRotation();

        /**
         * Get a reference to the list of components of this node.
         * @return Vector reference of unique_pointers to the components.
         */
        std::vector<std::unique_ptr<Component>>& GetComponents();

        /**
         * Get a reference to the list of children of this node.
         * @return Vector reference of unique_pointers to the children.
         */
        std::vector<std::unique_ptr<SceneNode>>& GetChildren();

    public:

        /**
         * Adds an specified component to the components list in the node.
         * @tparam T
         * @param aComponent unique_ptr to the new component.
         */
        template <typename T>
        void AddComponent(std::unique_ptr<T> aComponent)
        {
            if (GetComponent<T>() == nullptr)
            {
                aComponent->SetNodeContainer(this);
                mComponents.push_back(std::move(aComponent));
                __android_log_print(ANDROID_LOG_DEBUG,"ZEPTOLAB_TEST_SCENE",
                                    "Adding component of type %s to the node %s",
                                    aComponent->Type().c_str(),
                                    GetNodeName().c_str());
            }
            else
            {
                throw std::runtime_error("This component has been already added to this node. "
                                                 "You can't add another one of the same type.");
            }
        }

        /**
         * Returns a pointer to the component type specified. If this node does not contain the
         * specified component, returns nullptr.
         * @tparam T Type of component we are trying to get.
         * @return  Pointer to the component, or nullptr if it does not exist in the node.
         */
        template <typename T>
        T* GetComponent()
        {
            if (mComponents.empty())
                return nullptr;

            Component* ComponentToReturn = nullptr;
            std::for_each(std::begin(mComponents), std::end(mComponents), [&ComponentToReturn](std::unique_ptr<Component>& Component)
            {
                if (Component->Type() == T::type )
                {
                    ComponentToReturn = Component.get();
                }
            });
            return dynamic_cast<T*>(ComponentToReturn);
        }


    protected:

        // List with all node children.
        std::vector<std::unique_ptr<SceneNode>> mChildren;

        // Node name.
        const std::string mName;

        // Parent of the node.
        SceneNode* mParent;

        // List with all node components.
        std::vector<std::unique_ptr<Component>> mComponents;
    };
}

#endif //ZEPTOLABTEST_SCENE_NODE_H
