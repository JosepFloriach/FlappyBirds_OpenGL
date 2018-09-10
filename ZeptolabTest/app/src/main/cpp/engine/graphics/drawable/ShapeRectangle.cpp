//
// Created by Josep on 13/08/2018.
//

#include "ShapeRectangle.h"

namespace graphics
{
    ShapeRectangle::ShapeRectangle(utils::Width aWidth, utils::Height aHeight)
        : Shape()
    {
        // Square/rectangle is drawn by striping two triangles. We need
        // the coordinates of both of them. First of all we need to know
        // the distance from the center to the right limit of rectangle,
        // and the distance from the center to the top limit of rectangle.
        // These are used to know the 4 outer vertices of the square.
        auto Width = aWidth.value;
        auto Height = aHeight.value;
        auto DistCentRight = Width / 2.0f;
        auto DistCentTop = Height / 2.0f;

        // Build vertex data.
        const GLfloat VertexData[] = {
                -DistCentRight, DistCentTop,    0.0f,
                DistCentRight,  DistCentTop,    0.0f,
                DistCentRight,  -DistCentTop,   0.0f,

                -DistCentRight, -DistCentTop,   0.0f,
                -DistCentRight, DistCentTop,    0.0f,
                DistCentRight,  -DistCentTop,   0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
    }


    void ShapeRectangle::Draw()
    {
        glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) 0
        );

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    }

    std::unique_ptr<Shape> ShapeRectangle::Clone() const
    {
        return std::make_unique<ShapeRectangle>(*this);
    }
};
