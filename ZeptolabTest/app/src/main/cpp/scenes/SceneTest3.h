//
// Created by Josep on 13/08/2018.
//

#ifndef ZEPTOLABTEST_SCENETEST3_H
#define ZEPTOLABTEST_SCENETEST3_H

#include <GLES2/gl2.h>
#include <string>
#include "../engine/common/events/EventPool.h"
#include "../engine/scene/Scene.h"

/**
 * This scene shows several shapes colliding between them.
 */
class SceneTest3 : public scene::Scene
{
public:

    /**
     * Constructor
     * @param aDisplayWidth Width of the display
     * @param aDisplayHeight Height of the display.
     */
    SceneTest3(utils::Width aDisplayWidth, utils::Height aDisplayHeight);

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
     * Creates the big non-moving rectangle.
     */
    void CreateNodeBigRectangle();

    /**
     * Creates the big non-moving circle.
     */
    void CreateNodeBigCircle();

    /**
     * Creates the rectangle that will collide with the big rectangle.
     */
    void CreateNodeRectangle1();

    /**
     * Creates the rectangle that will collide with the big circle.
     */
    void CreateNodeRectangle2();

    /**
     * Creates the circle that will move from top to bot.
     */
    void CreateNodeCircle();

    /**
     * Called when a node enter into a collision with another one.
     * @param aEvent Event with the data that has triggered the collision.
     */
    void OnEnterCollision(const events::Event& aEvent);

    /**
     * Called when a node exits from colliding with another one.
     * @param aEvent Event with the data that has triggered the collision exit.
     */
    void OnExitCollision(const events::Event& aEvent);

    // Moving Rectangle 1 pointer.
    scene::SceneNode* mMovingRectangle1;

    // Moving Rectangle 2 pointer.
    scene::SceneNode* mMovingRectangle2;

    // Moving Circle pointer.
    scene::SceneNode* mMovingCircle;
};


#endif //ZEPTOLABTEST_SCENETEST3_H
