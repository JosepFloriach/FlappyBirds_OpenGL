//
// Created by Josep on 13/08/2018.
//

#ifndef ZEPTOLABTEST_SHAPE_H
#define ZEPTOLABTEST_SHAPE_H

#include "../../common/Utils.h"
#include <GLES2/gl2.h>

namespace graphics
{
    class Shape
    {
    public:
        /**
         * Constructor.
         */
        Shape();

        /**
         * Destructor
         */
        virtual ~Shape();

        /**
         * Copy constructor
         * @param aOther
         */
        Shape(const Shape& aOther);

        /**
         * Move constructor.
         * @param aOther
         */
        Shape(Shape&& aOther);

        /**
         * Copy operator.
         * @param aOther
         * @return
         */
        Shape& operator=(Shape& aOther);

        /**
         * Move operator.
         * @param aOther
         * @return
         */
        Shape& operator=(Shape&& aOther);

        /**
         * Draws the shape.
         */
        virtual void Draw() = 0;

        /**
         * Method to clone a polymorphic class.
         * @return
         */
        virtual std::unique_ptr<Shape> Clone() const = 0;

        /**
         * Sets the color of the shape.
         * @param aColor Color to be set.
         */
        void SetColor(utils::Color aColor);

    protected:
        // Buffer containing data vertices
        GLuint mBufferId;
        // Color of the shape. White by default.
        utils::Color mColor;
    };
}


#endif //ZEPTOLABTEST_SHAPE_H
