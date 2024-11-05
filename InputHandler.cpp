#include "InputHandler.h"

Command InputHandler::HandleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Up: {
                return Command::MoveUp;
            }
            case sf::Keyboard::Down: {
                return Command::MoveDown;
            }
            case sf::Keyboard::Left: {
                return Command::MoveLeft;
            }
            case sf::Keyboard::Right: {
                return Command::MoveRight;
            }
            case sf::Keyboard::Num1: {
                return Command::StartGame;
            }
            case sf::Keyboard::Num2: {
                return Command::ViewScoreboard;
            }
            case sf::Keyboard::Num3: {
                return Command::ExitGame;
            }
            case sf::Keyboard::Enter: {
                return Command::Confirm;
            }
            default: {
                return Command::None;
            }
        }
    }
    return Command::None;
}