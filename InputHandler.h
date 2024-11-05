#pragma once
#include <SFML/Window.hpp>

enum class Command {
    None,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    StartGame,
    ViewScoreboard,
    ExitGame,
    Confirm
};

class InputHandler {
public:
    static Command HandleInput(const sf::Event& event);
};