//
// Created by Josep on 13/08/2018.
//

#include "SceneNode.h"

#include "../graphics/glm/gtc/matrix_transform.hpp"

namespace scene
{
    SceneNode::SceneNode(const std::string& aName)
        : mName(aName)
        , mParent(nullptr)
    {
    };

    SceneNode::~SceneNode()
    {
        mComponents.clear();
        mChildren.clear();
    }

    SceneNode::SceneNode(const SceneNode &aOther)
    {
        std::transform(std::begin(aOther.mComponents), std::end(aOther.mComponents),
        std::back_inserter(mComponents), [](const std::unique_ptr<Component>& Comp)
        {
            return Comp->Clone();
        });

        std::transform(std::begin(aOther.mChildren), std::end(aOther.mChildren),
        std::back_inserter(mChildren), [](const std::unique_ptr<SceneNode>& Child)
        {
            return  std::make_unique<SceneNode>(*Child);
        });
    }

    SceneNode& SceneNode::operator=(const SceneNode &aOther)
    {
        SceneNode Tmp(aOther);
        std::swap(*this, Tmp);
        return *this;
    }

    SceneNode::SceneNode(SceneNode &&aOther)
        : mComponents(std::move(aOther.mComponents))
        , mChildren(std::move(aOther.mChildren))
    {
    }

    SceneNode& SceneNode::operator=(SceneNode &&aOther)
    {
        std::swap(mComponents, aOther.mComponents);
        std::swap(mChildren, aOther.mChildren);
        return *this;
    }

    const std::string& SceneNode::GetNodeName() const
    {
        return mName;
    }

    SceneNode& SceneNode::GetParent() const
    {
        return *mParent;
    }

    SceneNode& SceneNode::CreateChild(const std::string& aName)
    {
        std::unique_ptr<SceneNode> Node = std::make_unique<SceneNode>(aName);
        Node->mParent = this;
        mChildren.push_back(std::move(Node));
        return *mChildren.back();
    }

    std::vector<std::unique_ptr<SceneNode>>& SceneNode::GetChildren()
    {
        return mChildren;
    }

    std::vector<std::unique_ptr<Component>>& SceneNode::GetComponents()
    {
        return mComponents;
    }

    void SceneNode::Move(utils::Vector3<float> aMovement)
    {
        mPosition += aMovement;
        for (auto& Child: mChildren)
        {
            if (Child)
            {
                Child->Move(aMovement);
            }
        }
        UpdatePosition();
    }

    void SceneNode::SetPosition(utils::Vector3<float> aPosition)
    {
        if (!mParent)
        {
            mPosition = aPosition;
            for (auto& Child: mChildren)
            {
                if (Child)
                {
                    Child->SetPosition(aPosition);
                }
            }
            UpdatePosition();
        }
        else
        {
            __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SCENE",
                                "You are trying to set absolute position for a child node. Use "
                                        "SetRelativePosition instead.");
        }
    }

    void SceneNode::SetLocalPosition(utils::Vector3<float> aPosition)
    {
        mLocalPosition = aPosition;
        UpdatePosition();
    }

    void SceneNode::SetRelativePosition(utils::Vector3<float> aPosition)
    {
        if (mParent)
        {
            mRelativePosition = aPosition;
            mPosition = mParent->GetPosition() + mRelativePosition;
            UpdatePosition();
        }
        else
        {
            __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SCENE",
                                "You are trying to set relative position for a node with no parent."
                                        " Use SetPosition instead.");
        }
    }

    void SceneNode::RotateLocal(utils::Degrees aRotation, utils::Vector3<float> aRotationAxis)
    {
        mLocalRotationAxis = aRotationAxis;
        mLocalRotation += aRotation;
        UpdateRotation();
    }

    void SceneNode::Rotate(utils::Degrees aRotation, utils::Vector3<float> aRotationAxis)
    {
        mRotationAxis = aRotationAxis;
        mRotation += aRotation;
        for (auto& Child: mChildren)
        {
            if (Child)
            {
                Child->Rotate(aRotation, aRotationAxis);
            }
        }
        UpdateRotation();
    }

    void SceneNode::SetRotation(utils::Degrees aRotation,
                                 utils::Vector3<float> aRotationAxis)
    {
        if (!mParent)
        {
            mRotationAxis = aRotationAxis;
            mRotation = aRotation;
            for (auto& Child: mChildren)
            {
                if (Child)
                {
                    Child->SetRotation(aRotation, aRotationAxis);
                }
            }
            UpdateRotation();
        }
        else
        {
            __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SCENE",
                                "You are trying to set absolute rotation for a child node. Use "
                                        "SetRelativeRotation instead.");
        }
    }

    void SceneNode::SetRelativeRotation(utils::Degrees aRotation,
                                         utils::Vector3<float> aRotationAxis)
    {
        if (mParent)
        {
            mRotation = mParent->GetRotation() + mRelativeRotation;
            mRotationAxis = mRelativeRotationAxis;
            UpdateRotation();
        }
        else
        {
            __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SCENE",
                                "You are trying to set relative rotation for a node with no parent."
                                        " Use SetRotation instead.");
        }
    }

    void SceneNode::SetLocalRotation(utils::Degrees aRotation,
                                      utils::Vector3<float> aRotationAxis)
    {
        mLocalRotationAxis = aRotationAxis;
        mLocalRotation = aRotation;
        UpdateRotation();
    }

    void SceneNode::Scale(utils::Vector3<float> aScaleFactor)
    {
        mLocalScale += aScaleFactor;
        for (auto& Child: mChildren)
        {
            if (Child)
            {
                Child->Scale(aScaleFactor);
            }
        }
        UpdateScale();
    }

    void SceneNode::SetScale(utils::Vector3<float> aScale)
    {
        if (!mParent)
        {
            mLocalScale = aScale;
            for (auto& Child: mChildren)
            {
                if (Child)
                {
                    Child->SetScale(aScale);
                }
            }
            UpdateScale();
        }
        else
        {
            __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SCENE",
                                "You are trying to set absolute scale for a child node."
                                        " Use SetRelativeScale instead.");
        }
    }

    void SceneNode::SetLocalScale(utils::Vector3<float> aScale)
    {
        mLocalScale = aScale;
        UpdateScale();
    }

    void SceneNode::SetRelativeScale(utils::Vector3<float> aScale)
    {
        if (mParent)
        {
            mLocalScale = mParent->GetScale() + mRelativeScale;
            UpdateScale();
        }
        else
        {
            __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SCENE",
                                "You are trying to set relative scale for a node with no parent."
                                        " Use SetScale instead.");
        }
    }


    void SceneNode::Update(double aDt)
    {
        // Update each component in the scene node.
        for(auto& Component: mComponents)
        {
            if (Component)
            {
                Component.get()->Update(aDt);
            }
        }

        for (auto& Child: mChildren)
        {
            if (Child)
            {
                Child->Update(aDt);
            }
        }
    }

    void SceneNode::UpdatePosition()
    {
        for(auto& Component: mComponents)
        {
            if (Component)
            {
                Component.get()->UpdatePosition();
            }
        }

        for (auto& Child: mChildren)
        {
            if (Child)
            {
                Child->UpdatePosition();
            }
        }
    }

    void SceneNode::UpdateScale()
    {
        for(auto& Component: mComponents)
        {
            if (Component)
            {
                Component.get()->UpdateScale();
            }
        }

        for (auto& Child: mChildren)
        {
            if (Child)
            {
                Child->UpdateScale();
            }
        }
    }

    void SceneNode::UpdateRotation()
    {
        for(auto& Component: mComponents)
        {
            if (Component)
            {
                Component.get()->UpdateRotation();
            }
        }

        for (auto& Child: mChildren)
        {
            if (Child)
            {
                Child->UpdateRotation();
            }
        }
    }

};