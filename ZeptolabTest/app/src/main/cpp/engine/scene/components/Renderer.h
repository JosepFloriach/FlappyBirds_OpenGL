//
// Created by Josep on 22/08/2018.
//

#ifndef ZEPTOLABTEST_RENDERER_H
#define ZEPTOLABTEST_RENDERER_H

#include "../../graphics/glm/mat4x4.hpp"
#include "Component.h"

/**
 * Abstract class. Must be implemented for each concrete Renderer.
 * Renderer is an abstraction of a component that allows us to render forms and visual graphics onto
 * the screen. These graphics can be a texture, a geometric shape, a 3D model...
 */
namespace graphics{class Shader;}
namespace scene
{
    class SceneNode;
    class Renderer : public Component
    {
    public:

        /**
         * Destructor.
         */
        virtual ~Renderer();

        /**
        * Default constructor
        */
        Renderer();

        /**
         * Other constructors and operators. Deleted since this is an abstract class.
         */
        Renderer(Renderer&& aOther) = delete;
        Renderer(const Renderer& aOther) = delete;
        Renderer& operator=(const Renderer& aOther) = delete;
        Renderer& operator=(Renderer&& aOther) = delete;

        /**
         * This method must be implemented for each concrete Renderer.
         */
        virtual void Draw() = 0;

        /**
         * Update transform. Since each Renderer can have its own way to do that, each Renderer
         * must be implement this method.
         */
        virtual void UpdateTransform() = 0;

        /**
         * Use this method to update shader uniforms. By default, this method won't do anything. Each
         * renderer can re-implement this method if it needs.
         */
        virtual void UpdateShader() {};

        /**
         * Sets the shader to be used by the renderer.
         * @param aShader Pointer to the shader to be used.
         */
        void SetShader(graphics::Shader *aShader);

        /**
         * Updates the renderer. Basically udpates the transform, the shader variables and draw.
         * @param aDt Time in milliseconds since last frame.
         */
        virtual void Update(double aDt) override;

        /**
         * Return the matrix model according the current transform parameters.
         * @return glm::mat4
         */
        glm::mat4 GetMatrixModel() const;

        /**
         * Returns the matrix view according the current transform parameters.
         * @return glm::mat4
         */
        glm::mat4 GetMatrixView() const;

    protected:

        // Pointer to the current shader.
        graphics::Shader *mShader;
    };
}

#endif //ZEPTOLABTEST_RENDERER_H
