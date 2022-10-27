//
// Created by Josep on 11/08/2018.
//

#ifndef ZEPTOLABTEST_GAME_H
#define ZEPTOLABTEST_GAME_H

#include <string>
#include <memory>

#include "engine/common/Utils.h"
#include "engine/common/events/EventDispatcher.h"
#include "engine/common/events/EventPool.h"
#include "engine/scene/Scene.h"
#include "engine/common/Timer.h"

class Game
{
public:
    /**
     * Constructor
     * @param aSceneName Name of the scene that will be loaded.
     * @param aDisplayWidth Width of current display.
     * @param aDisplayHeight Height of current display.
     */
    Game(std::string aSceneName,
         utils::Width aDisplayWidth,
         utils::Height aDisplayHeight);

    /**
     * Destructor
     */
    ~Game();

    /**
     * Copy constructor.
     * @param aOther
     */
    Game(const Game& aOther) = delete;

    /**
     * Move constructor.
     * @param aOther
     */
    Game(Game&& aOther) = delete;

    /**
     * Copy assignment operator.
     * @param aOther
     * @return
     */
    Game& operator=(const Game& aOther) = delete;

    /**
     * Move assignment operator.
     * @param aOther
     * @return
     */
    Game& operator=(Game&& aOther) = delete;

    /**
     * Loads a specified name.
     * @param aName Name of the scene.
     */
    void LoadScene(std::string aName);

    /**
     * Called on init game.
     */
    void InitScene();

    /**
     * Called on every game tick.
     */
    void DrawScene();

    /**
     * Called when user touch the screen.
     */
    void OnTouch(float aX, float aY);

private:
    // Size of display.
    utils::Width mWidth;
    utils::Height mHeight;

    // Timer
    utils::Timer mTimer;

    // Scene.
    std::unique_ptr<scene::Scene> mScene;


};

#endif //ZEPTOLABTEST_GAME_H
