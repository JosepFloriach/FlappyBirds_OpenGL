//
// Created by Josep on 31/08/2018.
//

#ifndef ZEPTOLABTEST_SHAPECIRCLE_H
#define ZEPTOLABTEST_SHAPECIRCLE_H

#include "Shape.h"

namespace graphics
{
    class ShapeCircle final: public Shape
    {
    public:

        /**
         * Constructor.
         * @param aRadius Radius of the circle.
         * @param aVertexCount The vertex count will condition the quality of the circle.
         */
        ShapeCircle(utils::Radius aRadius, unsigned aVertexCount);

        /**
         * Draws the circle.
         */
        virtual void Draw() override;

        /***
         * Clones a Shape circle.
         * @return
         */
        virtual std::unique_ptr<Shape> Clone() const override;

    private:
        // Vertex count determines circle quality.
        unsigned mVertexCount;
    };
}


#endif //ZEPTOLABTEST_SHAPECIRCLE_H
