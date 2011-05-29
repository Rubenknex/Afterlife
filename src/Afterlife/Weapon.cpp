#include "Weapon.h"

#include "../TinyXML/tinyxml.h"

#include "World.h"

namespace al
{
    /// WeaponData
    void WeaponData::load(const std::string& filename)
    {
        TiXmlDocument doc;

        if (doc.LoadFile(filename))
        {
            TiXmlHandle handle(&doc);
            handle = handle.FirstChildElement();

            TiXmlElement* name = handle.FirstChild("Name").ToElement();
            m_Name = name->FirstChild()->ValueStr();

            TiXmlElement* damage = handle.FirstChild("Damage").ToElement();
            m_Damage = boost::lexical_cast<int>(damage->FirstChild()->ValueStr());

            TiXmlElement* rpm = handle.FirstChild("RPM").ToElement();
            m_FireRate = boost::lexical_cast<int>(rpm->FirstChild()->ValueStr());

            TiXmlElement* magCapacity = handle.FirstChild("MagCapacity").ToElement();
            m_MagCapacity = boost::lexical_cast<int>(magCapacity->FirstChild()->ValueStr());

            TiXmlElement* reloadDelay = handle.FirstChild("ReloadDelay").ToElement();
            m_ReloadDelay = boost::lexical_cast<float>(reloadDelay->FirstChild()->ValueStr());

            TiXmlElement* image = handle.FirstChild("Image").ToElement();
            m_ImageFile = image->FirstChild()->ValueStr();

            TiXmlElement* fireSound = handle.FirstChild("FireSound").ToElement();
            m_FireFile = fireSound->FirstChild()->ValueStr();

            TiXmlElement* reloadSound = handle.FirstChild("ReloadSound").ToElement();
            m_ReloadFile = reloadSound->FirstChild()->ValueStr();
        }
        else
        {
            std::cout << "Failed to load weapon: " << filename << " (file doesn't exist/invalid XML)" << std::endl;
        }
    }

    /// Weapon
    Weapon::Weapon(const WeaponData& data) :
        m_Data(data),
        m_Owner(NULL)
    {
        m_Image = sf::Sprite(*IM.GetResource(data.m_ImageFile));
        m_Image.SetOrigin(m_Image.GetSize() / 2.0f);

        mBulletsInMag = m_Data.m_MagCapacity;
        mBullets = 10000;
    }

    Weapon::~Weapon()
    {

    }

    void Weapon::update(float dt)
    {
            if (mReloading)
            {
                if (mReloadTimer <= m_Data.m_ReloadDelay)
                    mReloadTimer += dt;
                else
                {
                    float bulletsToAdd = m_Data.m_MagCapacity - mBulletsInMag;

                    if (mBullets > bulletsToAdd)
                    {
                        mBulletsInMag = m_Data.m_MagCapacity;
                        mBullets -= bulletsToAdd;
                    }
                    else
                    {
                        mBulletsInMag = mBullets;
                        mBullets = 0;
                    }

                    mReloading = false;
                    mReloadTimer = 0.0f;
                }
            }
            else
            {
                if (mShootTimer <= (60.0f / m_Data.m_FireRate))
                    mShootTimer += dt;
            }
    }

    void Weapon::draw(sf::RenderTarget& target)
    {
            float rotRadians = math::radians(m_Owner->GetRotation() + 90.0f);
            sf::Vector2f rotNormal(cos(rotRadians), sin(rotRadians));
            m_Image.SetPosition(m_Owner->GetPosition() + rotNormal * 14.0f);
            m_Image.SetRotation(m_Owner->GetRotation());

            //m_FireLight->setPosition(m_Owner->GetPosition() + rotNormal * 14.0f);

            target.Draw(m_Image);
    }

    void Weapon::fire(EntityManager& em, const sf::Vector2f pos, float angle, float speed)
    {
            if (mShootTimer > (60.0f / m_Data.m_FireRate))
            {
                if (mBulletsInMag > 0)
                {
                    float rotRadians = math::radians(angle);
                    sf::Vector2f offset(cos(rotRadians), sin(rotRadians));
                    em.add(EntityFactory::createProjectile(m_Owner->getWorld(), pos + offset * 20.0f, angle, speed, m_Data.m_Damage));

                    g_AudioPlayer.playSound(m_Data.m_FireFile, 100.0f, math::rand(0.9f, 1.0f));

                    mBulletsInMag -= 1;
                    mShootTimer = 0.0f;
                }
                else
                {
                    //reload();
                }
            }
    }

    void Weapon::reload()
    {
            if (!mReloading && mBulletsInMag < m_Data.m_MagCapacity && mBullets > 0)
            {
                g_AudioPlayer.playSound(m_Data.m_ReloadFile, 100.0f, 1.0f);

                mReloading = true;
            }
    }

    void Weapon::setOwner(Entity* e)
    {
        m_Owner = e;
    }

    int Weapon::getBullets()
    {
        return mBullets;
    }

    void Weapon::setBullets(int bullets)
    {
        mBullets = bullets;
    }

    int Weapon::getMagCapacity()
    {
        return m_Data.m_MagCapacity;
    }

    int Weapon::getBulletsInMag()
    {
        return mBulletsInMag;
    }
}
