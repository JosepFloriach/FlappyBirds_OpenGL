//
// Created by Josep on 21/08/2018.
//

#ifndef ZEPTOLABTEST_RENDERERCIRCLE_H
#define ZEPTOLABTEST_RENDERERCIRCLE_H

#include "ShapeRenderer.h"

/**
 * This component allows the node that is attached, to be rendered as a circle.
 */
namespace scene
{
    class SceneNode;
    class RendererCircle final: public ShapeRenderer
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
         * @param aRadius Radius of the circle
         * @param aVertexCount Quality vertex of the circle. The longer, more expensive to be drawn.
         */
        RendererCircle(utils::Radius aRadius, unsigned aVertexCount);

        /**
         * Function to return a clone of a renderer circle.
         * @return
         */
        std::unique_ptr<Component> Clone() const override;

    };
}

#endif //ZEPTOLABTEST_RENDERERCIRCLE_H
