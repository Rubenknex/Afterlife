#include "LightManager.h"

namespace al
{
    LightManager::LightManager() :
        mLightsImage(new sf::RenderImage()),
        mHorizontalPass(new sf::RenderImage()),
        mVerticalPass(new sf::RenderImage()),
        mAmbientColor(sf::Color::White)
    {
        if (sf::Shader::IsAvailable())
        {
            mBlurHorizontal.LoadFromFile("data/Shaders/gaussian_blur_horizontal.shader");
            mBlurVertical.LoadFromFile("data/Shaders/gaussian_blur_vertical.shader");
        }

        mLightsImage->Create(640, 360);
        mHorizontalPass->Create(640, 360);
        mVerticalPass->Create(640, 360);
        mVerticalPass->SetSmooth(true);

        mLightsSprite.SetImage(mVerticalPass->GetImage());
        mLightsSprite.SetBlendMode(sf::Blend::Multiply);
        mLightsSprite.SetScale(2.0f, 2.0f);
    }

    LightManager::~LightManager()
    {
        mLights.clear();

        delete mLightsImage;
        delete mHorizontalPass;
        delete mVerticalPass;
    }

    void LightManager::addLight(LightPtr light)
    {
        mLights.insert(light);
    }

    void LightManager::removeLight(LightPtr light)
    {
        mLights.erase(mLights.find(light));
    }

    void LightManager::draw(sf::RenderTarget& target)
    {
        // Clear the color of the light image to the ambient color.
        mLightsImage->Clear(mAmbientColor);

        // Copy the view of the game to ensure the lights will be rendered
        // at the appropriate position.
        mLightsImage->SetView(target.GetView());

        // Draw all the lights on the light image.
        std::set<LightPtr>::iterator it;
        for (it = mLights.begin(); it != mLights.end(); it++)
        {
            (*it)->draw(mLightsImage);
        }

        mLightsImage->Display();

        // Copy the view of the game.
        sf::View gameView = target.GetView();
        sf::View lightView(gameView.GetSize() / 2.0f, gameView.GetSize());

        // Draw the horizontal gaussian blur effect.
        mHorizontalPass->Clear();
        mBlurHorizontal.SetTexture("frame", mLightsImage->GetImage());
        mBlurHorizontal.SetParameter("frameWidth", (float)mLightsImage->GetWidth());
        mHorizontalPass->Draw(sf::Sprite(mLightsImage->GetImage()), mBlurHorizontal);
        mHorizontalPass->Display();

        // Draw the vertical gaussian blur effect.
        mVerticalPass->Clear();
        mBlurVertical.SetTexture("frame", mHorizontalPass->GetImage());
        mBlurVertical.SetParameter("frameHeight", (float)mLightsImage->GetHeight());
        mVerticalPass->Draw(sf::Sprite(mHorizontalPass->GetImage()), mBlurVertical);
        mVerticalPass->Display();

        // Draw the light image onto the game image using multiply blend mode. This multiplies
        // all the pixels with the color on the light image. If a pixel on the light image is gray, the
        // pixel on the game image will be multiplied by 0.5, thus making it appear darker.
        target.SetView(lightView);
        target.Draw(mLightsSprite);
        target.SetView(gameView);
    }

    void LightManager::setAmbientColor(const sf::Color& color)
    {
        mAmbientColor = color;
    }
}
