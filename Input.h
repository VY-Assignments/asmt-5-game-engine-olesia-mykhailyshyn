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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            return Input::Up;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            return Input::Down;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            return Input::Left;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            return Input::Right;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            return Input::Exit;
        }
        return Input::None;
    }
};