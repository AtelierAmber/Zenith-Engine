#pragma once
#include "KeyCode.h"

#include <unordered_map>

#include <SDL/SDL.h>

namespace Zenith {
#define frames_per_key_update 2
    struct KeyRef {
        KeyRef() : pressed(false), timer(0) {}
        bool pressed;
        int timer;

        KeyRef& operator=(bool press) {
            pressed = true;
            timer = frames_per_key_update;
            return *this;
        }
    };

    enum class MouseButton {
        BUTTON_LEFT = 1,
        BUTTON_MIDDLE = 2,
        BUTTON_RIGHT = 3,
    };
    struct Mouse {
    public:
        void update();

        void move(int x, int y, int xRel, int yRel) { 
            m_x = x; m_y = y;
            m_xRel = xRel; m_yRel = yRel;
        }

        void pressButton(MouseButton button);
        void releaseButton(MouseButton button);
        void scroll(int value) { m_scroll = value; }

        bool isButtonDown(MouseButton button);
        bool isButtonPressed(MouseButton button);
        bool wasButtonReleased(MouseButton button);

        int getX() const { return m_x; }
        int getY() const { return m_y; }
        int getXRel() const { return m_xRel; }
        int getYRel() const { return m_yRel; }
    private:
        int m_scroll;
        int m_x, m_y;
        int m_xRel, m_yRel;
        std::unordered_map<MouseButton, bool> m_buttonMap;
        std::unordered_map<MouseButton, KeyRef> m_previousButtonMap;
    };

    class WindowManager;
    /* Input manager stores a key map that maps Keys to booleans.
     * If the value in the key map is true, then the key is pressed.
     * Otherwise, it is released after 2 frames to prevent misread inputs.
     */

    class InputManager {
    public:
        InputManager();
        ~InputManager();

        void update(WindowManager* window);

        void pressKey(KeyID key);
        void releaseKey(KeyID key);

        KeyState keyState(KeyID key) const;

        const Mouse& getMouse() const { return m_mouse; }
    private:
        bool isKeyDown(KeyID key) const;
        bool isKeyPressed(KeyID key) const;
        bool wasKeyReleased(KeyID key) const;

        std::unordered_map<KeyID, bool> m_keyMap;
        std::unordered_map<KeyID, KeyRef> m_previousKeyMap;
        Mouse m_mouse;
    };
}