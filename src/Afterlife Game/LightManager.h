#ifndef LIGHTMANAGER_H_INCLUDED
#define LIGHTMANAGER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <set>
#include <iostream>

#include "Functions.h"
#include "Light.h"

namespace al
{
    typedef boost::shared_ptr<Light> LightPtr;

    class LightManager
    {
        public:
            LightManager();
            ~LightManager();

            void addLight(LightPtr);
            void removeLight(const std::string& name);

            void draw(sf::RenderTarget& target);

            LightPtr getLightByName(const std::string& name);

            void setAmbientColor(const sf::Color& color);

        private:
            sf::Shader mBlurHorizontal;
            sf::Shader mBlurVertical;
            sf::RenderImage* mLightsImage;
            sf::RenderImage* mHorizontalPass;
            sf::RenderImage* mVerticalPass;
            sf::Sprite mLightsSprite;
            std::map<std::string, LightPtr> m_Lights;
            sf::Color mAmbientColor;
    };
}

#endif // LIGHTMANAGER_H_INCLUDED
