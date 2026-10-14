#ifndef __APP_CORE_PLAYERCAR__HPP__
#define __APP_CORE_PLAYERCAR__HPP__

#include "App/Core/Entity.hpp"

namespace App::Core {
class PlayerCar : public Entity {
  public:
    PlayerCar();
    virtual ~PlayerCar();

    /**
     * @brief Resets the player's parameters to their initial values.
     */
    void reset();

    /**
     * @brief Sets the player's score.
     * @param score The new score to set.
     */
    void setScore(int score);

    /**
     * @brief Retrieves the player's current score.
     * @return The current score of the player.
     */
    int getScore();

    /**
     * @brief Retrieves the number of lives the player has.
     * @return The number of lives.
     */
    int getNumOfLives();

    /**
     * @brief Decrements the player's lives by one.
     */
    void decrementLive();

    /**
     * @brief Retrieves the number of rockets the player has.
     * @return The number of rockets.
     */
    int getNumOfRockets();

    /**
     * @brief Decrements the player's rockets by one.
     */
    void decrementRocket();

    virtual int  getWidth()  = 0;
    virtual int  getHeight() = 0;
    virtual void visualize() = 0;

    int score;
    int lives;
    int rockets;
};
} // namespace App::Core

#endif