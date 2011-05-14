#include "InputState.h"

namespace al
{
    InputState g_Input;

    InputState::InputState()
    {
        for (int i = 0; i < (int)sf::Key::Count; i++)
        {
            mPreviousKeys[i] = false;
            mCurrentKeys[i] = false;
        }

        for (int i = 0; i < sf::Mouse::ButtonCount; i++)
        {
            mPreviousMouseButtons[i] = false;
            mCurrentMouseButtons[i] = false;
        }

        mPreviousMouseX = 0;
        mPreviousMouseY = 0;
        mCurrentMouseX = 0;
        mCurrentMouseY = 0;
    }

    InputState::~InputState()
    {

    }

    void InputState::update(const sf::Input& input)
    {
        for (int i = 0; i < sf::Key::Count; i++)
        {
            mPreviousKeys[i] = mCurrentKeys[i];
            mCurrentKeys[i] = input.IsKeyDown((sf::Key::Code)i);
        }

        for (int i = 0; i < sf::Mouse::ButtonCount; i++)
        {
            mPreviousMouseButtons[i] = mCurrentMouseButtons[i];
            mCurrentMouseButtons[i] = input.IsMouseButtonDown((sf::Mouse::Button)i);
        }

        mPreviousMouseX = mCurrentMouseX;
        mPreviousMouseY = mCurrentMouseY;
        mCurrentMouseX = input.GetMouseX();
        mCurrentMouseY = input.GetMouseY();
    }

    bool InputState::isKeyDown(sf::Key::Code keyCode)
    {
        return mCurrentKeys[keyCode];
    }

    bool InputState::isKeyUp(sf::Key::Code keyCode)
    {
        return !mCurrentKeys[keyCode];
    }

    bool InputState::isKeyFirstDown(sf::Key::Code keyCode)
    {
        return !mPreviousKeys[keyCode] && mCurrentKeys[keyCode];
    }

    bool InputState::isKeyFirstUp(sf::Key::Code keyCode)
    {
        return mPreviousKeys[keyCode] && !mCurrentKeys[keyCode];
    }

    bool InputState::isMouseButtonDown(sf::Mouse::Button button)
    {
        return mCurrentMouseButtons[button];
    }

    bool InputState::isMouseButtonUp(sf::Mouse::Button button)
    {
        return !mCurrentMouseButtons[button];
    }

    bool InputState::isMouseButtonFirstDown(sf::Mouse::Button button)
    {
        return mCurrentMouseButtons[button] && !mPreviousMouseButtons[button];
    }

    bool InputState::isMouseButtonFirstUp(sf::Mouse::Button button)
    {
        return !mCurrentMouseButtons[button] && mPreviousMouseButtons[button];
    }

    int InputState::getMouseX()
    {
        return mCurrentMouseX;
    }

    int InputState::getMouseY()
    {
        return mCurrentMouseY;
    }

    sf::Vector2i InputState::getMousePos()
    {
        return sf::Vector2i(mCurrentMouseX, mCurrentMouseY);
    }

    sf::Vector2i InputState::getMouseDelta()
    {
        return sf::Vector2i(mCurrentMouseX, mCurrentMouseY) - sf::Vector2i(mPreviousMouseX, mPreviousMouseY);
    }
}
