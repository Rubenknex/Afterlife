#include "Tile.h"

namespace al
{
    Tile::Tile() :
        mIndex(0),
        mWalkable(false)
    {

    }

    Tile::Tile(int index, bool walkable) :
        mIndex(index),
        mWalkable(walkable)
    {

    }

    Tile::~Tile()
    {

    }

    int Tile::getIndex()
    {
        return mIndex;
    }

    void Tile::setIndex(int index)
    {
        mIndex = index;
    }

    bool Tile::getWalkable()
    {
        return mWalkable;
    }

    void Tile::setWalkable(bool walkable)
    {
        mWalkable = walkable;
    }
}
