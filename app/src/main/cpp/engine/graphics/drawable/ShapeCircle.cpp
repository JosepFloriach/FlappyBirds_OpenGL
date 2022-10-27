//
// Created by Josep on 31/08/2018.
//

#include "ShapeCircle.h"
#include <math.h>

namespace graphics
{
    ShapeCircle::ShapeCircle(utils::Radius aRadius, unsigned aVertexCount)
        : Shape()
        , mVertexCount(aVertexCount)
    {
        // Initialize vertex data with the center. It will be always at (0, 0, 0).
        GLfloat VertexData[mVertexCount * 3];
        VertexData[0] = 0.f;
        VertexData[1] = 0.f;
        VertexData[2] = 0.f;

        // Fill vertex data. To do that, we must apply the parametric
        // equation of the circumference:
        // x = center + radius * cos(angle)
        // y = center + radius * sin(angle)
        // Since all our shapes are centered in the local (0,0) there
        // is no need to add the center.
        for (auto iVertex = 1; iVertex < mVertexCount; ++iVertex)
        {
             // Calculate the angle for the point we are looking for.
            auto SubDivision = (iVertex / (float) (mVertexCount - 2));
            auto Angle = SubDivision * 2 * (float) utils::PI;

            // Vertex position
            auto VertexX = aRadius.value * cos(Angle);
            auto VertexY = aRadius.value * sin(Angle);

            VertexData[iVertex * 3 + 0] = VertexX;
            VertexData[iVertex * 3 + 1] = VertexY;
            VertexData[iVertex * 3 + 2] = 0.f;
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);
    }

    void ShapeCircle::Draw()
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

        glDrawArrays(GL_TRIANGLE_FAN, 0, mVertexCount);
    }

    std::unique_ptr<Shape> ShapeCircle::Clone() const
    {
        return std::make_unique<ShapeCircle>(*this);
    }
}