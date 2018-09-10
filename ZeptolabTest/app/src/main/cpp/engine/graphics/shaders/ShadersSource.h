//
// Created by Josep on 13/08/2018.
//

#ifndef ZEPTOLABTEST_SHADERS_H
#define ZEPTOLABTEST_SHADERS_H

#include <string>

/**
 * This class stores shader implementations. The optimal way to load these shaders would be to load
 * them from files and not directly from code. But there is a lack of documentation about loading
 * files in Android from NDK, and I hadn't so much time to explore about it...
 */
class ShadersSource
{
public:
    static const std::string DefaultFrag;
    static const std::string DefaultVert;

};

#endif //ZEPTOLABTEST_SHADERS_H
