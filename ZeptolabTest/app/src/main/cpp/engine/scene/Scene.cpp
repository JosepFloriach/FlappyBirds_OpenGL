//
// Created by Josep on 13/08/2018.
//

#include "Scene.h"
#include "SceneNode.h"
#include "../graphics/GlUtils.h"

namespace scene
{
    Scene::Scene(utils::Width aDisplayWidth, utils::Height aDisplayHeight)
        : mShaderController()
        , mWidth(aDisplayWidth)
        , mHeight(aDisplayHeight)
        , mWorldPhysics()
        , mCameraController(mWidth, mHeight)
        , mFactoryComponent(mShaderController, mCameraController, mWorldPhysics)
    {
        mShaderController.Init();
        mCameraController.Init();
    }

    Scene::~Scene()
    {
        mSceneNodes.clear();
    };

    SceneNode& Scene::CreateNode(const std::string &aName)
    {
        std::unique_ptr<SceneNode> Node = std::make_unique<SceneNode>(aName);
        mSceneNodes.push_back(std::move(Node));
        __android_log_print(ANDROID_LOG_DEBUG,"ZEPTOLAB_TEST_SCENE", "Adding node %s", aName.c_str());
        return *mSceneNodes.back();
    }

    void Scene::RemoveNode(const std::string& aName)
    {
        auto Iterator = find_if(mSceneNodes.begin(), mSceneNodes.end(), [&](std::unique_ptr<SceneNode>& Element)
        {
            return Element->GetNodeName() == aName;
        });
        if(Iterator != mSceneNodes.end())
        {
            __android_log_print(ANDROID_LOG_DEBUG,"ZEPTOLAB_TEST_SCENE", "Removing node %s", aName.c_str());
            (*Iterator)->GetChildren().clear();
            (*Iterator)->GetComponents().clear();
            mSceneNodes.erase(Iterator);
        }
    }

    void Scene::Draw(double aDt)
    {
        GlUtils::PreRender();
        mWorldPhysics.Update(aDt);
        for(auto& Node: mSceneNodes)
        {
            if (Node)
            {
                Node.get()->Update(aDt);
            }
        }
        GlUtils::PostRender();
    }

    std::vector<std::unique_ptr<SceneNode>>& Scene::GetAllNodes()
    {
        return mSceneNodes;
    }

    void Scene::OnTouch(float aX, float aY)
    {
        // Nothing to do. The concrete scene will implement these method if is needed.
    }

    graphics::CameraController& Scene::GetCameraController()
    {
        return mCameraController;
    }

    graphics::ShaderController& Scene::GetShaderController()
    {
        return mShaderController;
    }

    FactoryComponent& Scene::GetComponentFactory()
    {
        return mFactoryComponent;
    }

    physics::WorldPhysics& Scene::GetWorldPhysics()
    {
        return mWorldPhysics;
    }

    utils::Width Scene::GetWidth() const
    {
        return mWidth;
    }

    utils::Height Scene::GetHeight() const
    {
        return mHeight;
    }
}

