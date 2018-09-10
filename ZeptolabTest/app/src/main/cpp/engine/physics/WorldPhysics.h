//
// Created by Josep on 28/08/2018.
//

#ifndef ZEPTOLABTEST_WORLDPHYSICS_H
#define ZEPTOLABTEST_WORLDPHYSICS_H

#include "../common/Vector3.h"
#include "../common/Utils.h"

#include <map>
#include <vector>

namespace scene
{
    class Collider;
    class ColliderBox;
    class ColliderCircle;
}

namespace physics
{
    class WorldPhysicsImpl;
    class WorldPhysics final
    {
    public:
        /**
         * Gravity force.
         */
        static utils::Vector3<float> Gravity;

        /**
         * Constructor
         */
        WorldPhysics();

        /**
         * Destructor.
         */
        ~WorldPhysics();

        /**
         * Non-copyable, non-moveable class.
         */
        WorldPhysics(WorldPhysics&& aOther) = delete;
        WorldPhysics(const WorldPhysics& aOther) = delete;
        WorldPhysics& operator=(const WorldPhysics& aOther) = delete;
        WorldPhysics& operator=(WorldPhysics&& aOther) = delete;

        /**
         * Updates the physics world.
         * @param aDtf Time in milliseconds since last frame.
         */
        void Update(double aDt);

        /**
         * Adds a collider to the physics world
         * @param aCollider Pointer to the collider to be added.
         */
        void AddCollider(scene::Collider* aCollider);

    private:

        // Pointer to implementation.
        std::unique_ptr<WorldPhysicsImpl> mImpl;
    };
}



#endif //ZEPTOLABTEST_WORLDPHYSICS_H
