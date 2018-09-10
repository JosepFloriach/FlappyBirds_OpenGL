//
// Created by Josep on 13/08/2018.
//

#include "Shape.h"

#include "../glm/mat4x4.hpp"
#include "../glm/gtc/matrix_transform.hpp"

namespace graphics
{
    Shape::Shape()
        : mColor(utils::Color(1.0f, 1.0f, 1.0f))
    {
        // Generate vertex data buffer for this shape.
        glGenBuffers(1, &mBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
    }

    Shape::~Shape() = default;
    Shape::Shape(const Shape &aOther) = default;
    Shape::Shape(Shape &&aOther) = default;
    Shape& Shape::operator=(Shape &aOther) = default;
    Shape& Shape::operator=(Shape &&aOther) = default;

    void Shape::SetColor(utils::Color aColor)
    {
        mColor = aColor;
    }
};