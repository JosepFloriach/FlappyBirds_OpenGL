//
// Created by Josep on 01/09/2018.
//

#ifndef ZEPTOLABTEST_COLLIDERBOX_H
#define ZEPTOLABTEST_COLLIDERBOX_H

#include "Collider.h"

/**
 *
 * This class represents a Box Collider. The box collider needs a height and a width to be defined.
 * It's just a mathematical representation of a box/square.
 */
namespace scene
{
    class ColliderBox final : public Collider
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
         * Constructor.
         * @param aWidth Width of box collider
         * @param aHeight Height of box collider.
         */
        ColliderBox(utils::Width aWidth, utils::Height aHeight);

        /**
         * Nothing to update in a box collider.
         * @param aDt Time in milliseconds since las frame.
         */
        void Update(double aDt) override;

        /**
         * Returns the withd of the box collider
         * @return utils::Width
         */
        utils::Width GetWidth() const;

        /**
         * Returns the height of the box collider.
         * @return utils::Height
         */
        utils::Height GetHeight() const;

        /**
         * Function to return a clone of a collider box.
         * @return
         */
        std::unique_ptr<Component> Clone() const override;

    private:
        // Width
        utils::Width mWidth;
        // Height.
        utils::Height mHeight;
    };
};


#endif //ZEPTOLABTEST_COLLIDERBOX_H
