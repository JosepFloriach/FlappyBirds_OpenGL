//
// Created by Josep on 13/08/2018.
//

#ifndef ZEPTOLABTEST_SHAPESQUARE_H
#define ZEPTOLABTEST_SHAPESQUARE_H

#include "Shape.h"

namespace graphics
{
    class ShapeRectangle final : public Shape
    {
    public:

        /**
         * Constructor
         * @param aWidth Width of rectangle
         * @param aHeight Height of rectangle.
         */
        ShapeRectangle(utils::Width aWidth, utils::Height aHeight);

        /**
         * Draws the rectangle.
         */
        virtual void Draw() override;

        /**
         * Clones a Shape rectangle.
         * @return
         */
        virtual std::unique_ptr<Shape> Clone() const override;
    };
}

#endif //ZEPTOLABTEST_SHAPESQUARE_H
