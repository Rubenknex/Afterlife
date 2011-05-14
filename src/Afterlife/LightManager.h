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
    class LightManager
    {
        typedef boost::shared_ptr<Light> LightPtr;

        public:
            LightManager();
            ~LightManager();

            void addLight(LightPtr light);
            void removeLight(LightPtr light);

            void draw(sf::RenderTarget& target);

            void setAmbientColor(const sf::Color& color);

        private:
            sf::Shader mBlurHorizontal;
            sf::Shader mBlurVertical;
            sf::RenderImage* mLightsImage;
            sf::RenderImage* mHorizontalPass;
            sf::RenderImage* mVerticalPass;
            sf::Sprite mLightsSprite;
            std::set<LightPtr> mLights;
            sf::Color mAmbientColor;
    };
}

#endif // LIGHTMANAGER_H_INCLUDED
