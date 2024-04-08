#ifndef PLAY_TOGETHER_POLYGON_H
#define PLAY_TOGETHER_POLYGON_H

#include <vector>
#include <cmath>
#include "../Game/Point.h"

/**
 * @file Polygon.h
 * @brief Defines the Polygon class responsible for handling polygons in 2D space.
 */

enum class ZoneType {
    COLLISION,
    ICE,
    SAND,
    DEATH,
    CINEMATIC,
    BOSS,
    EVENT,
    SAVE
};

/**
 * @class Polygon
 * @brief Represents a polygon in 2D space.
 */
class Polygon {
public:
    /** CONSTRUCTOR **/

    Polygon(const std::vector<Point> &vertices, ZoneType type);


/** ACCESSORS **/

    /**
     * @brief Get the vertices of the polygon.
     * @return The vertices of the polygon.
     */
    [[nodiscard]] std::vector<Point> getVertices() const;

    /**
     * @brief Get the type of the zone.
     * @return The type of the zone.
     */
    [[nodiscard]] ZoneType getType() const;


    /** PUBLIC METHODS **/

    /**
     * @brief Checks if a polygon is convex.
     * @param polygon The polygon to check.
     * @return True if the polygon is convex, false otherwise.
     */
    [[nodiscard]] bool isConvex() const;

private:
    /** ATTRIBUTES **/

    std::vector<Point> vertices; /**< The vertices of the polygon. */
    ZoneType type; /**< The type of the zone. */


    /** PRIVATE METHODS **/

    /**
     * @brief Calculate the distance between two points.
     * @param a The first point.
     * @param b The second point.
     * @return The distance between points a and b.
     */
    static double distance(const Point &a, const Point &b);

    /**
     * @brief Calculate the angle between three points.
     * @param a The first point.
     * @param b The second point.
     * @param c The third point.
     * @return The angle in radians between the three points.
     */
    static double calculateAngle(const Point &a, const Point &b, const Point &c);

    /**
     * @brief Calculate the sum of interior angles of the polygon.
     * @return The sum of interior angles in degrees.
     */
    [[nodiscard]] double totalAngles() const;
};

#endif //PLAY_TOGETHER_POLYGON_H