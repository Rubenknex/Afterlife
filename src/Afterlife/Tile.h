#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace al
{
    class Tile
    {
        public:
            Tile();
            Tile(int index, bool walkable);
            ~Tile();

            int getIndex();
            void setIndex(int index);
            bool getWalkable();
            void setWalkable(bool walkable);

        private:
            int mIndex;
            bool mWalkable;
    };
}

#endif // TILE_H_INCLUDED
