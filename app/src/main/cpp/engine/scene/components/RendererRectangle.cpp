//
// Created by Josep on 21/08/2018.
//

#include "RendererRectangle.h"
#include "../../graphics/drawable/ShapeRectangle.h"

namespace scene
{
    const Component::ComponentDescriptor RendererRectangle::type= "RectangleRenderer";
    Component::ComponentDescriptor RendererRectangle::Type() const
    {
        return type;
    }

    RendererRectangle::RendererRectangle(utils::Width aWidth, utils::Height aHeight)
            : ShapeRenderer()
    {
        mShape = std::make_unique<graphics::ShapeRectangle>(aWidth, aHeight);
    }

    std::unique_ptr<Component> RendererRectangle::Clone() const
    {
        return std::make_unique<RendererRectangle>(*this);
    }
}