//
// Created by Josep on 08/09/2018.
//

#ifndef ZEPTOLABTEST_SCENETEST5_H
#define ZEPTOLABTEST_SCENETEST5_H

#include "../engine/scene/Scene.h"

/**
 * This scene shows a circle and a rectangle. The circle is parented to the rectangle, so when we
 * move the rectangle, the circle is moved with it.
 */
class SceneTest5 : public scene::Scene
{
public:
    /**
     * Constructor
     * @param aDisplayWidth Width of the display
     * @param aDisplayHeight Height of the display.
     */
    SceneTest5(utils::Width aDisplayWidth, utils::Height aDisplayHeight);

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
     * Creates the scene rectangle.
     * @return Reference to the node just created.
     */
    scene::SceneNode& CreateRectangle();

    /**
     * Creates the circle child of the rectangle.
     * @param aParent Node that will be set as parent.
     */
    void CreateCircleChild(scene::SceneNode& aParent);

    // Rectangle node pointer.
    scene::SceneNode* mRectangle;

};


#endif //ZEPTOLABTEST_SCENETEST4_H
