#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include "Game.h"
#include "Screen.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Snake Game");

    while (window.isOpen()) {
        showWelcomeScreen(window);
        if (!window.isOpen()) {
            return 0;
        }

        std::string playerName = enterPlayerName(window);
        if (playerName.empty()) {
            continue;
        }

        Game game(playerName);
        game.run(window);

        if (window.isOpen()) {
            showGameOverScreen(window);
        }
    }

    return 0;
}