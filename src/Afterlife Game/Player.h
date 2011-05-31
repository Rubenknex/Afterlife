#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Animation.h"
#include "Collision.h"
#include "SpotLight.h"
#include "Entity.h"
#include "Functions.h"
#include "Game.h"
#include "Grenade.h"
#include "InputState.h"
#include "LightManager.h"
#include "ResourceManager.h"
#include "InputState.h"
#include "Level.h"
#include "Scripting/Script.h"
#include "Weapon.h"

using boost::shared_ptr;

namespace al
{
    class Weapon;
    class WeaponData;
    class World;

    class Player : public Entity
    {
        public:
            Player(World* world);
            ~Player();

            void update(float dt);
            void draw(sf::RenderTarget& target);

            bool onCollision(boost::shared_ptr<Entity> other);

            void handleInput();
            void handleCollision();

            Weapon* getWeapon();
            void setWeapon(const WeaponData& data);

        private:
            //Script m_UpdateScript;

            Animation mAnimation;
            Weapon* mWeapon;
            shared_ptr<SpotLight> mFlashLight;

            bool mRightMouseDown;
            float mRightMouseTimer;
    };
}

#endif // PLAYER_H_INCLUDED