//
// Created by Josep on 01/09/2018.
//

#include "ColliderCircle.h"

namespace scene
{
    const Component::ComponentDescriptor ColliderCircle::type= "ColliderCircle";
    Component::ComponentDescriptor ColliderCircle::Type() const
    {
        return type;
    }

    ColliderCircle::ColliderCircle(utils::Radius aRadius)
        : mRadius(aRadius)
    {
    }

    std::unique_ptr<Component> ColliderCircle::Clone() const
    {
        return std::make_unique<ColliderCircle>(*this);
    }

    void ColliderCircle::Update(double aDt)
    {
        // Nothing to do.
    }

    utils::Radius ColliderCircle::GetRadius() const
    {
        return mRadius;
    }
}