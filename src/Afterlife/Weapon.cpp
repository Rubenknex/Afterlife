#include "Weapon.h"

#include "../TinyXML/tinyxml.h"

#include "World.h"

namespace al
{
    Weapon::Weapon(Entity* owner) :
        mOwner(owner),
        m_Loaded(false)
    {

    }

    Weapon::Weapon(const std::string& name, int capacity, int firerate, float damage, float reloadTime)
    {
        mName = name;

        mMagCapacity = capacity;

        mShootTimer = 0.0f;
        m_Firerate = firerate;
        mShootDelay = 1.0f / (firerate / 60.0f);

        mBullets = 1000;
        mBulletsInMag = capacity;

        mReloading = false;
        mReloadTimer = 0.0f;
        mReloadDelay = reloadTime;

        mDamage = damage;

        m_Loaded = true;
    }

    Weapon::~Weapon()
    {

    }

    void Weapon::load(const std::string& filename)
    {
        TiXmlDocument doc;

        if (doc.LoadFile(filename))
        {
            TiXmlHandle handle(&doc);
            handle = handle.FirstChildElement();

            TiXmlElement* name = handle.FirstChild("Name").ToElement();
            mName = name->FirstChild()->ValueStr();

            TiXmlElement* damage = handle.FirstChild("Damage").ToElement();
            mDamage = boost::lexical_cast<int>(damage->FirstChild()->ValueStr());

            TiXmlElement* rpm = handle.FirstChild("RPM").ToElement();
            m_Firerate = boost::lexical_cast<int>(rpm->FirstChild()->ValueStr());
            mShootDelay = 1.0f / (m_Firerate / 60.0f);

            TiXmlElement* magCapacity = handle.FirstChild("MagCapacity").ToElement();
            mMagCapacity = boost::lexical_cast<int>(magCapacity->FirstChild()->ValueStr());

            TiXmlElement* reloadDelay = handle.FirstChild("ReloadDelay").ToElement();
            mReloadDelay = boost::lexical_cast<float>(reloadDelay->FirstChild()->ValueStr());

            TiXmlElement* image = handle.FirstChild("Image").ToElement();
            //mImage = sf::Sprite(*IM.GetResource(image->FirstChild()->ValueStr()));
            shared_ptr<sf::Image> img = IM.GetResource("data/Images/Weapons/ak47.png");
            mImage = sf::Sprite(*img);
            mImage.SetOrigin(mImage.GetSize() / 2.0f);

            TiXmlElement* fireSound = handle.FirstChild("FireSound").ToElement();
            mFireSound = sf::Sound(*SM.GetResource(fireSound->FirstChild()->ValueStr()));

            TiXmlElement* reloadSound = handle.FirstChild("ReloadSound").ToElement();
            mReloadSound = sf::Sound(*SM.GetResource(reloadSound->FirstChild()->ValueStr()));

            mBullets = 1000;
            mBulletsInMag = mMagCapacity;
            mShootTimer = 0.0f;
            mReloadTimer = 0.0f;
            mReloading = false;

            m_FireLight = boost::shared_ptr<PointLight>(new PointLight(sf::Vector2f(), 1.0f, 32.0f, sf::Color(255, 230, 150), 16));
            m_FireLight->setOn(false);
            mOwner->getWorld()->getLightManager()->addLight(m_FireLight);

            m_Loaded = true;
        }
        else
        {
            std::cout << "Failed to load weapon: " << filename << " (file doesn't exist/invalid XML)" << std::endl;
        }
    }

    void Weapon::update(float dt)
    {
        if (m_Loaded)
        {
            if (mReloading)
            {
                if (mReloadTimer <= mReloadDelay)
                    mReloadTimer += dt;
                else
                {
                    float bulletsToAdd = mMagCapacity - mBulletsInMag;

                    if (mBullets > bulletsToAdd)
                    {
                        mBulletsInMag = mMagCapacity;
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
                if (mShootTimer <= mShootDelay)
                    mShootTimer += dt;
            }
        }
    }

    void Weapon::draw(sf::RenderTarget& target)
    {
        if (m_Loaded)
        {
            float rotRadians = radians(mOwner->GetRotation() + 90.0f);
            sf::Vector2f rotNormal(cos(rotRadians), sin(rotRadians));
            mImage.SetPosition(mOwner->GetPosition() + rotNormal * 14.0f);
            mImage.SetRotation(mOwner->GetRotation());

            m_FireLight->setPosition(mOwner->GetPosition() + rotNormal * 14.0f);

            target.Draw(mImage);
        }
    }

    void Weapon::fire(EntityManager& em, const sf::Vector2f pos, float angle, float speed)
    {
        if (m_Loaded)
        {
            if (mShootTimer > mShootDelay)
            {
                if (mBulletsInMag > 0)
                {
                    float rotRadians = radians(angle);
                    sf::Vector2f offset(cos(rotRadians), sin(rotRadians));
                    em.add(EntityFactory::createProjectile(mOwner->getWorld(), pos + offset * 20.0f, angle, speed, mDamage));

                    //m_FireLight->setOn(true);

                    mFireSound.Play();

                    mBulletsInMag -= 1;
                    mShootTimer = 0.0f;
                }
                else
                {
                    reload();
                }
            }
        }
    }

    void Weapon::reload()
    {
        if (m_Loaded)
        {
            if (!mReloading && mBulletsInMag < mMagCapacity && mBullets > 0)
            {
                mReloadSound.Play();

                mReloading = true;
            }
        }
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
        return mMagCapacity;
    }

    int Weapon::getBulletsInMag()
    {
        return mBulletsInMag;
    }

    Weapon Weapon::copy()
    {
        return Weapon(mName, mMagCapacity, m_Firerate, mDamage, mReloadDelay);
    }
}
