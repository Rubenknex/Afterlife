#ifndef SFXPLAYER_H_INCLUDED
#define SFXPLAYER_H_INCLUDED

#include <map>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"

namespace al
{
    class SFXPlayer
    {
        public:


            void play(const std::string& name, float volume, float pitch);

        private:
            std::map<std::string, sf::Sound> m_Sounds;
    };

    extern SFXPlayer g_SFXPlayer;
}

#endif // SFXPLAYER_H_INCLUDED
