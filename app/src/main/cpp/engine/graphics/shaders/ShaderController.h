//
// Created by Josep on 11/08/2018.
//

#ifndef ZEPTOLABTEST_SHADERCONTROLLER_H
#define ZEPTOLABTEST_SHADERCONTROLLER_H

#include <memory>
#include <string>

/**
 * This class handles the loading of shaders. It basically contains a vector of loaded shaders.
 */
namespace graphics
{
    class Shader;
    class ShaderControllerImpl;
    class ShaderController final
    {
    public:

        /**
         * Constructor.
         */
        ShaderController();

        /**
         * Destructor.
         */
        ~ShaderController();

        /**
         * Non-copyable, non-moveable class.
         */
        ShaderController(const ShaderController& aOther) = delete;
        ShaderController(ShaderController&& aOther) = delete;
        ShaderController& operator=(const ShaderController& aOther) = delete;
        ShaderController& operator=(ShaderController&& aOther) = delete;

        /**
         * Load all default shaders.
         */
        void Init();

        /**
         * Loads a shader to be used later.
         * @param aName String identifying shader, so it can be found when the user wants to use it.
         * @param aSourceVertex Full source code of Vertex shader.
         * @param aSourceFragment Full source code of Fragment shader.
         */
        void Load(const std::string& aName,
                  const std::string& aSourceVertex,
                  const std::string& aSourceFragment);

        /**
         * Gets a pointer to a specific loaded shader.
         * @param aName String identifying a specific shader.
         * @return Pointer to the shader.
         */
        Shader* GetShader(const std::string& aName) const;

    private:
        // Pointer to implementation.
        std::unique_ptr<ShaderControllerImpl> mImpl;
    };
}


#endif //ZEPTOLABTEST_SHADERCONTROLLER_H
