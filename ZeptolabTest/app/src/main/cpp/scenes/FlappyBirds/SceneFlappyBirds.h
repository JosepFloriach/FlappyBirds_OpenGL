//
// Created by Josep on 13/08/2018.
//

#ifndef ZEPTOLABTEST_SCENEFLAPPYBIRDS_H
#define ZEPTOLABTEST_SCENEFLAPPYBIRDS_H

#include <GLES2/gl2.h>
#include <string>
#include <memory>

#include "Player.h"
#include "Scenary.h"

#include "../../engine/scene/Scene.h"
#include "../../engine/common/events/EventPool.h"

/**
 * This scene shows the Flappy Birds game.
 */
class SceneFlappyBirds : public scene::Scene
{
public:
    // Target resolution width of the game. This value is basically the aspect ratio in which the
    // game will be played. If the display cannot fit this aspect ratio, the engine will apply
    // pillarboxes to fit the display to the target aspect ratio.
    static const float TARGET_RESOLUTION_WIDTH;

    // Target resolution height of the game.
    static const float TARGET_RESOLUTION_HEIGHT;

    /**
     * Constructor
     * @param aDisplayWidth Width of the display
     * @param aDisplayHeight Height of the display.
     */
    SceneFlappyBirds(utils::Width aDisplayWidth, utils::Height aDisplayHeight);

    /**
     * Inits the scene. Must be implemented for all the concrete scenes.
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

    /**
     * Called when a node enter into a collision with another one.
     * @param aEvent Event with the data that has triggered the collision.
     */
    void OnCollision(const events::Event& aEvent);

private:

    /**
     * Creates the game background.
     */
    void CreateBackground();

    /**
     * Creates the player node. The player will be a circle with a physics body, renderer and a
     * collider.
     */
    void CreatePlayer();

    /**
     * Creates the roof node. The roof will be a rectangle with a collider.
     */
    void CreateRoof();

    /**
     * Creates the floor node. The floor will be a rectangle with a collider.
     */
    void CreateFloor();

    // Scenary object. It will handle all scenary/map building.
    Scenary mScenary;

     // Player object. It will handle if the player is alive, awake, etc.
    Player mPlayer;
};


#endif //ZEPTOLABTEST_SCENEFLAPPYBIRDS_H
