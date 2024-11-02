#include "GameLauncher.h"
#include <iostream>

GameLauncher::GameLauncher()
        : window(sf::VideoMode(400, 400), "Snake Game Main Menu"),
          scoreboard("C:/KSE/OOP_design/Assignment_5_6/asmt-5-game-engine-olesia-mykhailyshyn/Scoreboard.txt")
{
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        std::cerr << "Font loading failed!" << std::endl;
    }
}

void GameLauncher::run() {
    while (window.isOpen()) {
        displayMenu();
        handleMenuSelection();
    }
}

void GameLauncher::displayMenu() {
    window.clear();

    sf::Text title("Snake Game", font, 50);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(80, 50);

    sf::Text option1("1. Start New Game", font, 30);
    sf::Text option2("2. View Top Scores", font, 30);
    sf::Text option3("3. Exit", font, 30);

    option1.setPosition(100, 150);
    option2.setPosition(100, 220);
    option3.setPosition(100, 290);

    option1.setFillColor(selectedOption == 0 ? sf::Color::Yellow : sf::Color::White);
    option2.setFillColor(selectedOption == 1 ? sf::Color::Yellow : sf::Color::White);
    option3.setFillColor(selectedOption == 2 ? sf::Color::Yellow : sf::Color::White);

    window.draw(title);
    window.draw(option1);
    window.draw(option2);
    window.draw(option3);
    window.display();
}

void GameLauncher::displayScoreboard() {
    sf::RenderWindow scoreWindow(sf::VideoMode(400, 600), "Scoreboard");

    if (!scoreboard.load()) {
        std::cerr << "Failed to load scores from file." << std::endl;
        return;
    }

    auto scores = scoreboard.getScores();
    std::sort(scores.begin(), scores.end(), [](const Player &a, const Player &b) {
        return a.score > b.score;
    });

    while (scoreWindow.isOpen()) {
        sf::Event event;
        while (scoreWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                scoreWindow.close();
            }
        }

        scoreWindow.clear(sf::Color::Black);

        sf::Text title("Top Scores", font, 40);
        title.setFillColor(sf::Color::White);
        title.setPosition(100, 20);
        scoreWindow.draw(title);

        float yPos = 100;
        int rank = 1;
        for (const auto &player : scores) {
            sf::Text scoreText(std::to_string(rank++) + ". " + player.name + ": " + std::to_string(player.score), font, 25);
            scoreText.setPosition(50, yPos);
            scoreText.setFillColor(rank == 1 ? sf::Color::Yellow : sf::Color::White);
            scoreWindow.draw(scoreText);
            yPos += 40;
            if (yPos > 500) break;
        }

        sf::Text exitText("Press ESC to return to Main Menu", font, 20);
        exitText.setPosition(50, 550);
        exitText.setFillColor(sf::Color::White);
        scoreWindow.draw(exitText);

        scoreWindow.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            scoreWindow.close();
        }
    }
}

void GameLauncher::handleMenuSelection() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                selectedOption = (selectedOption - 1 + 3) % 3;
            } else if (event.key.code == sf::Keyboard::Down) {
                selectedOption = (selectedOption + 1) % 3;
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedOption == 0) {
                    startGame();
                } else if (selectedOption == 1) {
                    displayScoreboard();
                } else if (selectedOption == 2) {
                    window.close();
                }
            }
        }
    }
}

void GameLauncher::startGame() {
    game = std::make_unique<Game>(window);
    sf::Clock clock;
    while (window.isOpen() && !game->gameOver()) {
        sf::Event event;
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
            }

            clock.restart();
        }

        window.clear();
        game->draw();
        window.display();
    }
}