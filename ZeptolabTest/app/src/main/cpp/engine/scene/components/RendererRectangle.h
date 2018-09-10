//
// Created by Josep on 21/08/2018.
//

#ifndef ZEPTOLABTEST_RENDERERRECTANGLE_H
#define ZEPTOLABTEST_RENDERERRECTANGLE_H

#include "ShapeRenderer.h"

/**
 * This component allows the node that is attached, to be rendered as a rectangle.
 */
namespace scene
{
    class SceneNode;
    class RendererRectangle final: public ShapeRenderer
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
         * @param aWidth Width of rectangle.
         * @param aHeight Height of rectangle.
         */
        RendererRectangle(utils::Width aWidth, utils::Height aHeight);

        /**
         * Function to return a clone of a renderer rectangle.
         * @return
         */
        std::unique_ptr<Component> Clone() const override;
    };
}

#endif //ZEPTOLABTEST_RENDERERRECTANGLE_H
