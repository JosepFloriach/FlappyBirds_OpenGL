//
// Created by Josep on 21/08/2018.
//

#ifndef ZEPTOLABTEST_COMPONENT_H
#define ZEPTOLABTEST_COMPONENT_H

#include "../Transform.h"


/**
 * This class is an abstract class. It represents a Component. A component provides a specific
 * behaviour associated to a dummy node.
 */
namespace scene
{
    class SceneNode;
    class Component : public Transform<Component>
    {
    public:
        using ComponentDescriptor = std::string;
        /**
         * Identifier of the component
         */
        const static ComponentDescriptor descriptor;

        /**
         * Destructor
         */
        virtual ~Component();

        /**
         * Default constructor.
         */
        Component();

        /**
         * Move constructor.
         * @param aOther
         */
        Component(Component&& aOther);

        /**
         * Copy constructor.
         * @param aOther
         */
        Component(const Component& aOther);

        /**
         * Copy operator.
         * @param aOther
         * @return
         */
        Component& operator=(const Component& aOther);

        /**
         * Move operator.
         * @param aOther
         * @return
         */
        Component& operator=(Component&& aOther);

        /**
         * Function to return a clone of a concrete component.
         * @return
         */
        virtual std::unique_ptr<Component> Clone() const = 0;

        /**
         * Updates the component.
         * @param aDt Time in milliseconds since las frame.
         */
        virtual void Update(double aDt) = 0;

        /**
         * Get the identifier of the component. This function must be implemented in all concrete
         * components
         * @return ComponentDescriptor.
         */
        virtual ComponentDescriptor Type() const = 0;

        /**
         * Sets the node containing this component
         * @param aNode Pointer to the node.
         */
        virtual void SetNodeContainer(scene::SceneNode *aNode);

        /**
         * Gets the pointer to the node containing this component.
         * @return Pointer to the node.
         */
        scene::SceneNode* GetNodeContainer() const;

        /**
         * Updates position of the component.
         */
        void UpdatePosition();

        /**
         * Updates rotation of the component
         */
        void UpdateRotation();

        /**
         * Updates scale of the component.
         */
        void UpdateScale();

    protected:

        // Node containing this component.
        scene::SceneNode *mNode;
    };
}

#endif //ZEPTOLABTEST_COMPONENT_H
