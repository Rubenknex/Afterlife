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

    /// Weapon provides behaviour of a weapon like reloading, shooting and ammunition management.
    class Weapon
    {
        public:
            Weapon(Entity* owner);
            Weapon(const std::string& name, int capacity, int firerate, float damage, float reloadTime);
            ~Weapon();

            /// Load a weapon from an XML file.
            void load(const std::string& filename);

            void update(float dt);
            void draw(sf::RenderTarget& target);

            /// Fire the weapon, remove one bullet, reload if neccesary and add a projectile to the world.
            void fire(EntityManager& pm, const sf::Vector2f pos, float angle, float speed);
            /// Reload the weapon.
            void reload();

            int getBullets();
            void setBullets(int bullets);

            int getMagCapacity();

            int getBulletsInMag();

            /// Copy's the weapon. At the beginning of the game all weapons will be loaded and when
            /// the player picks up a weapon the loaded weapon will be copied.
            Weapon copy();

        private:
            Entity* mOwner;

            bool m_Loaded;

            std::string mName;

            float mDamage;

            int m_Firerate;
            float mShootTimer;
            float mShootDelay;

            int mBullets;
            int mBulletsInMag;
            int mMagCapacity;

            bool mReloading;
            float mReloadTimer;
            float mReloadDelay;

            sf::Sprite mImage;
            sf::Sound mFireSound;
            sf::Sound mReloadSound;

            boost::shared_ptr<PointLight> m_FireLight;
    };
}

#endif // WEAPON_H_INCLUDED
