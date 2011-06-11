#include "SpotLight.h"

namespace al
{
    SpotLight::SpotLight(const std::string& name, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, float angle, float openAngle) :
        Light(name, pos, intensity, radius, color),
        mAngle(angle),
        mOpenAngle(openAngle)
    {
        generateVertices();
    }

    SpotLight::~SpotLight()
    {

    }

    void SpotLight::setAngle(float angle)
    {
        mAngle = angle;

        mTriangles[0].SetRotation(angle);
    }

    void SpotLight::generateVertices()
    {
        mTriangles.clear();

        float angleRad = mAngle * M_PI / 180.0;
        float openAngleRad = mOpenAngle * M_PI / 180.0;

        addTriangle(sf::Vector2f(mRadius * cos(angleRad - openAngleRad), mRadius * sin(angleRad - openAngleRad)),
                    sf::Vector2f(mRadius * cos(angleRad + openAngleRad), mRadius * sin(angleRad + openAngleRad)));
    }
}
