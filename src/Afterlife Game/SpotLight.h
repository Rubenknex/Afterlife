#ifndef SPOTLIGHT_H_INCLUDED
#define SPOTLIGHT_H_INCLUDED

#include "Light.h"

namespace al
{
    class SpotLight : public Light
    {
        public:
            SpotLight(const std::string& name, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, float angle, float openAngle);
            ~SpotLight();

            void setAngle(float angle);

        private:
            void generateVertices();

        private:
            float mAngle;
            float mOpenAngle;
    };
}

#endif // SPOTLIGHT_H_INCLUDED
