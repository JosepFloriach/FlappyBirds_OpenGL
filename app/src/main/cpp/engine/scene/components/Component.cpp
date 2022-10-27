//
// Created by Josep on 23/08/2018.
//

#include "Component.h"
#include "../SceneNode.h"

namespace scene
{
    Component::Component()
            : mNode(nullptr)
    {
    }

    Component::~Component()
    {
        mNode = nullptr;
    }

    Component::Component(const Component &aOther) = default;
    Component::Component(Component &&aOther) = default;
    Component& Component::operator=(Component &&aOther) = default;
    Component& Component::operator=(const Component &aOther) = default;

    void Component::UpdatePosition()
    {
        if (mNode)
        {
            mPosition = mRelativePosition + mNode->GetPosition();
        }
    }

    void Component::UpdateScale()
    {
        if (mNode)
        {
            mLocalScale = mRelativeScale + mNode->GetScale();
        }
    }

    void Component::UpdateRotation()
    {
        if (mNode)
        {
            mLocalRotationAxis = mLocalRotationAxis + mNode->GetLocalRotationAxis();
            if (mNode->GetLocalRotation().value != 0)
            {
                mLocalRotation = mNode->GetLocalRotation();
            }

            mRotationAxis = mRelativeRotationAxis + mNode->GetRotationAxis();
            if (mNode->GetRotation().value != 0)
            {
                mRotation = mNode->GetRotation();
            }
        }
    }

    void Component::SetNodeContainer(scene::SceneNode *aNode)
    {
        mNode = aNode;
    }

    SceneNode* Component::GetNodeContainer() const
    {
        return mNode;
    }
}