#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Animation.h"
#include "Collision.h"
#include "DirectionalLight.h"
#include "Entity.h"
#include "Functions.h"
#include "Game.h"
#include "Grenade.h"
#include "InputState.h"
#include "LightManager.h"
#include "ResourceManager.h"
#include "InputState.h"
#include "Level.h"

using boost::shared_ptr;

namespace al
{
    class Weapon;
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

        private:
            Animation mAnimation;
            Weapon* mWeapon;
            shared_ptr<DirectionalLight> mFlashLight;

            bool mRightMouseDown;
            float mRightMouseTimer;
    };
}

#endif // PLAYER_H_INCLUDED
