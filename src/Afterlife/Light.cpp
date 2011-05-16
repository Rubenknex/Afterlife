#include "Light.h"

namespace al
{
    Light::Light(const std::string& name, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color) :
        m_Name(name),
        mOn(true),
        mPosition(pos),
        mIntensity(intensity),
        mRadius(radius),
        mColor(color)
    {

    }

    Light::~Light()
    {

    }

    void Light::draw(sf::RenderTarget* target)
    {
        if (mOn)
        {
            for (int i = 0; i < mTriangles.size(); i++)
            {
                target->Draw(mTriangles[i]);
            }
        }
    }

    std::string Light::getName()
    {
        return m_Name;
    }

    void Light::setPosition(const sf::Vector2f& pos)
    {
        mPosition = pos;

        for (int i = 0; i < mTriangles.size(); i++)
        {
            mTriangles[i].SetPosition(pos);
        }
    }

    void Light::setIntensity(float intensity)
    {
        mIntensity = intensity;

        for (int i = 0; i < mTriangles.size(); i++)
        {
            mTriangles[i].SetPointColor(0, sf::Color((int)(mIntensity * mColor.r), (int)(mIntensity * mColor.g), (int)(mIntensity * mColor.b)));
        }
    }

    float Light::getIntensity()
    {
        return mIntensity;
    }

    void Light::setRadius(float radius)
    {
        mRadius = radius;

        generateVertices();
    }

    void Light::setOn(bool on)
    {
        mOn = on;
    }

    void Light::addTriangle(const sf::Vector2f v1, const sf::Vector2f v2)
    {
        sf::Shape triangle;

        triangle.AddPoint(0.0f, 0.0f, sf::Color((int)(mIntensity * mColor.r), (int)(mIntensity * mColor.g), (int)(mIntensity * mColor.b)), sf::Color(255, 255, 255));

        triangle.AddPoint(v1, sf::Color(0, 0, 0), sf::Color(255, 255, 255));
        triangle.AddPoint(v2, sf::Color(0, 0, 0), sf::Color(255, 255, 255));

        triangle.SetBlendMode(sf::Blend::Add);
        triangle.SetPosition(mPosition);

        mTriangles.push_back(triangle);
    }
}
