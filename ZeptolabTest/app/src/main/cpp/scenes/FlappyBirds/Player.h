//
// Created by Josep on 03/09/2018.
//

#ifndef ZEPTOLABTEST_PLAYER_H
#define ZEPTOLABTEST_PLAYER_H

#include "../../engine/scene/SceneNode.h"

class Player : public scene::SceneNode
{
public:

    // Player jump force.
    static float JUMP_FORCE;

    /**
     * Constructor
     */
    explicit Player(const std::string aPlayerName);

    /**
     * Makes the player jump
     */
    void Jump();

    /**
     * Return if the player is awake. This is basically if the player touched for the first time and
     * the "Bird" is affected by gravity force.
     * @return Bool specifying if the player is awake.
     */
    bool IsAwake() const;

    /**
     * Returns if the player has dead.
     * @return Bool specifying if the player is Dead.
     */
    bool IsDead() const;

    /**
     * Awakes the player.
     */
    void Awake();

    /**
     * Kills the player.
     */
    void Kill();

private:
    // Is the player awake?
    bool mIsAwake;
    // Is the player dead?
    bool mIsDead;

};


#endif //ZEPTOLABTEST_PLAYER_H
