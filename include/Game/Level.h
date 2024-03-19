#ifndef PLAY_TOGETHER_LEVEL_H
#define PLAY_TOGETHER_LEVEL_H

#include <SDL.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Polygon.h"

// Define constants for directories and file names
constexpr char MAPS_DIRECTORY[] = "../assets/maps/";
constexpr char POLYGONS_FILE[] = "polygons.txt";
constexpr char DANGER_FILE[] = "dangerPolygons.txt";
constexpr char BOXES_FILE[] = "boxes.txt";

/**
 * @file Level.h
 * @brief Defines the Level class responsible for level object.
 */

/**
 * @class Level
 * @brief Represents the level object including obstacles.
 */
class Level {
public:
    /** CONSTRUCTOR **/

    Level(const std::string &map_name);


    /** ACCESSORS **/

    /**
     * @brief Return the obstacles attribute.
     * @return A vector of Polygon.
     */
    [[nodiscard]] std::vector<Polygon> getObstacles() const;
    /**
    * @brief Return the dangerObstacles attribute.
    * @return A vector of Polygon.
    */
    [[nodiscard]] std::vector<Polygon> getDangerObstacles() const;
    /**
    * @brief Return the specialBoxes attribute.
    * @return A vector of Polygon.
    */
    [[nodiscard]] std::vector<Polygon> getSpecialBoxes() const;



private:
    /** ATTRIBUTES **/

    std::vector<Polygon> obstacles; /**< Collection of polygons representing obstacles. */

    std::vector<Polygon> dangerObstacles;/**< Collection of polygons representing obstacles that will be the danger. */

    std::vector<Polygon> specialBoxes;/**< Collection of polygons representing special Boxes with power. */
    /** PRIVATE METHODS **/

    /**
     * @brief Loads obstacles from a map file.
     * @param mapName The name of the map file.
     * @param obstacles The type of obstacles that we want to load
     * @param filename The name of the obstacles file
     */
    void loadPolygonsFromMap(const std::string &mapName,std::vector<Polygon> &obstacles, const char *filename);


};

#endif //PLAY_TOGETHER_LEVEL_H
