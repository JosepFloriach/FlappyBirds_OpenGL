//
// Created by Josep on 22/08/2018.
//

#ifndef ZEPTOLABTEST_SHAPERENDERER_H
#define ZEPTOLABTEST_SHAPERENDERER_H

#include "Renderer.h"
#include "../../graphics/drawable/Shape.h"
#include <memory>

/**
 * Abstract class. Must be implemented for each concrete Shape Renderer.
 * ShapeRenderer is an abstraction of a component that allows us to render geometric shapes. For
 * example, rectangles, circles, triangles, and any other polygon drawn in OpenGl.
 */
namespace scene
{
    class SceneNode;
    class ShapeRenderer : public Renderer
    {
    public:

        /**
         * Destructor.
         */
        virtual ~ShapeRenderer();

        /**
         * Default constructor.
         */
        ShapeRenderer();

        /**
         * Copy constructor.
         * @param aOther
         */
        ShapeRenderer(const ShapeRenderer& aOther);

        /**
         * Move constructor.
         * @param aOther
         */
        ShapeRenderer(ShapeRenderer&& aOther);

        /**
         * Copy assignment
         * @param aOther
         * @return
         */
        ShapeRenderer& operator=(const ShapeRenderer& aOther);

        /**
         * Move assignment
         * @param aOther
         * @return
         */
        ShapeRenderer& operator=(ShapeRenderer&& aOther);

        /**
         * Sets color of the shape.
         * @param aColor
         */
        virtual void SetColor(utils::Color aColor) final;

    protected:

        /***
         * Draws the shape.
         */
        virtual void Draw() override;

        /**
         * Updates position, scale and rotation of the shape.
         */
        virtual void UpdateTransform() override;

    protected:
        // Unique pointer to the shape.
        std::unique_ptr<graphics::Shape> mShape;

        // Color of the shape.
        utils::Color mColor;
    };
}
#endif //ZEPTOLABTEST_SHAPERENDERER_H
