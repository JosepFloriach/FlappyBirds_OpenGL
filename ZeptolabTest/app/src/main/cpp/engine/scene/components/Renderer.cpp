//
// Created by Josep on 22/08/2018.
//

#include "Renderer.h"
#include "../../graphics/glm/mat4x4.hpp"
#include "../../graphics/glm/gtc/matrix_transform.hpp"
#include "../../graphics/shaders/Shader.h"


namespace scene
{
    Renderer::~Renderer() = default;
    Renderer::Renderer() = default;

    void Renderer::Update(double aDt)
    {
        UpdateTransform();
        UpdateShader();
        Draw();
    }

    void Renderer::SetShader(graphics::Shader* aShader)
    {
        mShader = aShader;
    }

    glm::mat4 Renderer::GetMatrixView() const
    {
        // Scale. We will not allow any scalation in world axis.
        auto ViewMatrix = glm::scale(glm::mat4(1.0f),
                                     glm::vec3(1.0f,
                                               1.0f,
                                               1.0f));
        // Rotation
        ViewMatrix = glm::rotate(ViewMatrix,
                                 glm::radians(mRotation.value),
                                 glm::vec3(mRotationAxis.X,
                                           mRotationAxis.Y,
                                           mRotationAxis.Z));
        // Translate
        ViewMatrix = glm::translate(ViewMatrix,
                                    glm::vec3(mPosition.X,
                                              mPosition.Y,
                                              mPosition.Z));
        return ViewMatrix;
    }

    glm::mat4 Renderer::GetMatrixModel() const
    {
        // Scale
        auto ModelMatrix = glm::scale(glm::mat4(1.0f),
                                      glm::vec3(mLocalScale.X,
                                                mLocalScale.Y,
                                                mLocalScale.Z));
        // Rotation
        ModelMatrix = glm::rotate(ModelMatrix,
                                  glm::radians(mLocalRotation.value),
                                  glm::vec3(mLocalRotationAxis.X,
                                            mLocalRotationAxis.Y,
                                            mLocalRotationAxis.Z));
        // Translate
        ModelMatrix =  glm::translate(ModelMatrix,
                                      glm::vec3(mLocalPosition.X,
                                                mLocalPosition.Y,
                                                mLocalPosition.Z));
        return ModelMatrix;
    }
}