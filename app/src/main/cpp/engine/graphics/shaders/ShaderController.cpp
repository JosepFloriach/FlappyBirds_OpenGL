
// Created by Josep on 11/08/2018.
//

#include "ShaderController.h"
#include "Shader.h"
#include "ShadersSource.h"

#include <vector>
#include <map>
#include <android/log.h>

namespace graphics
{
    class ShaderControllerImpl
    {
    private:
        typedef std::map<std::string, std::unique_ptr<Shader>> tShadersMap;
        tShadersMap mShaders;

    public:
        /**
         * Constructor (default).
         */
        ShaderControllerImpl() = default;

        /**
         * Load all default shaders.
         */
        void Init()
        {
            Load("Default", ShadersSource::DefaultVert, ShadersSource::DefaultFrag);
            GetShader("Default")->AddUniform("MVP");
            GetShader("Default")->AddUniform("r");
            GetShader("Default")->AddUniform("g");
            GetShader("Default")->AddUniform("b");
        }

        /**
         * Loads a shader to be used later.
         * @param aName String identifying shader, so it can be found when the user wants to use it.
         * @param aSourceVertex Full source code of Vertex shader.
         * @param aSourceFragment Full source code of Fragment shader.
         */
        void Load(const std::string& aName,
                  const std::string& aSourceVertex,
                  const std::string& aSourceFragment)
        {
            // These Ids will be filled by reference.
            GLuint VertexId = 0;
            GLuint FragmentId = 0;
            GLuint ProgramId = 0;

            // Compile vertex and fragment shaders.
            auto VertexCompiled = Compile(aSourceVertex, GL_VERTEX_SHADER, VertexId);
            auto FragmentCompiled = Compile(aSourceFragment, GL_FRAGMENT_SHADER, FragmentId);
            // Link vertex and fragment.
            auto ShaderLinked = Link(VertexId, FragmentId, ProgramId);
            // Logs results.
            LogShaderLoad(VertexCompiled, FragmentCompiled, ShaderLinked);

            // If everything went fine, adds the ProgramId to the map.
            if (VertexCompiled && FragmentCompiled && ShaderLinked)
            {
                auto NewShader = std::make_unique<Shader>(ProgramId);
                mShaders[aName] = std::move(NewShader);
            }
        }

        /**
         * Compiles the source of a shader.
         * @param aSourceShader Source.
         * @param aShaderType Shader type. It should be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
         * @param aShaderId This will be filled with shader id.
         * @return true if everything went fine. False otherwise.
         */
        bool Compile(const std::string& aSourceShader,
                     GLenum aShaderType,
                     GLuint& aShaderId)
        {
            auto SourceArray = aSourceShader.c_str();
            GLint result = GL_FALSE;
            aShaderId = glCreateShader(aShaderType);

            glShaderSource(aShaderId, 1, &SourceArray, NULL);
            glCompileShader(aShaderId);

            // TODO: in case the compilation fails, we should return the specific error.
            glGetShaderiv(aShaderId, GL_COMPILE_STATUS, &result);

            return result != 0;
        }

        /**
         * Link vertex and fragment shaders together.
         * @param aVertexId Identifier of vertex shader.
         * @param aFragmentId Identifier of fragment shader.
         * @param aProgramId This will be filled with ProgramId.
         * @return true if everything went fine. False otherwise.
         */
        bool Link(GLuint aVertexId,
                  GLuint aFragmentId,
                  GLuint& aProgramId)
        {
            GLint result = GL_FALSE;

            aProgramId = glCreateProgram();

            glAttachShader(aProgramId, aVertexId);
            glAttachShader(aProgramId, aFragmentId);
            glLinkProgram(aProgramId);

            glGetProgramiv(aProgramId, GL_LINK_STATUS, &result);

            if (aVertexId)
                glDeleteShader(aVertexId);
            if (aFragmentId)
                glDeleteShader(aFragmentId);

            // TODO: in case linking fails, we should return the specific error.
            if (result == 0)
            {
                if (aProgramId) {
                    glDeleteProgram(aProgramId);
                }
            }
            return result != 0;
        }

        /**
         * Log the results of the shader load.
         * @param aVertexCompiled Specifies if vertex shader was  compiled successfuly.
         * @param aFragmentCompiled Specifies if fragment shader was  compiled successfuly.
         * @param aProgramLinked Specifies if both shaders was linked successfuly.
         */
        void LogShaderLoad(bool aVertexCompiled,
                           bool aFragmentCompiled,
                           bool aProgramLinked )
        {
            // TODO: this logging is only valid for android. This should be more generic.
            if (!aVertexCompiled)
            {
                __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SHADER",
                                    "Error compiling vertex shader!");
            }
            else if (!aFragmentCompiled)
            {
                __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SHADER",
                                    "Error compiling fragment shader!");
            }
            else
            {
                __android_log_print(ANDROID_LOG_DEBUG,"ZEPTOLAB_TEST_SHADER",
                                    "Shader compiled successfuly!!");
            }

            if (!aProgramLinked)
            {
                __android_log_print(ANDROID_LOG_ERROR,"ZEPTOLAB_TEST_SHADER",
                                    "Error linking shaders!");
            }
            else{
                __android_log_print(ANDROID_LOG_DEBUG,"ZEPTOLAB_TEST_SHADER",
                                    "Shaders linked successfuly!!");
            }
        }

        /**
         * Given a shader name, returns a pointer to the shader object associated.
         * @param aName Name of shader.
         * @return Pointer to the object associated with this shader.
         */
        Shader* GetShader(const std::string& aName) const
        {
            assert(mShaders.count(aName) > 0 && "This shader does not exist!");
            return mShaders.at(aName).get();
        }

    };

    ShaderController::ShaderController()
        : mImpl(std::make_unique<ShaderControllerImpl>())
    {
    }

    ShaderController::~ShaderController() = default;

    void ShaderController::Init()
    {
        mImpl->Init();
    }

    void ShaderController::Load(const std::string& aName,
                          const std::string& aSourceVertex,
                          const std::string& aSourceFragment)
    {
        mImpl->Load(aName, aSourceVertex, aSourceFragment);
    }

    Shader* ShaderController::GetShader(const std::string& aName) const
    {
        return mImpl->GetShader(aName);
    }
}
