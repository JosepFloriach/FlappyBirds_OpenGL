//
// Created by Josep on 13/08/2018.
//

#ifndef ZEPTOLABTEST_SCENETEST2_H
#define ZEPTOLABTEST_SCENETEST2_H

#include <GLES2/gl2.h>
#include <string>
#include <memory>

#include "../engine/scene/Scene.h"

/**
 * This scene shows a rectangle with a rigid body that will jump on user tap/touch.
 */
class SceneTest2 : public scene::Scene
{
public:

    /**
     * Constructor
     * @param aDisplayWidth Width of the display
     * @param aDisplayHeight Height of the display.
     */
    SceneTest2(utils::Width aDisplayWidth, utils::Height aDisplayHeight);

    /**
     * Inits the scene. Must be impleneted for all the concrete scenes.
     */
    void Init() override;

    /**
    * Update the scene. Must be implemented for all the concrete scenes.
    * @param aDt
    */
    void Update(double aDt) override;

    /**
     * Called when the user taps the screen.
     * @param aX Position X where has touched.
     * @param aY Position Y where has touched.
     */
    void OnTouch(float aX, float aY) override;

private:

    /**
     * Creates the background scene.
     */
    void CreateBackground();

    /**
     * Creates the rectangle with the physics body.
     */
    void CreateRectangle();

    /**
     * Makes jump the physics body.
     */
    void Jump();

    // Pointer to physics body node.
    scene::SceneNode* mBody;
};


#endif //ZEPTOLABTEST_SCENETEST2_H
