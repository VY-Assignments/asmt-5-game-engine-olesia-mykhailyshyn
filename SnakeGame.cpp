#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include "Game.h"
#include "Screen.h"
#include "Scoreboard.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Snake Game");

    while (window.isOpen()) {
        int choice = showWelcomeScreen(window);
        if (choice == 3 || !window.isOpen()) return 0;

        if (choice == 2) {
            Scoreboard& scoreboard = Scoreboard::getInstance();
            scoreboard.loadScores();
            showScoreboard(window, "", 0);  
            continue;
        }

        if (choice == 1) {
            std::string playerName = enterPlayerName(window);
            if (playerName.empty()) continue;

            Game game(playerName);
            game.run(window);

            if (window.isOpen()) {
                showScoreboard(window, playerName, game.getFinalScore());
                showGameOverScreen(window);
            }
        }
    }

    return 0;
}