#ifndef AUDIOPLAYER_H_INCLUDED
#define AUDIOPLAYER_H_INCLUDED
 
#include <map>
#include <SFML/Audio.hpp>
 
#include "ResourceManager.h"
 
struct FadeData
{
    std::string name;
    float targetVolume;
    float timer;
    float fadeTime;
};
 
class AudioPlayer
{
public:
 
    void fadeInMusic(const std::string& name, float volume, float time);
    void fadeOutMusic(const std::string& name, float time);
 
    void playSound(const std::string& name, float volume = 100.0f, float pitch = 1.0f);
 
private:
    std::map<std::string, sf::Sound> m_Sounds;
};
 
extern AudioPlayer g_audioPlayer;
 
#endif // AUDIOPLAYER_H_INCLUDED
 
