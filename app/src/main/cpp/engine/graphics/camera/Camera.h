//
// Created by Josep on 15/08/2018.
//

#ifndef ZEPTOLABTEST_CAMERA_H
#define ZEPTOLABTEST_CAMERA_H

#include <memory>

#include "../glm/mat4x4.hpp"
#include "../../common/Utils.h"

namespace graphics
{
    class CameraImpl;
    class Camera
    {
    public:
        friend class CameraControllerImpl;

        enum PROJECTION_MODE
        {
            PM_ORTHO,
            PM_PERSPECTIVE
        };

        /**
         * Constructor
         */
        Camera();

        /**
         * Destructor.
         */
        ~Camera();

        /**
         * Copy constructor.
         * @param aOther
         */
        Camera(const Camera& aOther);

        /**
         * Move constructor.
         * @param aOther
         */
        Camera(Camera&& aOther);

        /**
         * Move assignment operator.
         * @param aOther
         * @return
         */
        Camera& operator=(Camera&& aOther);

        /**
         * Copy assignment operator.
         * @param aOther
         * @return
         */
        Camera& operator=(const Camera& aOther);

        /**
         * Sets the projection mode. Thera are two options: PM_ORTHO or
         * PM_PERSPECTIVE. The first one sets a Orthogonal projection,
         * and the second one a perspective projection.
         *
         */
        void SetProjectionMode(PROJECTION_MODE aMode);

        /**
         * Enable Z Depth test If enabled, the order to draw the objects
         * will depend on the Z axis position on each object. If disabled,
         * the order to draw the objects will depend on the own Draw calls,
         * making that the first objects drawn, will be farther that the
         * last ones.
         * @param aEnable Bool indicating if you want to enable Z depth.
         */
        void EnableZDepth(bool aEnable);

        /**
         * Sets Field of View in degrees, for a perspective projection.
         * @param aValue FOV in degrees.
         */
        void SetFOV(utils::Degrees aValue);

        /**
         * Sets Field of View in radians, for a perspective projection.
         * @param aValue
         */
        void SetFOV(utils::Radians aValue);

        /**
         * Sets near plane of the camera.
         * @param aValue Near Z plane.
         */
        void SetNear(float aValue);

        /**
         * Sets far plane of the camera
         * @param aValue Far Z plane.
         */
        void SetFar (float aValue);

        /**
         * Sets the current projection matrix. Every object in the scene will have to use
         * this matrix to be rendered in every frame.
         * @param aMatrix The projection matrix to be set.
         */
        static void SetProjectionMatrix(glm::mat4 aMatrix)
        {
            ProjectionMatrix = aMatrix;
        }

        /**
         * Returns the current projection matrix. Every object in the scene will have to use
         * this matrix to be rendered in every frame.
         * @return glm::mat4 matrix.
         */
        static glm::mat4 GetProjectionMatrix()
        {
            return ProjectionMatrix;
        }


    private:

        /**
         * Sets target resolution. This target resolution is set in camera controller but
         * camera need it to update the current projection matrix.
         * @param aTargetWidth Target resolution width.
         * @param aTargetHeight Target resolution height.
         */
        void SetTargetResolution(utils::Width aTargetWidth,
                                 utils::Height aTargetHeight);

        // Projection matrix.
        static glm::mat4 ProjectionMatrix;

        // Pointer to implementation.
        std::unique_ptr<CameraImpl> mImpl;

    };
}

#endif //ZEPTOLABTEST_CAMERA_H
