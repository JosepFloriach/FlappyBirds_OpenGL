//
// Created by Josep on 21/08/2018.
//

#include "RendererCircle.h"
#include "../../graphics/drawable/ShapeCircle.h"

namespace scene
{
    const Component::ComponentDescriptor RendererCircle::type= "CircleRenderer";
    Component::ComponentDescriptor RendererCircle::Type() const
    {
        return type;
    }

    RendererCircle::RendererCircle(utils::Radius aRadius, unsigned aVertexCount)
            : ShapeRenderer()
    {
        mShape = std::make_unique<graphics::ShapeCircle>(aRadius, aVertexCount);
    }

    std::unique_ptr<Component> RendererCircle::Clone() const
    {
        return std::make_unique<RendererCircle>(*this);
    }
}