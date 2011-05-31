#include "ParticleSystem.h"

namespace al
{
    ParticleSystem::ParticleSystem(const std::string& name) :
        mName(name)
    {
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            mParticles[i].alive = false;
        }
    }

    ParticleSystem::~ParticleSystem()
    {

    }

    void ParticleSystem::load(const std::string& filename)
    {
        TiXmlDocument doc;

        if (doc.LoadFile(filename))
        {
            TiXmlHandle handle(&doc);
            handle = handle.FirstChild("ParticleSystem");

            TiXmlElement* texture = handle.FirstChild("Texture").ToElement();
            mTexture.SetImage(*IM.GetResource(texture->FirstChild()->ValueStr()));
            mTexture.SetOrigin(mTexture.GetSize() / 2.0f);

            TiXmlElement* color = handle.FirstChild("Color").ToElement();
            int r = boost::lexical_cast<int>(color->Attribute("R"));
            int g = boost::lexical_cast<int>(color->Attribute("G"));
            int b = boost::lexical_cast<int>(color->Attribute("B"));
            mColor = sf::Color(r, g, b);

            TiXmlElement* drawOrder = handle.FirstChild("DrawOrder").ToElement();
            mDrawOrder = boost::lexical_cast<int>(drawOrder->FirstChild()->ValueStr());

            TiXmlElement* minSpeed = handle.FirstChild("MinSpeed").ToElement();
            mMinSpeed = boost::lexical_cast<float>(minSpeed->FirstChild()->ValueStr());
            TiXmlElement* maxSpeed = handle.FirstChild("MaxSpeed").ToElement();
            mMaxSpeed = boost::lexical_cast<float>(maxSpeed->FirstChild()->ValueStr());

            TiXmlElement* minAngle = handle.FirstChild("MinAngle").ToElement();
            mMinAngle = boost::lexical_cast<float>(minAngle->FirstChild()->ValueStr());
            TiXmlElement* maxAngle = handle.FirstChild("MaxAngle").ToElement();
            mMaxAngle = boost::lexical_cast<float>(maxAngle->FirstChild()->ValueStr());

            TiXmlElement* minScale = handle.FirstChild("MinScale").ToElement();
            mMinScale = boost::lexical_cast<float>(minScale->FirstChild()->ValueStr());
            TiXmlElement* maxScale = handle.FirstChild("MaxScale").ToElement();
            mMaxScale = boost::lexical_cast<float>(maxScale->FirstChild()->ValueStr());

            TiXmlElement* minRotation = handle.FirstChild("MinRotation").ToElement();
            mMinRotation = boost::lexical_cast<float>(minRotation->FirstChild()->ValueStr());
            TiXmlElement* maxRotation = handle.FirstChild("MaxRotation").ToElement();
            mMaxRotation = boost::lexical_cast<float>(maxRotation->FirstChild()->ValueStr());

            TiXmlElement* minLifespan = handle.FirstChild("MinLifespan").ToElement();
            mMinLifespan = boost::lexical_cast<float>(minLifespan->FirstChild()->ValueStr());
            TiXmlElement* maxLifespan = handle.FirstChild("MaxLifespan").ToElement();
            mMaxLifespan = boost::lexical_cast<float>(maxLifespan->FirstChild()->ValueStr());

            TiXmlElement* minParticles = handle.FirstChild("MinParticles").ToElement();
            mMinParticles = boost::lexical_cast<int>(minParticles->FirstChild()->ValueStr());
            TiXmlElement* maxParticles = handle.FirstChild("MaxParticles").ToElement();
            mMaxParticles = boost::lexical_cast<int>(maxParticles->FirstChild()->ValueStr());
        }
        else
        {
            std::cout << "Failed to load ParticleSystem: " << filename << std::endl;
        }
    }

    void ParticleSystem::fire(sf::Vector2f pos)
    {
        int numParticles = sf::Randomizer::Random(mMinParticles, mMaxParticles);
        int particleCounter = 0;

        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (!mParticles[i].alive)
            {
                mParticles[i].pos = pos;
                float angle = sf::Randomizer::Random(mMinAngle, mMaxAngle);
                float speed = sf::Randomizer::Random(mMinSpeed, mMaxSpeed);
                mParticles[i].vel = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
                mParticles[i].rotation = sf::Randomizer::Random(mMinRotation, mMaxRotation);
                mParticles[i].scale = sf::Randomizer::Random(mMinScale, mMaxScale);
                mParticles[i].timeAlive = 0.0f;
                mParticles[i].lifespan = sf::Randomizer::Random(mMinLifespan, mMaxLifespan);
                mParticles[i].alive = true;

                particleCounter++;
            }

            if (particleCounter >= numParticles)
                break;
        }
    }

    void ParticleSystem::update(float dt)
    {
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (mParticles[i].alive)
            {
                mParticles[i].pos += mParticles[i].vel * dt;
                mParticles[i].timeAlive += dt;

                if (mParticles[i].timeAlive > mParticles[i].lifespan)
                {
                    mParticles[i].alive = false;
                }
            }
        }
    }

    void ParticleSystem::draw(sf::RenderTarget& target)
    {
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (mParticles[i].alive)
            {
                mTexture.SetPosition(mParticles[i].pos);
                mTexture.SetScale(mParticles[i].scale, mParticles[i].scale);
                mTexture.SetRotation(mParticles[i].rotation);

                int alpha = 255 - ((mParticles[i].timeAlive / mParticles[i].lifespan) * 255);
                mTexture.SetColor(sf::Color(mColor.r, mColor.g, mColor.b, alpha));

                target.Draw(mTexture);
            }
        }
    }

    const std::string& ParticleSystem::getName()
    {
        return mName;
    }

    bool ParticleSystem::operator<(const ParticleSystem& rhs) const
    {
        return mDrawOrder < rhs.mDrawOrder;
    }
}
