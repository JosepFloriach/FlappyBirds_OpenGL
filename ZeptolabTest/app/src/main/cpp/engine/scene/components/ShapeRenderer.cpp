//
// Created by Josep on 22/08/2018.
//

#include "ShapeRenderer.h"
#include "../SceneNode.h"
#include "../../graphics/camera/Camera.h"
#include "../../graphics/shaders/Shader.h"

namespace scene
{
    ShapeRenderer::ShapeRenderer()
            : Renderer()
            , mColor(1.0f, 1.0f, 1.0f)
    {
    }

    ShapeRenderer::~ShapeRenderer() = default;

    ShapeRenderer::ShapeRenderer(const ShapeRenderer &aOther)
        : mShape(aOther.mShape->Clone())
        , mColor(aOther.mColor)
    {
    }

    ShapeRenderer::ShapeRenderer(ShapeRenderer &&aOther)
        : mShape (std::move(aOther.mShape))
        , mColor (aOther.mColor)
    {
    }

    ShapeRenderer& ShapeRenderer::operator=(const ShapeRenderer &aOther)
    {
        mShape = aOther.mShape->Clone();
        mColor = aOther.mColor;
        return *this;
    }

    ShapeRenderer& ShapeRenderer::operator=(ShapeRenderer &&aOther)
    {
        mShape = std::move(aOther.mShape);
        mColor = aOther.mColor;
        return *this;
    }

    void ShapeRenderer::UpdateTransform()
    {
        if (mShader)
        {
            auto ModelMatrix = GetMatrixModel();
            auto ViewMatrix = GetMatrixView();
            auto ProjectionMatrix = graphics::Camera::GetProjectionMatrix();
            auto MVPMatrix = ProjectionMatrix * ViewMatrix * ModelMatrix;

            glUseProgram(mShader->GetProgramId());
            mShader->SetUniformMat4("MVP", MVPMatrix);
            mShader->SetUniformFloat("r", mColor.R);
            mShader->SetUniformFloat("g", mColor.G);
            mShader->SetUniformFloat("b", mColor.B);
        }
    }

    void ShapeRenderer::SetColor(utils::Color aColor)
    {
        mColor = aColor;
    }

    void ShapeRenderer::Draw()
    {
        mShape->Draw();
    }
}
