#include "ParticleManager.h"

namespace al
{
    ParticleManager::ParticleManager()
    {

    }

    ParticleManager::~ParticleManager()
    {

    }

    void ParticleManager::loadSystem(const std::string& filename, const std::string& name)
    {
        ParticleSystem ps(name);
        ps.load(filename);

        mParticleSystems.push_back(ps);

        std::sort(mParticleSystems.begin(), mParticleSystems.end());
    }

    void ParticleManager::fireSystem(const std::string& name, sf::Vector2f pos)
    {
        for (int i = 0; i < mParticleSystems.size(); i++)
        {
            if (mParticleSystems[i].getName() == name)
            {
                mParticleSystems[i].fire(pos);

                break;
            }
        }
    }

    void ParticleManager::update(float dt)
    {
        for (int i = 0; i < mParticleSystems.size(); i++)
        {
            mParticleSystems[i].update(dt);
        }
    }

    void ParticleManager::draw(sf::RenderTarget& target)
    {
        for (int i = 0; i < mParticleSystems.size(); i++)
        {
            mParticleSystems[i].draw(target);
        }
    }
}
