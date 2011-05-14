#ifndef POINTLIGHT_H_INCLUDED
#define POINTLIGHT_H_INCLUDED

#include "Light.h"

namespace al
{
    class PointLight : public Light
    {
        public:
            PointLight(const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, int quality);
            ~PointLight();

        private:
            void generateVertices();

        private:
            int mQuality;
    };
}

#endif // POINTLIGHT_H_INCLUDED
