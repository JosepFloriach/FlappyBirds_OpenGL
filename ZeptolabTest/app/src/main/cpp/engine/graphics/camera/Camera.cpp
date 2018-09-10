//
// Created by Josep on 15/08/2018.
//

#include "Camera.h"
#include "../glm/gtc/matrix_transform.hpp"

#include <GLES2/gl2.h>

namespace graphics
{
    glm::mat4 Camera::ProjectionMatrix = glm::mat4(1.0f);

    class CameraImpl
    {
    private:
        Camera::PROJECTION_MODE mProjectionMode;
        bool mZDepthEnabled;
        glm::mat4 mProjectionMatrix;
        utils::Width mTargetWidth;
        utils::Height mTargetHeight;
        float mFOV;
        float mNear;
        float mFar;

    public:

        CameraImpl()
                : mProjectionMode(Camera::PM_PERSPECTIVE)
                , mZDepthEnabled(false)
                , mProjectionMatrix(glm::mat4())
                , mTargetWidth (utils::Width(800.f))
                , mTargetHeight (utils::Height(600.f))
                , mFOV (0.7853f)
                , mNear (0.1f)
                , mFar(100.0f)
        {
        }

        void SetTargetResolution(utils::Width aWidth, utils::Height aHeight)
        {
            mTargetWidth = aWidth;
            mTargetHeight = aHeight;
            UpdateMatrix();
        }

        void SetProjectionMode(Camera::PROJECTION_MODE aMode)
        {
            mProjectionMode = aMode;
            UpdateMatrix();
        }

        void EnableZDepth(bool aEnable)
        {
            if (aEnable)
            {
                glEnable(GL_DEPTH_TEST);
            }
            else
            {
                glDisable(GL_DEPTH_TEST);
            }
            UpdateMatrix();
        }

        void SetFOV(utils::Degrees aValue)
        {
            mFOV = glm::radians(aValue.value);
            UpdateMatrix();
        }

        void SetFOV(utils::Radians aValue)
        {
            mFOV = aValue.value;
            UpdateMatrix();
        }

        void SetNear(float aValue)
        {
            mNear = aValue;
            UpdateMatrix();
        }

        void SetFar (float aValue)
        {
            mFar = aValue;
            UpdateMatrix();
        }

        void UpdateMatrix()
        {
            if (mProjectionMode == Camera::PM_ORTHO)
            {
                Camera::SetProjectionMatrix(
                        glm::ortho(-mTargetWidth.value / 2.0f,
                                   mTargetWidth.value / 2.0f,
                                   -mTargetHeight.value / 2.0f,
                                   mTargetHeight.value / 2.0f,
                                   mNear,
                                   mFar));
            }

            if (mProjectionMode == Camera::PM_PERSPECTIVE)
            {
                Camera::SetProjectionMatrix(
                        glm::perspective(mFOV,
                                         mTargetWidth.value / mTargetHeight.value,
                                         mNear,
                                         mFar));
            }
        };

        glm::mat4 GetProjectionMatrix() const
        {
            return mProjectionMatrix;
        }
    };

    Camera::Camera()
        : mImpl(std::make_unique<CameraImpl>())
    {
    }

    Camera::~Camera() = default;

    Camera::Camera(const Camera &aOther)
        : mImpl(std::make_unique<CameraImpl>(*aOther.mImpl))
    {
    }

    Camera::Camera(Camera &&aOther)
        : mImpl(std::move(aOther.mImpl))
    {
    }

    Camera& Camera::operator=(const Camera &aOther)
    {
        mImpl = std::make_unique<CameraImpl>(*aOther.mImpl);
        return *this;
    }

    Camera& Camera::operator=(Camera&& aOther)
    {
        mImpl = std::move(aOther.mImpl);
        return *this;
    }

    void Camera::SetTargetResolution(utils::Width aWidth, utils::Height aHeight)
    {
        mImpl.get()->SetTargetResolution(aWidth, aHeight);
    }

    void Camera::SetProjectionMode(PROJECTION_MODE aMode)
    {
        mImpl.get()->SetProjectionMode(aMode);
    }

    void Camera::SetNear(float aValue)
    {
        mImpl.get()->SetNear(aValue);
    }

    void Camera::SetFar(float aValue)
    {
        mImpl.get()->SetFar(aValue);
    }

    void Camera::SetFOV(utils::Radians aValue)
    {
        mImpl.get()->SetFOV(aValue);
    }

    void Camera::SetFOV(utils::Degrees aValue)
    {
        mImpl.get()->SetFOV(aValue);
    }

    void Camera::EnableZDepth(bool aEnable)
    {
        mImpl.get()->EnableZDepth(aEnable);
    }
}