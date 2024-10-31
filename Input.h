#pragma once
#include <SFML/Graphics.hpp>

enum class Input {
    Up,
    Down,
    Left,
    Right,
    Pause,
    Exit,
    None
};

class InputHandler {
public:
    static Input getInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            return Input::Up;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            return Input::Down;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            return Input::Left;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            return Input::Right;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            return Input::Pause;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return Input::Exit;
        }
        return Input::None;
    }
};