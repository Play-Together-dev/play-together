#ifndef PLAY_TOGETHER_GAME_H
#define PLAY_TOGETHER_GAME_H

#include <vector>
#include <SDL.h>
#include "Polygon.h"
#include "Player.h"
#include <climits>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
/**
 * @file Game.h
 * @brief Defines the Game class responsible for handling the main game logic.
 */

/**
 * @class Game
 * @brief Represents the main game logic including initialization, event handling, collision detection, and rendering.
 */
class Game {
public:
    Game(SDL_Window* window, SDL_Renderer* renderer, const Player& initialPlayer); /**< Constructor for the Game class. */

    /**
     * @brief Runs the game loop.
     */
    void run();

    /**
     * @brief Stops the game loop and cleans up resources.
     */
    void stop();

/**
 * @brief Loads obstacles from a map file.
 * @param mapName The name of the map file.
 */
void loadPolygonsFromMap(const std::string &mapName);

private:
    SDL_Window *window; /**< SDL window for rendering. */
    SDL_Renderer *renderer; /**< SDL renderer for rendering graphics. */
    std::vector<Polygon> obstacles; /**< Collection of polygons representing obstacles. */
    Player player; /**< The player object. */
    bool isRunning = true; /**< Flag indicating if the game is running. */

    /**
     * @brief Handles SDL events, updating the movement variables accordingly.
     * @param moveX Reference to the X-axis movement variable.
     * @param moveY Reference to the Y-axis movement variable.
     */
    void handleEvents(int &moveX, int &moveY);

    /**
     * @brief Applies player movement based on the current movement variables.
     * @param moveX The movement along the X-axis.
     * @param direction The direction along the X-axis.
     * @param timeSpeed The time that has elapsed since the player started running.
     * @param moveY The movement along the Y-axis.
     */
    void applyPlayerMovement(int &moveX, int direction, float  &timeSpeed, int &moveY);

    /**
     * @brief Handles collisions between the player and obstacles.
     * @param direction The direction along the X-axis.
     * @param moveY The movement along the Y-axis.
     */
    void handleCollisions(int direction, int moveY);

    /**
     * @brief Renders the game by drawing the player and obstacles.
     */
    void render();

    /**
     * @brief Checks for collision between the player and a polygon obstacle.
     * @param playerVertices The vector of Point representing the vertices of the player object.
     * @param obstacle The polygon obstacle.
     * @return True if a collision is detected, false otherwise.
     */
    static bool checkCollision(const std::vector<Point>& playerVertices, const Polygon &obstacle);

    /**
     * @brief Checks if a polygon is convex.
     * @param polygon The polygon to check.
     * @return True if the polygon is convex, false otherwise.
     */
    static bool isConvex(const Polygon &polygon);
};

#endif //PLAY_TOGETHER_GAME_H
