//
// Created by Josep on 04/09/2018.
//

#ifndef ZEPTOLABTEST_SCENARY_H
#define ZEPTOLABTEST_SCENARY_H


#include "../../engine/scene/SceneNode.h"


namespace scene { class Scene; }
class Scenary
{
public:

    // Scenary move speed.
    static float MOVE_SPEED;
    // Max time can pass before a new pipe is respawned.
    static float PIPE_SPAWN_MAX_FREQ;
    // Min time can pass before a new pipe is respawned.
    static float PIPE_SPAWN_MIN_FREQ;
    // Max distance in the gap between the two parts of the pipe.
    static float PIPE_GAP_MAX_DISTANCE;
    // Min distance in the gap between the two parts of the pipe.
    static float PIPE_GAP_MIN_DISTANCE;
    // Width of the pipe
    static float PIPE_WIDTH;
    // Max Y distance in which the next pipe will be respawned relative to the previous pipe.
    static float NEXT_PIPE_Y_OFFSET;

    /**
     * Constructore
     * @param aScene Pointer to the scene we are handle.
     */
    explicit Scenary(scene::Scene* aScene);

    /**
     * Update the scenary. Basically this method will create a new pipe (if corresponds) and delete
     * the old ones if they are not useful anymore (because they went out of the screen).
     * @param aDt Time in milliseconds since last frame.
     */
    void Update(double aDt);

private:

    /**
     * Handles the spawn of a new pipe.
     * @param aDt Time in milliseconds since last frame.
     */
    void PipeGeneration(double aDt);

    /**
     * Spawns a new pipe.
     */
    void SpawnPipe();

    /**
     * Reset variables to respawn the next pipe.
     */
    void ResetTimeForNextPipe();

    // Pointer to the current scene.
    scene::Scene* mScene;

    // Seconds passed since the last time we spawned a pipe.
    float mSecondsSinceLastPipe;
    // Seconds until the next pipe.
    float mSecondsUntilNextPipe;
    // Y position of the respawned last pipe.
    float mYPositionGapLastPipe;
    // Count of spawned pipes.
    unsigned mPipesCount;

    std::vector<scene::SceneNode*> mPipes;





};


#endif //ZEPTOLABTEST_SCENARY_H
