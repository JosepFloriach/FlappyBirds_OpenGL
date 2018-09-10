//
// Created by Josep on 08/09/2018.
//

#ifndef ZEPTOLABTEST_SCENETEST4_H
#define ZEPTOLABTEST_SCENETEST4_H

#include "../engine/scene/Scene.h"

/**
 * This scene shows a circle behind a rectangle to show the rendering order when z-buffer is
 * deactivated.
 */
class SceneTest4 : public scene::Scene
{
public:
    /**
     * Constructor
     * @param aDisplayWidth Width of the display
     * @param aDisplayHeight Height of the display.
     */
    SceneTest4(utils::Width aDisplayWidth, utils::Height aDisplayHeight);

    /**
     * Inits the scene. Must be impleneted for all the concrete scenes.
     */
    void Init() override;

    /**
    * Update the scene. Must be implemented for all the concrete scenes.
    * @param aDt
    */
    void Update(double aDt) override;
private:

    /**
     * Creates the background scene.
     */
    void CreateNodeBackground();

    /**
     * Cretaes the rectangle node.
     */
    void CreateNodeRectangle();

    /**
     * Creates the circle node.
     */
    void CreateNodeCircle();
};


#endif //ZEPTOLABTEST_SCENETEST4_H
