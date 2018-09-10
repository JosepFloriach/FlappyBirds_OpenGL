//
// Created by Josep on 21/08/2018.
//

#ifndef ZEPTOLABTEST_TRANSFORM_H
#define ZEPTOLABTEST_TRANSFORM_H

#include "../common/Utils.h"
#include "../common/Vector3.h"

/**
 * This class allow an object to have a transform. A transform means a place in the world. A class
 * with transform means that it can move, rotate, scale...Is a CRTP class and adds Transform
 * functionalities to the template type.
 * @tparam T Type of the class that will get these funcionalities.
 */
template <typename T>
class Transform
{

public:
    Transform()
        : mPosition(utils::Vector3<float>(0.0f, 0.0f, 0.0f))
        , mLocalPosition(utils::Vector3<float>(0.0f, 0.0f, 0.0f))
        , mRelativePosition(utils::Vector3<float>(0.f, 0.f,0.f))
        , mLocalScale(utils::Vector3<float>(1.f, 1.f, 1.f))
        , mRelativeScale(utils::Vector3<float>(0.f, 0.f, 0.f))
        , mRotation(utils::Degrees(0.f))
        , mRotationAxis(utils::Vector3<float>(0.f, 0.f, 1.f))
        , mLocalRotation(utils::Degrees(0.f))
        , mLocalRotationAxis(utils::Vector3<float>(0.f, 0.f, 1.f))
        , mRelativeRotation(utils::Degrees(0.f))
        , mRelativeRotationAxis(utils::Vector3<float>(0.0f, 0.0f, 0.0f))
    {
    }

    /**
     * Returns absolute position.
     * @return Vector3
     */
    utils::Vector3<float> GetPosition() const
    {
        return mPosition;
    }

    /**
     * Returns local scale (there are no absolute scales).
     * @return Vector3.
     */
    utils::Vector3<float> GetScale() const
    {
        return mLocalScale;
    }

    /**
     * Returns local rotation axis.
     * @return Vector3.
     */
    utils::Vector3<float> GetLocalRotationAxis() const
    {
        return mLocalRotationAxis;
    }

    /**
     * Returns local rotation (in degrees).
     * @return Utils::Degrees.
     */
    utils::Degrees GetLocalRotation() const
    {
        return mLocalRotation;
    }

    /**
     * Returns absolute rotation axis.
     * @return Vector3.
     */
    utils::Vector3<float> GetRotationAxis() const
    {
        return mRotationAxis;
    }

    /**
     * Returns absolute rotation (in degrees).
     * @return Utils::Degrees.
     */
    utils::Degrees GetRotation() const
    {
        return mRotation;
    }

protected:

    utils::Vector3<float> mLocalRotationAxis;
    utils::Vector3<float> mRotationAxis;
    utils::Vector3<float> mRelativeRotationAxis;

    utils::Vector3<float> mLocalPosition;
    utils::Vector3<float> mLocalScale;
    utils::Degrees mLocalRotation;

    utils::Vector3<float> mRelativePosition;
    utils::Vector3<float> mRelativeScale;
    utils::Degrees mRelativeRotation;

    utils::Vector3<float> mPosition;
    utils::Degrees mRotation;
};

#endif //ZEPTOLABTEST_TRANSFORM_H
