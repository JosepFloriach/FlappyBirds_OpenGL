//
// Created by Josep on 15/08/2018.
//

#ifndef ZEPTOLABTEST_SHADER_H
#define ZEPTOLABTEST_SHADER_H

#include <string>
#include <GLES2/gl2.h>

#include "../glm/mat4x4.hpp"

/**
 * This class represents a shader.
 */
namespace graphics
{
    class ShaderImpl;
    class Shader final
    {
    public:

        /**
         * Shader constructor.
         * @param aProgramId Identifier of this shader.
         */
        explicit Shader(GLuint aProgramId);

        /**
         * Destructor
         */
        ~Shader();

        /**
         * Copy constructor.
         * @param aOther
         */
        Shader(const Shader& aOther);

        /**
         * Move constructor.
         * @param aOther
         */
        Shader(Shader&& aOther);

        /**
         * Move assignment operator.
         * @param aOther
         * @return
         */
        Shader& operator=(Shader&& aOther);

        /**
         * Copy assignment operator.
         * @param aOther
         * @return
         */
        Shader& operator=(const Shader& aOther);

        /**
         * Gets the identifier of shader so it can be used by OpenGL function
         * glUseProgram.
         * @return GLuint identifying this shader.
         */
        GLuint GetProgramId() const;

        /**
         * Loads a uniform into the Shader, so it value
         * can be set later.
         * @param aName Name identifying the uniform.
         */
        void AddUniform(std::string aName);

        /**
         * Sets the value of a uniform of type mat4. The uniform must
         * be loaded previously by AddUniform method.
         * @param aName Name of the uniform (must be loaded already).
         * @param aValue value of type mat4.
         */
        void SetUniformMat4(std::string aName, glm::mat4 aValue);

        /**
         * Sets the value of a uniform of type float. The uniform must
         * be loaded previously by AddUniform method.
         * @param aName Name of the uniform (must be loaded already).
         * @param aValue value of type float.
         */
        void SetUniformFloat(std::string aName, float aValue);

    private:
        // Pointer to implementation.
        std::unique_ptr<ShaderImpl> mImpl;
    };
}

#endif //ZEPTOLABTEST_SHADER_H
