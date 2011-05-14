#ifndef DIRECTIONALLIGHT_H_INCLUDED
#define DIRECTIONALLIGHT_H_INCLUDED

#include "Light.h"

namespace al
{
    class DirectionalLight : public Light
    {
        public:
            DirectionalLight(const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, float angle, float openAngle);
            ~DirectionalLight();

            void setAngle(float angle);

        private:
            void generateVertices();

        private:
            float mAngle;
            float mOpenAngle;
    };
}

#endif // DIRECTIONALLIGHT_H_INCLUDED
