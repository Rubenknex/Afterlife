#include "LightRenderer.h"

LightRenderer::LightRenderer(int windowWidth, int windowHeight, int lightTargetWidth, int lightTargetHeight) :
    m_lightsImage(new sf::RenderImage()),
    m_horizontalPass(new sf::RenderImage()),
    m_verticalPass(new sf::RenderImage()),
    m_ambientColor(sf::Color::White)
{
    if (sf::Shader::IsAvailable())
    {
        m_blurHorizontal.LoadFromFile("data/Shaders/gaussian_blur_horizontal.glsl");
        m_blurVertical.LoadFromFile("data/Shaders/gaussian_blur_vertical.glsl");
        
        m_lightsImage->Create(lightTargetWidth, lightTargetHeight);
        m_horizontalPass->Create(lightTargetWidth, lightTargetHeight);
        m_verticalPass->Create(lightTargetWidth, lightTargetHeight);
        
        m_verticalPass->SetSmooth(true);
        
        m_lightsSprite.SetImage(m_verticalPass->GetImage());
        m_lightsSprite.SetBlendMode(sf::Blend::Multiply);
        m_lightsSprite.SetScale((float)(windowWidth / lightTargetWidth), (float)(windowHeight / lightTargetHeight));
    }
}

LightRenderer::~LightRenderer()
{
    delete m_lightsImage;
    delete m_horizontalPass;
    delete m_verticalPass;
}

void LightRenderer::draw(sf::RenderTarget& target)
{
    if (sf::Shader::IsAvailable())
    {
        // Clear the color of the light image to the ambient color.
        m_lightsImage->Clear(m_ambientColor);
        
        // Copy the view of the game to ensure the lights will be rendered
        // at the appropriate position.
        m_lightsImage->SetView(target.GetView());
        
        // Draw all the lights on the light image.
        boost::ptr_map<std::string, Light>::iterator it;
        for (it = m_lights->begin(); it != m_lights->end(); it++)
        {
            it->second->draw(m_lightsImage);
        }
        
        m_lightsImage->Display();
        
        // Copy the view of the game.
        sf::View gameView = target.GetView();
        sf::View lightView(gameView.GetSize() / 2.0f, gameView.GetSize());
        
        // Draw the horizontal gaussian blur effect.
        m_horizontalPass->Clear();
        m_blurHorizontal.SetTexture("frame", m_lightsImage->GetImage());
        m_blurHorizontal.SetParameter("frameWidth", (float)m_lightsImage->GetWidth());
        m_horizontalPass->Draw(sf::Sprite(m_lightsImage->GetImage()), m_blurHorizontal);
        m_horizontalPass->Display();
        
        // Draw the vertical gaussian blur effect.
        m_verticalPass->Clear();
        m_blurVertical.SetTexture("frame", m_horizontalPass->GetImage());
        m_blurVertical.SetParameter("frameHeight", (float)m_lightsImage->GetHeight());
        m_verticalPass->Draw(sf::Sprite(m_horizontalPass->GetImage()), m_blurVertical);
        m_verticalPass->Display();
        
        // Draw the light image onto the game image using multiply blend mode. This multiplies
        // all the pixels with the color on the light image. If a pixel on the light image is gray, the
        // pixel on the game image will be multiplied by 0.5, thus making it appear darker.
        target.SetView(lightView);
        target.Draw(m_lightsSprite);
        target.SetView(gameView);
    }
}

void LightRenderer::setLights(boost::ptr_map<std::string, Light>* lights)
{
    m_lights = lights;
}

void LightRenderer::setAmbientColor(const sf::Color ambient)
{
    m_ambientColor = ambient;
}
