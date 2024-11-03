#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Scoreboard.h" // To access Scoreboard functions

const int WIDTH = 1500;
const int HEIGHT = 1000;
const int SIZE = 50;

void showWelcomeScreen(sf::RenderWindow& window) {
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
                    return; // Proceed to name input
                } else if (event.key.code == sf::Keyboard::Num2) {
                    showScoreboard(window, "N/A", 0); // Show scoreboard
                } else if (event.key.code == sf::Keyboard::Num3) {
                    window.close(); // Exit game
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
}


std::string enterPlayerName(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        throw std::runtime_error("Unable to load font!");
    }

    sf::Text prompt("Enter your name:", font, 30);
    prompt.setFillColor(sf::Color::White);
    prompt.setPosition(WIDTH / 2 - prompt.getGlobalBounds().width / 2, HEIGHT / 3);

    std::string playerName;
    sf::Text playerNameText("", font, 30);
    playerNameText.setFillColor(sf::Color::Yellow);
    playerNameText.setPosition(WIDTH / 2 - 100, HEIGHT / 3 + 50);

    sf::RectangleShape inputBox(sf::Vector2f(400, 50));
    inputBox.setFillColor(sf::Color(50, 50, 50));
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(WIDTH / 2 - 200, HEIGHT / 3 + 45);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b' && !playerName.empty()) {
                    playerName.pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r') {
                    playerName += static_cast<char>(event.text.unicode);
                }
                playerNameText.setString(playerName);
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (playerName.empty()) {
                    return ""; // Return empty string to indicate no name was entered
                }
                return playerName; // Return the entered name
            }
        }

        window.clear(sf::Color(20, 20, 50));
        window.draw(prompt);
        window.draw(inputBox);
        window.draw(playerNameText);
        window.display();
    }

    return ""; // Default return if window is closed
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
    std::vector<ScoreEntry> scores;
    Scoreboard scoreboard("C:\\KSE\\OOP_design\\Assignment_5_6\\asmt-5-game-engine-olesia-mykhailyshyn\\Scoreboard.txt");
    scoreboard.loadScores();

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        throw std::runtime_error("Unable to load font!");
    }

    sf::Text scoreboardTitle("Scoreboard", font, 50);
    scoreboardTitle.setFillColor(sf::Color::Yellow);
    scoreboardTitle.setPosition(WIDTH / 2 - scoreboardTitle.getGlobalBounds().width / 2, HEIGHT / 10);

    sf::Text topTitle("Top 3 Players", font, 35);
    topTitle.setFillColor(sf::Color::White);
    topTitle.setPosition(WIDTH / 4, HEIGHT / 4);

    int y_offset = HEIGHT / 3;
    int count = 1;
    for (const auto& score : scores) {
        if (count > 3) break;
        std::string scoreText = std::to_string(count) + ". " + score.name + " - " + std::to_string(score.score);
        sf::Text scoreEntry(scoreText, font, 25);
        scoreEntry.setFillColor(sf::Color(230, 230, 250));
        scoreEntry.setPosition(WIDTH / 4, y_offset);
        window.draw(scoreEntry);
        y_offset += 40;
        count++;
    }

    window.display();

    bool exitToMain = false;
    while (window.isOpen() && !exitToMain) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                exitToMain = true;
            }
        }
    }
}