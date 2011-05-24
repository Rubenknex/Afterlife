#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>

#include "EntityFactory.h"
#include "Functions.h"
#include "EntityManager.h"
#include "LightManager.h"
#include "PointLight.h"
#include "ResourceManager.h"

namespace al
{
    class Entity;
    class World;

    /// The data of a weapon, like rate of fire or magazine size.
    class WeaponData
    {
        friend class Weapon;
        friend class WeaponPickup;

        public:
            void load(const std::string& filename);

        private:
            std::string m_Name;
            std::string m_ImageFile;
            std::string m_FireFile;
            std::string m_ReloadFile;
            int m_MagCapacity;
            int m_FireRate;
            float m_Damage;
            float m_ReloadDelay;
    };

    /// Weapon provides behaviour of a weapon like reloading, shooting and ammunition management.
    class Weapon
    {
        public:
            //Weapon(Entity* owner);
            Weapon(const WeaponData& data);
            ~Weapon();

            /// Load a weapon from an XML file.
            //void load(const std::string& filename);

            void update(float dt);
            void draw(sf::RenderTarget& target);

            /// Fire the weapon, remove one bullet, reload if neccesary and add a projectile to the world.
            void fire(EntityManager& pm, const sf::Vector2f pos, float angle, float speed);
            /// Reload the weapon.
            void reload();

            void setOwner(Entity* e);

            int getBullets();
            void setBullets(int bullets);

            int getMagCapacity();

            int getBulletsInMag();

        private:
            Entity* m_Owner;

            WeaponData m_Data;

            float mShootTimer;

            int mBullets;
            int mBulletsInMag;

            bool mReloading;
            float mReloadTimer;

            sf::Sprite m_Image;
    };
}

#endif // WEAPON_H_INCLUDED
