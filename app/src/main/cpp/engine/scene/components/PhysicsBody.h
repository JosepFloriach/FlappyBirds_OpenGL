//
// Created by Josep on 29/08/2018.
//

#ifndef ZEPTOLABTEST_PHYSICSBODY_H
#define ZEPTOLABTEST_PHYSICSBODY_H

#include "Component.h"
#include <vector>

/**
 * This component allows the node that is attached, to be affected by physic forces.
 */
namespace scene
{
    class PhysicsBody final: public Component
    {
    public:
        /**
         * Identifier of this component
         */
        static const ComponentDescriptor type;

        /**
        * Get the identifier of this component.
        * @return ComponentDescriptor.
        */
        ComponentDescriptor Type() const override;

        /**
         * Constructor
         */
        PhysicsBody();

        /**
         * Function to return a clone of a collider box.
         * @return
         */
        std::unique_ptr<Component> Clone() const override;

        /**
         * Sets if the gravity should be applied to the node attached.
         * @param aApplyGravity Bool specifying if gravity should be applied.
         */
        void SetApplyGravity(bool aApplyGravity);

        /**
         * Returns if gravity is applied to the node attached.
         * @return
         */
        bool IsGravityApplied() const;

        /**
         * Updates the component.
         * @param aDt Time in milliseconds since the last frame.
         */
        void Update(double aDt) override;

        /**
         * Adds a force to the physics body.
         * @param aForce Vector3 specifying the force direction.
         */
        void AddForce(utils::Vector3<float> aForce);

        /**
         * Stops all forces. All physics are stopped and the node attached stops its movement derived
         * from the physics.
         */
        void Stop();

    private:
        // Current force applied.
        utils::Vector3<float> mForce;
        // Is gravity applied?
        bool mApplyGravity;
        // Current velocity.
        utils::Vector3<float> mVelocity;
    };
}

#endif //ZEPTOLABTEST_PHYSICSBODY_H
