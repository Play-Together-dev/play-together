#ifndef PLAY_TOGETHER_CAMERA_H
#define PLAY_TOGETHER_CAMERA_H

#include <SDL.h>
#include <random>
#include "Point.h"

constexpr float SCREEN_WIDTH = 800;
constexpr float SCREEN_HEIGHT = 600;
constexpr float LERP_SMOOTHING_FACTOR = 0.05f;


/**
 * @file Camera.h
 * @brief Defines the Camera class responsible for handling the camera logic.
 */

/**
 * @class Level
 * @brief Represents the camera logic including movement and shaking.
 */

class Camera {
public:
    /** CONSTRUCTORS **/

    Camera();


    /** ACCESSORS **/

    /**
     * @brief Return the x attribute.
     * @return The value of the x attribute.
     */
    [[nodiscard]] float getX() const;

    /**
     * @brief Return the y attribute.
     * @return The value of the y attribute.
     */
    [[nodiscard]] float getY() const;

    /**
     * @brief Return the width attribute.
     * @return The value of the w attribute.
     */
    [[nodiscard]] float getW() const;

    /**
     * @brief Return the height attribute.
     * @return The value of the H attribute.
     */
    [[nodiscard]] float getH() const;

    /**
     * @brief Return the area attribute.
     * @return A rectangle representing the area.
     */
    [[nodiscard]] SDL_FRect getArea() const;


    /** MODIFIERS **/

    /**
    * @brief Set the x attribute.
    * @param val The new value of the x attribute.
    */
    void setX(float val);

    /**
    * @brief Set the x attribute.
    * @param val The new value of the x attribute.
    */
    void setY(float val);

    /**
     * @brief Set the isShaking attribute.
     * @param state The new state of the isShaking attribute.
     * @see toggleIsShaking for a similar operation.
     */
    void setIsShaking(bool state);

    /**
     * @brief Toggle the isShaking attribute.
     * @see setIsShaking for a similar operation.
     */
    void toggleIsShaking();


    /** PUBLIC METHODS **/

    /**
     * @brief Initialize the camera position according to players positions.
     * @param camera_point A point representing the camera point position.
     */
    void initializeCameraPosition(Point camera_point);

    /**
     * @brief Applies camera movement based on the positions of all players.
     * @param camera_point A point representing the camera point position.
     */
    void applyCameraMovement(Point camera_point);

    /**
     * @brief Renders the collisions by drawing obstacles.
     * @param renderer Represents the renderer of the game.
     * @param camera_point Represents the camera point.
     */
    void renderCameraPoint(SDL_Renderer *renderer, Point camera_point) const;

    /**
     * @brief Renders the collisions by drawing obstacles.
     * @param renderer Represents the renderer of the game.
     */
    void renderCameraArea(SDL_Renderer *renderer) const;


private:
    /** ATTRIBUTES **/

    float x = 0; /**< The x-coordinate of the camera's position */
    float y = 0; /**< The y-coordinate of the camera's position */
    float w = SCREEN_WIDTH; /**< The width of the camera */
    float h = SCREEN_HEIGHT; /**< The height of the camera */

    /**< Rectangle for camera "not moving area" */
    SDL_FRect area = {w / 5.f,
                      h / 5.f,
                      w - (w / 2.f) - w / 5.f,
                      h - (h / 5.f) - h / 5.f};

    bool isShaking = false; /**< Flag indicating if the camera is currently shaking */
    float shakeAmplitude = 2; /**< The amplitude of the camera shake */


    /** PRIVATE METHODS **/

    /**
     * @brief Applies a shake movement to the camera .
     */
    void makeCameraShake();

};


#endif //PLAY_TOGETHER_CAMERA_H
