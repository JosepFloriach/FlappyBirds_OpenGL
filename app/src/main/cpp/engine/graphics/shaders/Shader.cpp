//
// Created by Josep on 15/08/2018.
//

#include "Shader.h"

#include <map>

namespace graphics
{
    class ShaderImpl
    {
    private:
        GLuint mProgramId;
        typedef std::map<std::string, GLuint> tUniformsMap;
        tUniformsMap mUniforms;

    public:
        ShaderImpl(GLuint aProgramId)
            : mProgramId(aProgramId)
        {
        }

        void AddUniform(std::string aName)
        {
            mUniforms[aName] = glGetUniformLocation(mProgramId, aName.c_str());
        }

        GLuint GetUniformId(std::string aName) const
        {
            assert(mUniforms.count(aName) > 0 && "There is no such uniform name.");
            return mUniforms.at(aName);
        }

        GLuint GetProgramId() const
        {
            return mProgramId;
        }

        void SetUniformFloat(std::string aName, float aValue)
        {
            auto UniformId = GetUniformId(aName);
            glUniform1f(UniformId, aValue);
        }

        void SetUniformMat4(std::string aName, glm::mat4 aValue)
        {
            auto UniformId = GetUniformId(aName);
            glUniformMatrix4fv(UniformId, 1, GL_FALSE, &aValue[0][0]);
        }
    };

    Shader::Shader(GLuint aProgramId)
        : mImpl(std::make_unique<ShaderImpl>(aProgramId))
    {
    }

    Shader::~Shader() = default;

    Shader::Shader(const Shader &aOther)
        : mImpl(std::make_unique<ShaderImpl>(*aOther.mImpl))
    {
    }

    Shader::Shader(Shader &&aOther)
        : mImpl(std::move(aOther.mImpl))
    {
    }

    Shader& Shader::operator=(const Shader &aOther)
    {
        mImpl = std::make_unique<ShaderImpl>(*aOther.mImpl);
        return *this;
    }

    Shader& Shader::operator=(Shader &&aOther)
    {
        mImpl = std::move(aOther.mImpl);
        return *this;
    }

    GLuint Shader::GetProgramId() const
    {
        return mImpl.get()->GetProgramId();
    }

    void Shader::AddUniform(std::string aName)
    {
        return mImpl.get()->AddUniform(aName);
    }

    void Shader::SetUniformMat4(std::string aName, glm::mat4 aValue)
    {
        mImpl.get()->SetUniformMat4(aName, aValue);
    }
    void Shader::SetUniformFloat(std::string aName, float aValue)
    {
        mImpl.get()->SetUniformFloat(aName, aValue);
    }
}