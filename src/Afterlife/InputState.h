#ifndef INPUTSTATE_H_INCLUDED
#define INPUTSTATE_H_INCLUDED

#include <map>
#include <iostream>
#include <SFML/Window/Input.hpp>

namespace al
{
    /// Provides high level methods for retrieving input.
    class InputState
    {
        public:
            InputState();
            ~InputState();

            /// Update the input state, copy all the key states and mouse position.
            void update(const sf::Input& input);

            /// Keyboard key methods.
            bool isKeyDown(sf::Key::Code keyCode);
            bool isKeyUp(sf::Key::Code keyCode);
            bool isKeyFirstDown(sf::Key::Code keyCode);
            bool isKeyFirstUp(sf::Key::Code keyCode);

            /// Mouse button methods.
            bool isMouseButtonDown(sf::Mouse::Button button);
            bool isMouseButtonUp(sf::Mouse::Button button);
            bool isMouseButtonFirstDown(sf::Mouse::Button button);
            bool isMouseButtonFirstUp(sf::Mouse::Button button);

            /// Mouse position methods.
            int getMouseX();
            int getMouseY();
            sf::Vector2i getMousePos();
            sf::Vector2i getMouseDelta();

            /// Convert a string to a key code.
            sf::Key::Code getKeyCode(const std::string& s);

        private:
            bool mCurrentKeys[sf::Key::Count];
            bool mPreviousKeys[sf::Key::Count];

            bool mCurrentMouseButtons[sf::Mouse::ButtonCount];
            bool mPreviousMouseButtons[sf::Mouse::ButtonCount];

            int mCurrentMouseX;
            int mPreviousMouseX;
            int mCurrentMouseY;
            int mPreviousMouseY;

            std::map<std::string, sf::Key::Code> m_KeyMap;
    };

    /// There is only one keyboard/mouse per game, so just make it a global variable for ease of access.
    extern InputState g_Input;
}

#endif // INPUTSTATE_H_INCLUDED
