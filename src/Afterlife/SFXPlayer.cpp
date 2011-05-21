#include "SFXPlayer.h"

namespace al
{
    SFXPlayer g_SFXPlayer;

    void SFXPlayer::play(const std::string& name, float volume, float pitch)
    {
        std::map<std::string, sf::Sound>::iterator it = m_Sounds.find(name);

        if (it == m_Sounds.end())
        {
            sf::Sound sound;
            sound.SetBuffer(*SM.GetResource(name));

            m_Sounds.insert(std::pair<std::string, sf::Sound>(name, sound));

            it = m_Sounds.find(name);
        }

        it->second.SetVolume(volume);
        it->second.SetPitch(pitch);
        it->second.Play();
    }
}
