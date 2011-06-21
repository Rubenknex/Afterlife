#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
 
#include <SFML/Graphics.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "TinyXML/tinyxml.h"
 
#include "Collision.h"
#include "Functions.h"
#include "Scene/Light.h"
#include "Parsing.h"
#include "ResourceManager.h"
#include "Scripting/Script.h"
#include "Tile.h"
 
class World;
 
// Holds all the tile and collision data for a level.
class Level
{
public:
    enum TileSide
    {
        NONE,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
    };
 
public:
    Level(World* world);
    ~Level();
 
    // Load a level from an XML file.
    void load(const std::string& filename);
    // Save this level to an XML file.
    void save(const std::string& filename);
 
    // Wether a tile at this position is walkable.
    bool isWalkable(int x, int y);
 
    // Converts a tile source rectangle to it's index.
    int rectToIndex(const sf::IntRect& rect);
    // Converts an index to a source rectangle of the tile.
    sf::IntRect indexToRect(int index);
 
    void update(float dt);
    void draw(sf::RenderTarget& target);
 
    // Returns the side of the tile on which the position is, currently used for determining
    // in which direction grenades bounces when they collide with a wall.
    TileSide getTileSide(const sf::Vector2f pos);
 
    // Cast a ray from one point to another and return wether it crossed any non walkable tiles.
    bool rayCast(const sf::Vector2f& start, const sf::Vector2f& end);
 
    // Return the width of the level in pixels.
    int getWidthPixels();
    // Return the height of the level in pixels.
    int getHeightPixels();
 
    // Return the bounds of the level in pixels.
    sf::FloatRect getLevelRect();
    // Returns a bounding rectangle of a tile.
    sf::FloatRect getTileRect(int x, int y);
 
private:
    World* m_world;

    std::vector<std::vector<Tile> > mTiles;
    std::string mTilesetFilename;
    sf::Sprite mTileset;
 
    Script* m_UpdateScript;
 
    int mWidth;
    int mHeight;
    int mTileWidth;
    int mTileHeight;
};
 
#endif // LEVEL_H_INCLUDED
 
