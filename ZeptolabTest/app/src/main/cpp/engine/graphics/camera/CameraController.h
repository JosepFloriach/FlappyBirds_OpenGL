//
// Created by Josep on 11/08/2018.
//

#ifndef ZEPTOLABTEST_CAMERACONTROLLER_H
#define ZEPTOLABTEST_CAMERACONTROLLER_H

#include <memory>
#include <string>

#include "Camera.h"

namespace graphics
{
    class CameraControllerImpl;
    class CameraController
    {
    public:

        /**
         * Constructor.
         */
        CameraController(utils::Width aDisplayWidth, utils::Height aDisplayHeight);

        /**
         * Destructor.
         */
        ~CameraController();

        /**
         * Non-copyable, non-moveable class.
         */
        CameraController(const CameraController& aOther) = delete;
        CameraController(CameraController&& aOther) = delete;
        CameraController& operator=(const CameraController& aOther) = delete;
        CameraController& operator=(CameraController&& aOther) = delete;

        /**
         * Load a default camera.
         */
        void Init();

        /**
         * Adds a perspective camera to be used later.
         * @param aName String identifying the camera, so it can be found when the user wants to use it.
         */
        void AddCamera(const std::string& aName);

        /**
         * Gets a reference to the current camera object.
         */
        Camera& GetCurrentCamera() const;

        /**
         * Sets the current camera object. If the camera name does not exist, it will throw
         * an error.
         * @param aName Name of the camera previously added.
         */
        void SetCurrentCamera(const std::string& aName);

        /**
         * Sets the desired target resolution for the game. This resolution will set the aspect
         * ratio to be used in the game, and it will be forced in any device while this camera is
         * default camera. If device physical resolution does not fit into the desired target
         * resolution, pillarboxes will be added on bottom and top or to the sides depending in
         * which way the target resolution fits better.
         * @param aWidth Desired width resolution
         * @param aHeight Desired height resolution.
         */
         void SetTargetResolution(utils::Width aWidth, utils::Height aHeight);

    private:
        // Pointer to implementation.
        std::unique_ptr<CameraControllerImpl> mImpl;
    };
}


#endif //ZEPTOLABTEST_CAMERACONTROLLER_H
