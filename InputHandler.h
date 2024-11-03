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
    InputHandler();
    static Command handleInput(const sf::Event& event);

private:
    Command currentCommand;
};