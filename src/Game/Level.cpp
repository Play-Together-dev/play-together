#include "../../include/Game/Level.h"

/**
 * @file Level.cpp
 * @brief Implements the Level class responsible for level object.
 */

/** CONSTRUCTOR **/

Level::Level(const std::string &map_name) {
    loadPolygonsFromMap(map_name,obstacles,POLYGONS_FILE);
    loadPolygonsFromMap(map_name,dangerObstacles,DANGER_FILE);
    loadPolygonsFromMap(map_name,specialBoxes,BOXES_FILE);
}


/** ACCESSORS **/

std::vector<Polygon> Level::getObstacles() const{
    return obstacles;
}
std::vector<Polygon> Level::getDangerObstacles() const {
    return dangerObstacles;
}
std::vector<Polygon> Level::getSpecialBoxes() const {
    return specialBoxes;
}


/** METHODS **/

void Level::loadPolygonsFromMap(const std::string &mapName,std::vector<Polygon> &obs, const char *filename) {
    obs.clear();

    // Define the file path for the polygon data
    std::string filePath = std::string(MAPS_DIRECTORY) + mapName + "/" + filename;//POLYGONS_FILE;

    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string line;

        // Read each line from the file
        while (std::getline(file, line)) {
            std::vector<Point> vertices;
            std::istringstream iss(line);
            char dummy;

            // Extract points from each line
            while (iss >> dummy >> std::ws && dummy == '(') {
                int x;
                int y;
                iss >> x >> dummy >> y >> dummy;
                vertices.emplace_back(x, y);
                iss >> dummy;
            }
            // Add the completed polygon to the obstacles vector
            obs.emplace_back(vertices);
        }

        file.close();
        std::cout << "Loaded " << obs.size() << " polygons from the map " << mapName << "." << std::endl;
    } else {
        std::cerr << "Unable to open the file." << std::endl;
    }
}