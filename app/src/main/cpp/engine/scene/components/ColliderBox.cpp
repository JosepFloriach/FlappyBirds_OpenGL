//
// Created by Josep on 01/09/2018.
//

#include "ColliderBox.h"

namespace scene
{
    const Component::ComponentDescriptor ColliderBox::type= "ColliderBox";
    Component::ComponentDescriptor ColliderBox::Type() const
    {
        return type;
    }

    ColliderBox::ColliderBox(utils::Width aWidth, utils::Height aHeight)
        : mWidth(aWidth)
        , mHeight(aHeight)
    {
    }

    std::unique_ptr<Component> ColliderBox::Clone() const
    {
        return std::make_unique<ColliderBox>(*this);
    }

    void ColliderBox::Update(double aDt)
    {
        // Nothing to do.
    }

    utils::Width ColliderBox::GetWidth() const
    {
        return mWidth;
    }

    utils::Height ColliderBox::GetHeight() const
    {
        return mHeight;
    }
}