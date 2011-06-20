#ifndef LIGHTRENDERER_H_INCLUDED
#define LIGHTRENDERER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>

#include "IRenderer.h"
#include "../Scene/Light.h"
#include "../Scene/PointLight.h"
#include "../Scene/SpotLight.h"

typedef boost::shared_ptr<Light> LightPtr;

class LightRenderer : public IRenderer
{
public:
    LightRenderer(int windowWidth, int windowHeight, int lightTargetWidth, int lightTargetHeight);
    ~LightRenderer();

    void draw(sf::RenderTarget& target);
    
    void setLights(std::map<std::string, LightPtr> lights);
    void setAmbientColor(const sf::Color ambient);

private:
    sf::Shader m_blurHorizontal;
    sf::Shader m_blurVertical;
    sf::RenderImage* m_lightsImage;
    sf::RenderImage* m_horizontalPass;
    sf::RenderImage* m_verticalPass;
    sf::Sprite m_lightsSprite;
    
    std::map<std::string, LightPtr> m_lights;
    sf::Color m_ambientColor;
};

#endif // LIGHTRENDERER_H_INCLUDED
