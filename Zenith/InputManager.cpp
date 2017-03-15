#include "InputManager.h"
#include "WindowManager.h"

namespace Zenith {
    InputManager::InputManager() {}

    InputManager::~InputManager() {}

    void InputManager::update(WindowManager* window) {
        m_mouse.update();
        SDL_Event evnt;
        while (SDL_PollEvent(&evnt)) {
            switch (evnt.type) {
            case SDL_QUIT:
                window->recieveMessage(WindowMessage::QUIT);
                break;
            case SDL_KEYDOWN:
                pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                switch (evnt.button.button) {
                case SDL_BUTTON_LEFT:
                    m_mouse.releaseButton(MouseButton::BUTTON_LEFT);
                    break;
                case SDL_BUTTON_RIGHT:
                    m_mouse.releaseButton(MouseButton::BUTTON_RIGHT);
                    break;
                case SDL_BUTTON_MIDDLE:
                    m_mouse.releaseButton(MouseButton::BUTTON_MIDDLE);
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                m_mouse.move(evnt.motion.x, evnt.motion.y, evnt.motion.xrel, evnt.motion.yrel);
                break;
            case SDL_MOUSEWHEEL:
                m_mouse.scroll(evnt.wheel.y);
                break;
            }
        }

        for (auto& it : m_keyMap) {
            if (m_previousKeyMap[it.first].timer <= 0) {
                m_previousKeyMap[it.first].timer = 0;
                m_previousKeyMap[it.first].pressed = it.second;
            }
            else --m_previousKeyMap[it.first].timer; /**< Decrease key press time.*/
        }
    }

    void InputManager::pressKey(KeyID key) {
        /* Associative map */
        m_keyMap[key] = true;
    }

    void InputManager::releaseKey(KeyID key) {
        m_keyMap[key] = false;
        m_previousKeyMap[key] = true;
    }

    KeyState InputManager::keyState(KeyID key) const{
        if (isKeyPressed(key)) return KeyState::TAPPED;
        if (isKeyDown(key)) return KeyState::PRESSED;
        if (wasKeyReleased(key)) return KeyState::RELEASED;
        return KeyState::NOTACTIVE;
    }

    bool InputManager::isKeyDown(KeyID key) const{
        /* Don't create arbitrary keys */
        auto it = m_keyMap.find(key);
        if (it != m_keyMap.end()) {
            /* Found the key in map */
            return it->second;
        }
        return false;
    }

    bool InputManager::isKeyPressed(KeyID key) const{
        if (isKeyDown(key) && !wasKeyReleased(key)) {
            return true;
        }
        return false;
    }

    bool InputManager::wasKeyReleased(KeyID key) const{
        /* Don't create arbitrary keys */
        auto it = m_previousKeyMap.find(key);
        if (it != m_previousKeyMap.end()) {
            /* Found the key in map */
            return it->second.pressed;
        }
        return false;
    }

    void Mouse::update() {
        m_yRel = 0;
        m_xRel = 0;
        for (auto& it : m_buttonMap) {
            if (m_previousButtonMap[it.first].timer <= 0) {
                m_previousButtonMap[it.first].timer = 0;
                m_previousButtonMap[it.first].pressed = it.second;
            }
            else --m_previousButtonMap[it.first].timer; /**< Decrease key press time.*/
        }
    }

    void Mouse::pressButton(MouseButton button) {
        m_buttonMap[button] = true;
    }

    void Mouse::releaseButton(MouseButton button) {
        m_buttonMap[button] = true;
        m_previousButtonMap[button] = true;
    }

    bool Mouse::isButtonDown(MouseButton button) {
        /* Don't create arbitrary keys */
        auto it = m_buttonMap.find(button);
        if (it != m_buttonMap.end()) {
            /* Found the key in map */
            return it->second;
        }
        return false;
    }

    bool Mouse::isButtonPressed(MouseButton button) {
        if (isButtonDown(button) && !wasButtonReleased(button)) {
            return true;
        }
        return false;
    }

    bool Mouse::wasButtonReleased(MouseButton button) {
        /* Don't create arbitrary keys */
        auto it = m_previousButtonMap.find(button);
        if (it != m_previousButtonMap.end()) {
            /* Found the key in map */
            return it->second.pressed;
        }
        return false;
    }

}