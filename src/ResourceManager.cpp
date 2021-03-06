#include "ResourceManager.h"
 
FontManager FM;
 
shared_ptr<sf::Font> FontManager::load(const std::string& id)
{
    shared_ptr<sf::Font> font(new sf::Font());
 
    if (!font->LoadFromFile(id))
    {
        std::cout << "Failed to load: " << id << std::endl;
    }
 
    return font;
}
 
ImageManager IM;
 
shared_ptr<sf::Image> ImageManager::load(const std::string& id)
{
    //std::cout << "Loading: " << id << std::endl;
 
    shared_ptr<sf::Image> image(new sf::Image());
 
    if (!image->LoadFromFile(id))
    {
        std::cout << "Failed to load: " << id << std::endl;
 
        image->SetSmooth(false);
 
        return image;
    }
 
    return image;
}
 
SoundManager SM;
 
shared_ptr<sf::SoundBuffer> SoundManager::load(const std::string& id)
{
    shared_ptr<sf::SoundBuffer> sound(new sf::SoundBuffer());
 
    if (!sound->LoadFromFile(id))
    {
        std::cout << "Failed to load: " << id << std::endl;
    }
 
    return sound;
}
 
MusicManager MM;
 
shared_ptr<sf::Music> MusicManager::load(const std::string& id)
{
    shared_ptr<sf::Music> music(new sf::Music());
 
    if (!music->OpenFromFile(id))
    {
        std::cout << "Failed to load: " << id << std::endl;
    }
 
    return music;
}
 
