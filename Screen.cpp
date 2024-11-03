#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Scoreboard.h"

const int WIDTH = 1500;
const int HEIGHT = 1000;

int showWelcomeScreen(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        throw std::runtime_error("Unable to load font!");
    }

    sf::Text title("Welcome to Snake Game", font, 50);
    title.setFillColor(sf::Color::White);
    title.setPosition(WIDTH / 2 - title.getGlobalBounds().width / 2, HEIGHT / 4);

    sf::Text option1("1: Start Game", font, 30);
    option1.setFillColor(sf::Color::Green);
    option1.setPosition(WIDTH / 2 - option1.getGlobalBounds().width / 2, HEIGHT / 2 - 50);

    sf::Text option2("2: View Scoreboard", font, 30);
    option2.setFillColor(sf::Color::Yellow);
    option2.setPosition(WIDTH / 2 - option2.getGlobalBounds().width / 2, HEIGHT / 2);

    sf::Text option3("3: Exit", font, 30);
    option3.setFillColor(sf::Color::Red);
    option3.setPosition(WIDTH / 2 - option3.getGlobalBounds().width / 2, HEIGHT / 2 + 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    return 1; // Start Game
                } else if (event.key.code == sf::Keyboard::Num2) {
                    return 2; // View Scoreboard
                } else if (event.key.code == sf::Keyboard::Num3) {
                    window.close(); // Exit
                    return 3;
                }
            }
        }

        window.clear(sf::Color(20, 20, 50));
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.display();
    }
    return 3;
}


std::string enterPlayerName(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        throw std::runtime_error("Unable to load font!");
    }

    sf::Text prompt("Enter your name:", font, 30);
    prompt.setFillColor(sf::Color::White);
    prompt.setPosition(WIDTH / 2 - prompt.getGlobalBounds().width / 2, HEIGHT / 3);

    sf::Text warningMessage("", font, 25);
    warningMessage.setFillColor(sf::Color::Red);
    warningMessage.setPosition(WIDTH / 2 - 100, HEIGHT / 3 + 100);

    sf::Text instruction("Press Enter to confirm or 3 to return to main menu", font, 20);
    instruction.setFillColor(sf::Color::White);
    instruction.setPosition(WIDTH / 2 - instruction.getGlobalBounds().width / 2, HEIGHT / 3 + 150);

    std::string playerName = "";
    sf::Text playerNameText("", font, 30);
    playerNameText.setFillColor(sf::Color::Yellow);
    playerNameText.setPosition(WIDTH / 2 - 100, HEIGHT / 3 + 50);

    sf::RectangleShape inputBox(sf::Vector2f(400, 50));
    inputBox.setFillColor(sf::Color(50, 50, 50));
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(WIDTH / 2 - 200, HEIGHT / 3 + 45);

    sf::Event clearEvent;
    while (window.pollEvent(clearEvent)) {
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !playerName.empty()) {
                    playerName.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r') {
                    playerName += static_cast<char>(event.text.unicode);
                }
                playerNameText.setString(playerName);
                warningMessage.setString("");
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (playerName.empty()) {
                        warningMessage.setString("Please enter a name to start the game.");
                    }
                    else {
                        return playerName;
                    }
                } else if (event.key.code == sf::Keyboard::Num3) {
                    return "";
                }
            }
        }

        window.clear(sf::Color(20, 20, 50));
        window.draw(prompt);
        window.draw(inputBox);
        window.draw(playerNameText);
        window.draw(warningMessage);
        window.draw(instruction);
        window.display();
    }

    return "";
}

void showGameOverScreen(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        throw std::runtime_error("Unable to load font!");
    }

    sf::Text gameOverText("Game Over", font, 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(WIDTH / 2 - gameOverText.getGlobalBounds().width / 2, HEIGHT / 3);

    sf::Text restartText("Press Enter to return to the main menu", font, 30);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(WIDTH / 2 - restartText.getGlobalBounds().width / 2, HEIGHT / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return;
            }
        }

        window.clear(sf::Color(20, 20, 50));
        window.draw(gameOverText);
        window.draw(restartText);
        window.display();
    }
}

void showScoreboard(sf::RenderWindow& window, const std::string& playerName, int playerScore) {
    Scoreboard scoreboard(R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\Scoreboard.txt)");
    scoreboard.loadScores();

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        throw std::runtime_error("Unable to load font!");
    }

    sf::Text scoreboardTitle("Scoreboard", font, 50);
    scoreboardTitle.setFillColor(sf::Color::Yellow);
    scoreboardTitle.setPosition(WIDTH / 2 - scoreboardTitle.getGlobalBounds().width / 2, HEIGHT / 10);

    window.clear(sf::Color(20, 20, 50));
    window.draw(scoreboardTitle);

    int y_offset = HEIGHT / 4;
    int count = 1;

    // Display top 3 scores with highlighted color
    for (const auto& score : scoreboard.getTopScores(3)) {
        std::string scoreText = std::to_string(count) + ". " + score.name + " - " + std::to_string(score.score);
        sf::Text scoreEntry(scoreText, font, 30);
        scoreEntry.setFillColor(sf::Color::Cyan);  // Highlight color for top scores
        scoreEntry.setPosition(WIDTH / 4, y_offset);
        window.draw(scoreEntry);
        y_offset += 50;
        count++;
    }

    // Show the current game's rank if it’s not in the top 3
    int playerRank = scoreboard.getRank(playerName, playerScore);
    if (playerRank > 3) {
        std::string playerRankText = "Your rank: " + std::to_string(playerRank) + ". " + playerName + " - " + std::to_string(playerScore);
        sf::Text playerRankEntry(playerRankText, font, 25);
        playerRankEntry.setFillColor(sf::Color::White);
        playerRankEntry.setPosition(WIDTH / 4, y_offset + 20);
        window.draw(playerRankEntry);
    }

    sf::Text instruction("Press Enter to return to the main menu", font, 25);
    instruction.setFillColor(sf::Color::White);
    instruction.setPosition(WIDTH / 2 - instruction.getGlobalBounds().width / 2, HEIGHT - 100);
    window.draw(instruction);

    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return;  // Return to welcome screen
            }
        }
    }
}
