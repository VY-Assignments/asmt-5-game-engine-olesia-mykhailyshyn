#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scoreboard.h"

class GameLauncher {
public:
    GameLauncher();
    void run();

private:
    sf::RenderWindow window;
    Scoreboard scoreboard;
    std::unique_ptr<Game> game;
    sf::Font font;
    int selectedOption = 0;

    void displayMenu();
    void displayScoreboard();
    void handleMenuSelection();
    void startGame();
};
