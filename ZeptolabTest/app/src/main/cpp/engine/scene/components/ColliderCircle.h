//
// Created by Josep on 01/09/2018.
//

#ifndef ZEPTOLABTEST_COLLIDERCIRCLE_H
#define ZEPTOLABTEST_COLLIDERCIRCLE_H

#include "Collider.h"

/**
 * This class represents a Circle Collider. The circle collider just needs a Radius to be defined.
 * Unlike a graphic circle, a circle collider does not need a "quality" or "vertexCount" attribute,
 * because is just a mathematical representation of a circle.
 */
namespace scene
{
    class ColliderCircle final : public Collider
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
         * @param aRadius Radius of the collider.
         */
        explicit ColliderCircle(utils::Radius aRadius);

        /**
         * Function to return a clone of a collider box.
         * @return
         */
        std::unique_ptr<Component> Clone() const override;

        /**
         * Nothing to update in the collider. But it must be implemented.
         * @param aDt
         */
        void Update(double aDt) override;

        /**
         * Gets the collider circle radius.
         * @return utils::Radius
         */
        utils::Radius GetRadius() const;

    private:

        // Radius of the collider.
        utils::Radius mRadius;
    };
};


#endif //ZEPTOLABTEST_COLLIDERCIRCLE_H
