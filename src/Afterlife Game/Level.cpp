#include "Level.h"

#include "../TinyXML/tinyxml.h"

namespace al
{
    Level::Level() :
        mTilesetFilename(std::string()),
        mTileset(sf::Image()),
        m_UpdateScript(NULL),
        mWidth(0),
        mHeight(0),
        mTileWidth(0),
        mTileHeight(0)
    {

    }

    Level::~Level()
    {
        if (m_UpdateScript != NULL)
            delete m_UpdateScript;
    }

    void Level::load(const std::string& filename)
    {
        TiXmlDocument doc;

        if (doc.LoadFile(filename))
        {
            TiXmlHandle handle(&doc);
            handle = handle.FirstChild("Level");

            TiXmlElement* tileset = handle.FirstChildElement("Tileset").ToElement();
            mTilesetFilename = tileset->FirstChild()->ValueStr();
            mTileset = sf::Sprite(*IM.GetResource(mTilesetFilename));

            TiXmlElement* script = handle.FirstChildElement("Script").ToElement();
            m_UpdateScript = new Script(&g_ScriptManager, "Level");
            m_UpdateScript->loadSection(script->FirstChild()->ValueStr());
            m_UpdateScript->build();

            m_UpdateScript->prepareFunction("initialize");
            m_UpdateScript->executeFunction();

            TiXmlElement* width = handle.FirstChildElement("Width").ToElement();
            mWidth = atoi(width->FirstChild()->Value());

            TiXmlElement* height = handle.FirstChildElement("Height").ToElement();
            mHeight = atoi(height->FirstChild()->Value());

            TiXmlElement* tileWidth = handle.FirstChildElement("TileWidth").ToElement();
            mTileWidth = atoi(tileWidth->FirstChild()->Value());

            TiXmlElement* tileHeight = handle.FirstChildElement("TileHeight").ToElement();
            mTileHeight = atoi(tileHeight->FirstChild()->Value());

            for (int x = 0; x < mWidth; x++)
            {
                mTiles.push_back(std::vector<Tile>());

                for (int y = 0; y < mHeight; y++)
                {
                    mTiles[x].push_back(Tile(0, false));
                }
            }

            TiXmlElement* tiles = handle.FirstChildElement("Tiles").ToElement();
            int yPos = 0;
            for (TiXmlElement* row = tiles->FirstChildElement(); row; row = row->NextSiblingElement())
            {
                std::vector<std::string> indices;
                boost::algorithm::split(indices, row->FirstChild()->ValueStr(), boost::is_any_of(" "));

                for (int i = 0; i < (int)indices.size(); i++)
                    mTiles[i][yPos].setIndex(atoi(indices[i].c_str()));

                yPos++;
            }

            TiXmlElement* collision = handle.FirstChildElement("Collision").ToElement();
            yPos = 0;
            for (TiXmlElement* row = collision->FirstChildElement(); row; row = row->NextSiblingElement())
            {
                std::vector<std::string> collData;
                boost::algorithm::split(collData, row->FirstChild()->ValueStr(), boost::algorithm::is_any_of(" "));

                for (int i = 0; i < (int)collData.size(); i++)
                {
                    mTiles[i][yPos].setWalkable(strcmp(collData[i].c_str(), "1") == 0 ? false : true);
                }

                yPos++;
            }
        }
    }

    void Level::save(const std::string& filename)
    {

    }

    bool Level::isWalkable(int x, int y)
    {
        int tX = x / mTileWidth;
        int tY = y / mTileHeight;

        if (tX >= 0 && tY >= 0 && tX < mWidth && tY < mHeight)
            return this->mTiles[tX][tY].getWalkable();

        return false;
    }

    int Level::rectToIndex(const sf::IntRect& rect)
    {
        int width = mTileset.GetImage()->GetWidth() / mTileWidth;
        int y = (rect.Top / mTileHeight) * width;
        int x = rect.Left / mTileWidth;

        return y + x;
    }

    sf::IntRect Level::indexToRect(int index)
    {
        int width = mTileset.GetImage()->GetWidth() / mTileWidth;
        int x = index % width;
        int y = index / width;

        return sf::IntRect(x * mTileWidth, y * mTileHeight, mTileWidth, mTileHeight);
    }

    void Level::update(float dt)
    {
        m_UpdateScript->prepareFunction("update");
        m_UpdateScript->setArgFloat(0, dt);
        m_UpdateScript->executeFunction();
    }

    void Level::draw(sf::RenderTarget& target)
    {
        // Find which tiles we need to draw, this saves drawing tiles that
        // are not visible anyway.
        //sf::FloatRect viewRect = window.GetViewport();
        sf::Vector2f center = target.GetDefaultView().GetCenter();
        sf::Vector2f size = target.GetDefaultView().GetSize();
        int startX = (center.x - size.x / 2.0f) / mTileWidth;
        int endX = (center.x + size.x / 2.0f)/ mTileWidth + 1;
        int startY = (center.y - size.y / 2.0f) / mTileHeight;
        int endY = (center.y + size.y / 2.0f) / mTileHeight + 1;

        //printRect<float>(viewRect);

        if (startX < 0)
            startX = 0;
        if (startY < 0)
            startY = 0;
        if (endX > mWidth)
            endX = mWidth;
        if (endY > mHeight)
            endY = mHeight;


        for (int x = 0; x < mWidth; x++)
        {
            for (int y = 0; y < mHeight; y++)
            {
                mTileset.SetPosition(x * mTileWidth, y * mTileHeight);
                mTileset.SetSubRect(indexToRect(mTiles[x][y].getIndex()));

                target.Draw(mTileset);
            }
        }


        /*
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);

        glPushMatrix();
        glTranslatef(-viewRect.Left, -viewRect.Top, 0.0f);
        glTranslatef(0.375f, 0.375f, 0.0f);

        mTileset.Bind();

        for (int x = startX; x < endX; x++)
        {
            for (int y = startY; y < endY; y++)
            {
                sf::IntRect subRect = indexToRect(mTiles[x][y].getIndex());
                sf::FloatRect texCoords((float)subRect.Left / mTileset.GetWidth(), (float)subRect.Top / mTileset.GetHeight(), (float)subRect.Right / mTileset.GetWidth(), (float)subRect.Bottom / mTileset.GetHeight());

                glBegin(GL_QUADS);
                    glTexCoord2f(texCoords.Left, texCoords.Top); glVertex2f(x * mTileWidth, y * mTileHeight);
                    glTexCoord2f(texCoords.Right, texCoords.Top); glVertex2f(x * mTileWidth + mTileWidth, y * mTileHeight);
                    glTexCoord2f(texCoords.Right, texCoords.Bottom); glVertex2f(x * mTileWidth + mTileWidth, y * mTileHeight + mTileHeight);
                    glTexCoord2f(texCoords.Left, texCoords.Bottom); glVertex2f(x * mTileWidth, y * mTileHeight + mTileHeight);
                glEnd();
            }
        }

        glPopMatrix();
        */
    }

    Level::TileSide Level::getTileSide(const sf::Vector2f pos)
    {
        sf::FloatRect tileRect = getTileRect(pos.x, pos.y);
        sf::Vector2f tileCenter(tileRect.Left + tileRect.Width / 2.0f, tileRect.Top + tileRect.Height / 2.0f);

        if (pointInTriangle(pos, sf::Vector2f(tileRect.Left, tileRect.Top), tileCenter, sf::Vector2f(tileRect.Left, tileRect.Top + tileRect.Height)))
        {
            return Level::LEFT;
        }
        else if (pointInTriangle(pos, sf::Vector2f(tileRect.Left, tileRect.Top), tileCenter, sf::Vector2f(tileRect.Left + tileRect.Width, tileRect.Top)))
        {
            return Level::TOP;
        }
        else if (pointInTriangle(pos, sf::Vector2f(tileRect.Left + tileRect.Width, tileRect.Top), tileCenter, sf::Vector2f(tileRect.Left + tileRect.Width, tileRect.Top + tileRect.Height)))
        {
            return Level::RIGHT;
        }
        else if (pointInTriangle(pos, sf::Vector2f(tileRect.Left, tileRect.Top + tileRect.Height), tileCenter, sf::Vector2f(tileRect.Left + tileRect.Width, tileRect.Top + tileRect.Height)))
        {
            return Level::BOTTOM;
        }

        return Level::NONE;
    }

    bool Level::rayCast(const sf::Vector2f& start, const sf::Vector2f& end)
    {
        int startX = start.x / mTileWidth;
        int startY = start.y / mTileHeight;
        int endX = end.x / mTileWidth;
        int endY = end.y / mTileHeight;
        std::vector<sf::Vector2i> points = bresenhamLine(startX, startY, endX, endY);

        bool collision = false;

        if (points.size() > 0)
        {
            int pointIndex = 0;

            if (points[0].x != startX || points[0].y != startY)
                pointIndex = points.size() - 1;

            while (true)
            {
                sf::Vector2i point = points[pointIndex];

                if (!isWalkable(point.x * mTileWidth, point.y * mTileHeight))
                {
                    collision = true;

                    break;
                }

                if (points[0].x != startX || points[0].y != startY)
                {
                    pointIndex--;

                    if (pointIndex < 0)
                        break;
                }
                else
                {
                    pointIndex++;

                    if (pointIndex >= points.size())
                        break;
                }
            }
        }

        return collision;
    }

    int Level::getWidthPixels()
    {
        return mWidth * mTileWidth;
    }

    int Level::getHeightPixels()
    {
        return mHeight * mTileHeight;
    }

    sf::FloatRect Level::getLevelRect()
    {
        return sf::FloatRect(0.0f, 0.0f, mWidth * mTileWidth, mHeight * mTileHeight);
    }

    sf::FloatRect Level::getTileRect(int x, int y)
    {
        int tx = (x / mTileWidth) * mTileWidth;
        int ty = (y / mTileHeight) * mTileHeight;

        return sf::FloatRect(tx, ty, mTileWidth, mTileHeight);
    }
}
