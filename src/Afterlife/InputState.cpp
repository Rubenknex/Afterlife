#include "InputState.h"

#define ADDKEY(s, key) m_KeyMap.insert(std::pair<std::string, sf::Key::Code>(s, key))

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

        ADDKEY("a", sf::Key::A);
        ADDKEY("s", sf::Key::S);
        ADDKEY("d", sf::Key::D);
        ADDKEY("w", sf::Key::W);
        ADDKEY("space", sf::Key::Space);
        ADDKEY("enter", sf::Key::Return);
        ADDKEY("left", sf::Key::Left);
        ADDKEY("right", sf::Key::Right);
        ADDKEY("up", sf::Key::Up);
        ADDKEY("down", sf::Key::Down);
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

    sf::Key::Code InputState::getKeyCode(const std::string& s)
    {
        std::map<std::string, sf::Key::Code>::iterator it = m_KeyMap.find(s);

        if (it != m_KeyMap.end())
            return it->second;

        return sf::Key::Count;
    }
}
