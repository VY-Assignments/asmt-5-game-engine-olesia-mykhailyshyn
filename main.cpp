#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Scoreboard.h"

void displayMenu(sf::RenderWindow &window) {
    window.clear();
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        std::cerr << "Font loading failed!" << std::endl;
        return;
    }

    sf::Text title("Snake Game", font, 30);
    title.setPosition(120, 50);

    sf::Text option1("1. Start New Game", font, 20);
    option1.setPosition(120, 150);

    sf::Text option2("2. View Top Scores", font, 20);
    option2.setPosition(120, 200);

    sf::Text option3("3. Exit", font, 20);
    option3.setPosition(120, 250);

    window.draw(title);
    window.draw(option1);
    window.draw(option2);
    window.draw(option3);
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Snake Game Main Menu");
    Scoreboard scoreboard("C:/KSE/OOP_design/Assignment_5_6/asmt-5-game-engine-olesia-mykhailyshyn/Scoreboard.txt");

    std::unique_ptr<Game> game = nullptr;
    bool gameRunning = false;

    while (window.isOpen()) {
        if (!gameRunning) {
            displayMenu(window);

            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Num1) {
                        // Start a new game
                        game = std::make_unique<Game>(window);
                        gameRunning = true;
                    } else if (event.key.code == sf::Keyboard::Num2) {
                        // View top scores
                        window.clear();
                        scoreboard.load();
                        scoreboard.display();
                        system("pause");  // Wait for user to press a key
                        displayMenu(window);  // Redisplay menu after viewing scores
                    } else if (event.key.code == sf::Keyboard::Num3) {
                        // Exit
                        window.close();
                    }
                }
            }
        } else {
            // Run the game loop
            sf::Clock clock;

            while (window.isOpen() && gameRunning) {
                sf::Event event{};
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }

                if (clock.getElapsedTime().asSeconds() > 0.1f) {
                    game->handleInput();
                    game->run();

                    if (game->gameOver()) {
                        scoreboard.addPlayer({"Player", game->getScore()});
                        scoreboard.save();
                        gameRunning = false;
                        displayMenu(window);
                    }

                    clock.restart();
                }

                window.clear();
                game->draw();
                window.display();
            }
        }
    }

    return 0;
}