//
// Created by Josep on 26/08/2018.
//

#ifndef ZEPTOLABTEST_SCENETEST1_H
#define ZEPTOLABTEST_SCENETEST1_H

#include "../engine/scene/Scene.h"

/**
 * This scene shows several shapes performing different animations.
 */
class SceneTest1 : public scene::Scene
{

public:

    /**
     * Constructor
     * @param aDisplayWidth Width of the display
     * @param aDisplayHeight Height of the display.
     */
    SceneTest1(utils::Width aDisplayWidth, utils::Height aDisplayHeight);

    /**
     * Inits the scene. Must be implemented for all the concrete scenes.
     */
    void Init() override;

    /**
    * Update the scene. Must be implemented for all the concrete scenes.
    * @param aDt
    */
    void Update(double aDt) override;

private:

    /**
     * Creates a rectangle from specified build parameters.
     * @param aName Name of the node
     * @param aWidth Width of the rectangle
     * @param aHeight Height of the rectangle
     * @param aColor Color of the rectangle
     * @param aPosition Default position of the rectangle.
     * @returnf Pointer to the created rectangle.
     */
    scene::SceneNode* CreateRectangle(const std::string& aName,
                                       utils::Width aWidth,
                                       utils::Height aHeight,
                                       utils::Color aColor,
                                       utils::Vector3<float> aPosition);

    /**
     * Performs a Heart Beat animation to a specified node.
     * @param aNode Node to apply the animation
     * @param aDt Time in milliseconds since last frame.
     */
    void HeartBeat(scene::SceneNode& aNode, double aDt);

    /**
     * Performs a Ping Pong animation to a specified node.
     * @param aNode Node to apply the animation
     * @param aDt Time in milliseconds since last frame.
     */
    void PingPong(scene::SceneNode& aNode, double aDt);

    /**
     * Performs a Spin animation to a specified node.
     * @param aNode Node to apply the animation
     * @param aDt Time in milliseconds since last frame.
     */
    void Spin(scene::SceneNode& aNode, double aDt);

    // Pointer to red rectangle.
    scene::SceneNode* mRectangleRed;

    // Pointer to blue rectangle
    scene::SceneNode* mRectangleBlue;

    // Pointer to green rectangle.
    scene::SceneNode* mRectangleGreen;

    // Moving direction of the node with the Ping pong animation
    float mMovingDirection;

    // Scale direction of the node with the Heart beat animation.
    float mScaleDirection;
};


#endif //ZEPTOLABTEST_SCENETEST1_H
