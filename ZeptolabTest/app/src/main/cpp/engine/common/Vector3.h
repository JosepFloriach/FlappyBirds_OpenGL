//
// Created by Josep on 24/08/2018.
//

#ifndef ZEPTOLABTEST_VECTOR3_H
#define ZEPTOLABTEST_VECTOR3_H

#include <cmath>

/**
 * This class represents a vector3 in the space.
 */
namespace utils
{
    template<typename T = float>
    class Vector3
    {
    public:
        Vector3()
                : X(0.f)
                , Y(0.f)
                , Z(0.f)
        {
        }

        Vector3(T aX, T aY, T aZ)
                : X(aX)
                , Y(aY)
                , Z(aZ)
        {
        }

        Vector3(const Vector3& aOther) = default;
        Vector3(Vector3&& aOther) = default;
        Vector3& operator=(const Vector3& aOther) = default;
        Vector3& operator=(Vector3&& aOther) = default;

        Vector3& operator -=(const Vector3& aOther)
        {
            X -= aOther.X;
            Y -= aOther.Y;
            Z -= aOther.Z;
        }

        Vector3& operator +=(const Vector3& aOther)
        {
            X += aOther.X;
            Y += aOther.Y;
            Z += aOther.Z;
            return *this;
        }

        Vector3 operator *=(const T& aValue)
        {
            X *= aValue;
            Y *= aValue;
            Z *= aValue;
            return *this;
        }

        Vector3 operator /=(const T& aValue)
        {
            X /= aValue;
            Y /= aValue;
            Z /= aValue;
        }

        Vector3 operator- (const Vector3& aOther)
        {
            return Vector3(X - aOther.X, Y - aOther.Y, Z - aOther.Z);
        }

        Vector3 operator+ (const Vector3& aOther)
        {
            return Vector3(X + aOther.X, Y + aOther.Y, Z + aOther.Z);
        }

        Vector3 operator* (const T& aValue)
        {
            return Vector3(X * aValue, Y * aValue, Z * aValue);
        }

        Vector3 operator/ (const T& aValue)
        {
            return Vector3(X / aValue, Y / aValue, Z / aValue);
        }

        // todo: implement the rest of vector operations

        Vector3 Normalize()
        {
            float length = sqrt(pow(X,2.f) + pow(Y,2.f) + pow(Z,2.f));
            return *this/length;
        }

        T X;
        T Y;
        T Z;
    };
}


#endif //ZEPTOLABTEST_VECTOR3_H
