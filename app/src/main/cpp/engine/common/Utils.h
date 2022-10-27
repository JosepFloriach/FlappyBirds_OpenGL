//
// Created by Josep on 14/08/2018.
//

#ifndef ZEPTOLABTEST_UTILS_H
#define ZEPTOLABTEST_UTILS_H

#include <string>
#include <algorithm>
#include "Vector3.h"

namespace utils
{
	static const double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270;

	struct Width
	{
		explicit Width(float aValue)
			: value(aValue)
		{
		}
		float value;
	};

	struct Height
	{
		explicit Height(float aValue)
			: value(aValue)
		{
		}
		float value;
	};

	struct Radius
	{
		explicit Radius(float aValue)
			: value(aValue)
		{
		}
		float value;
	};

	struct Color
	{
		Color (float aR, float aG, float aB)
				: R(aR)
				, G(aG)
				, B(aB)
		{
		}
		float R;
		float G;
		float B;
	};

	// Strong type.
	struct Radians
	{
		explicit Radians(float aValue)
			: value(aValue)
		{
		}
		float value;
	};

	// Strong type.
	struct Degrees
	{
		explicit Degrees(float aValue)
			: value(aValue)
		{
		}

		Degrees& operator +=(const Degrees& aOther)
		{
			value += aOther.value;
			return *this;
		}

		Degrees& operator+ (const Degrees& aOther)
		{
			value += aOther.value;
			return *this;
		}

		//todo: implement the rest of operators.

		float value;
	};

	static float Clamp(float aValue, float aLower, float aUpper)
	{
		return std::min(aUpper, std::max(aValue, aLower));
	}

	template <typename T>
	static T GetRandom(T aMin, T aMax)
	{
		return aMin + static_cast<T> (std::rand()) / (static_cast<T>(RAND_MAX/(aMax - aMin)));
	}
}

#endif //ZEPTOLABTEST_UTILS_H