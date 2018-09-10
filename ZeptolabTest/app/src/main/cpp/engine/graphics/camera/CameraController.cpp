
// Created by Josep on 11/08/2018.
//

#include "CameraController.h"

#include <map>
#include <GLES2/gl2.h>

namespace graphics
{
    class CameraControllerImpl
    {
    private:
        // Map of cameras in the scene.
        typedef std::map<std::string, Camera> tCamerasMap;
        tCamerasMap mCameras;
        // Pointer to the current camera.
        Camera* mCurrentCamera;
        // Device display width
        utils::Width mDisplayWidth;
        // Device display height.
        utils::Height mDisplayHeight;
        // Target resolution width
        utils::Width mTargetWidth;
        // Target resolution height.
        utils::Height mTargetHeight;
    public:
        CameraControllerImpl(utils::Width aDisplayWidth,
                             utils::Height aDisplayHeight)
                : mDisplayWidth(aDisplayWidth)
                , mDisplayHeight(aDisplayHeight)
                , mTargetWidth(utils::Width(800.f))
                , mTargetHeight(utils::Height(600.f))
        {
        }

        void Init()
        {
            AddCamera("Default");
            SetCurrentCamera("Default");

            GetCurrentCamera().SetProjectionMode(Camera::PM_PERSPECTIVE);
            GetCurrentCamera().SetNear(0.1f);
            GetCurrentCamera().SetFar(1000.0f);
            GetCurrentCamera().SetFOV(utils::Degrees(45.f));
        }

        void AddCamera(const std::string& aName)
        {
            mCameras[aName] = std::move(Camera());
        }

        void SetCurrentCamera(const std::string& aName)
        {
            if (mCameras.count(aName) == 0)
                throw std::runtime_error("This camera does not exist!");
            mCurrentCamera = &mCameras.at(aName);
        }

        Camera& GetCurrentCamera() const
        {
            if (mCameras.size() == 0)
                throw std::runtime_error("There are no cameras yet!");
            return *mCurrentCamera;
        }

        void SetTargetResolution(utils::Width aWidth,
                                 utils::Height aHeight)
        {
            mTargetWidth = aWidth;
            mTargetHeight = aHeight;

            UpdateViewport();
            GetCurrentCamera().SetTargetResolution(aWidth, aHeight);
        }

        void UpdateViewport()
        {
            float DisplayWidth = mDisplayWidth.value;
            float DisplayHeight = mDisplayHeight.value;

            auto CurrentWidth = 0;
            auto CurrentHeight = 0;
            auto ViewPortX = 0.f;
            auto ViewPortY = 0.f;

            if (std::min(DisplayWidth, DisplayHeight) == DisplayWidth)
            {
                CurrentWidth = DisplayWidth;
                CurrentHeight = DisplayWidth * mTargetHeight.value / mTargetWidth.value;
                if (CurrentHeight > DisplayHeight)
                {
                    CurrentHeight = DisplayHeight;
                    CurrentWidth = DisplayHeight * mTargetWidth.value / mTargetHeight.value;
                    ViewPortX = DisplayWidth/2.0f - CurrentWidth/2.0f;
                }
                else
                {
                    ViewPortY = DisplayHeight/2.0f - CurrentHeight/2.0f;
                }
            }
            else
            {
                CurrentHeight = DisplayHeight;
                CurrentWidth = DisplayHeight * mTargetWidth.value / mTargetHeight.value;
                if (CurrentWidth > DisplayWidth)
                {
                    CurrentWidth = DisplayWidth;
                    CurrentHeight = DisplayWidth * mTargetHeight.value / mTargetWidth.value;
                    ViewPortX = DisplayWidth/2.0f - CurrentWidth/2.0f;
                }
                else
                {
                    ViewPortX = DisplayWidth/2.0f - CurrentWidth/2.0f;
                }
            }

            glViewport(ViewPortX, ViewPortY, CurrentWidth, CurrentHeight);
        }
    };

    CameraController::CameraController(utils::Width aDisplayWidth, utils::Height aDisplayHeight)
        : mImpl(std::make_unique<CameraControllerImpl>(aDisplayWidth, aDisplayHeight))
    {
    }

    CameraController::~CameraController() = default;

    void CameraController::Init()
    {
        mImpl.get()->Init();
    }

    void CameraController::AddCamera(const std::string& aName)
    {
        mImpl.get()->AddCamera(aName);
    }

    void CameraController::SetCurrentCamera(const std::string& aName)
    {
        mImpl.get()->SetCurrentCamera(aName);
    }

    Camera& CameraController::GetCurrentCamera() const
    {
        return mImpl.get()->GetCurrentCamera();
    }

    void CameraController::SetTargetResolution(utils::Width aWidth,
                                               utils::Height aHeight)
    {
        mImpl.get()->SetTargetResolution(aWidth, aHeight);
    }
}
