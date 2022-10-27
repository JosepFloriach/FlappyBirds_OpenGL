//
// Created by Josep on 01/09/2018.
//

#ifndef ZEPTOLABTEST_COLLIDER_H
#define ZEPTOLABTEST_COLLIDER_H

#include "Component.h"

/**
 * This class is just a layer over colliders to allow the world of physics to have a common interface
 * between all colliders. It's like an Strategy pattern but with no common methods/functions.
 */
namespace scene
{
    class Collider : public Component
    {
    public:
        /**
         *  Destructor.
         */
        virtual ~Collider() = default;

        /**
         * Constructors, assignment and move operator.
         */
        Collider() = default;
        Collider(Collider&& aOther) = default;
        Collider(const Collider& aOther) = default;
        Collider& operator=(const Collider& aOther) = default;
        Collider& operator=(Collider&& aOther) = default;
    };
};


#endif //ZEPTOLABTEST_COLLIDER_H
