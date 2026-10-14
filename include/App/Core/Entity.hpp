#ifndef __APP_CORE_ENTITY__HPP__
#define __APP_CORE_ENTITY__HPP__

namespace App::Core {
class Entity {
  public:
    Entity();
    virtual ~Entity();

    /**
     * @brief Move the entity within the specified limits.
     * @param limitUp Upper limit for the y-coordinate.
     * @param limitRight Right limit for the x-coordinate.
     * @param limitDown Lower limit for the y-coordinate.
     * @param limitLeft Left limit for the x-coordinate.
     */
    void move(int limitUp, int limitRight, int limitDown, int limitLeft);

    /**
     * @brief Move the entity without any limits.
     */
    void move();

    /**
     * @brief Set the entity's position to the center of the screen.
     * @param screen_width Width of the screen.
     * @param screen_height Height of the screen.
     * @param width Width of the entity's texture.
     * @param height Height of the entity's texture.
     */
    void setCenter(int screen_width, int screen_height, int width, int height);

    /**
     * @brief Set the entity's position for score printing.
     * @param screen_width Width of the screen.
     * @param screen_height Height of the screen.
     * @param width Width of the score texture.
     * @param height Height of the score texture.
     */
    void setScorePosition(int screen_width, int width);

    virtual void visualize() = 0;

    int x;
    int y;
    int velX;
    int velY;
};
} // namespace App::Core

#endif
