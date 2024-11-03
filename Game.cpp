#include "Game.h"
#include "FoodFactory.h"
#include <iostream>

Game::Game(const std::string& playerName) : playerName(playerName) {
    gameOver = false;

    normalFood = FoodFactory::createFood(FoodType::Normal, R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\normal.png)");
    poisonousFood = FoodFactory::createFood(FoodType::Poisonous, R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\poisonous.png)");
}

void Game::run(sf::RenderWindow& window) {
    window.setFramerateLimit(10);

    while (window.isOpen() && !gameOver) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else {
                Command command = InputHandler::handleInput(event);
                handleCommand(command);
            }
        }

        update();
        render(window);
    }

    Scoreboard::getInstance().saveScore(playerName, snake.getSize());
}

int Game::getFinalScore() const {
    return snake.getSize();
}

void Game::update() {
    snake.move();

    if (snake.getHeadPosition() == normalFood->getPosition()) {
        snake.growSnake();
        normalFood->respawn();
        snake.setFirstFoodEaten();
    }

    if (snake.getHeadPosition() == poisonousFood->getPosition()) {
        if (snake.getSize() > 1) {
            snake.shrinkSnake();
            poisonousFood->respawn();
        }
        else {
            Scoreboard::getInstance().saveScore(playerName, snake.getSize());
            gameOver = true;
        }
    }

    if (snake.checkCollision()) {
        Scoreboard::getInstance().saveScore(playerName, snake.getSize());
        gameOver = true;
    }

    if (snake.reachedMaxSize()) {
        Scoreboard::getInstance().saveScore(playerName, snake.getSize());
        std::cout << "Congratulations! You reached the maximum size!" << std::endl;
        gameOver = true;
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear(sf::Color(20, 20, 50));
    drawGrid(window);
    snake.draw(window);
    normalFood->draw(window);
    poisonousFood->draw(window);
    window.display();
}

void Game::handleCommand(Command command) {
    switch (command) {
        case Command::MoveUp:
            snake.changeDirection(Up);
            break;
        case Command::MoveDown:
            snake.changeDirection(Down);
            break;
        case Command::MoveLeft:
            snake.changeDirection(Left);
            break;
        case Command::MoveRight:
            snake.changeDirection(Right);
            break;
        case Command::Confirm:
            gameOver = true;
            break;
        default:
            break;
    }
}

void Game::drawGrid(sf::RenderWindow& window) {
    const int WIDTH = 1500;
    const int HEIGHT = 1000;
    const int SIZE = 50;

    for (int x = 0; x < WIDTH; x += SIZE) {
        for (int y = 0; y < HEIGHT; y += SIZE) {
            sf::RectangleShape cell(sf::Vector2f(SIZE, SIZE));
            cell.setPosition(x, y);
            cell.setFillColor(sf::Color::Transparent);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(75, 0, 130));
            window.draw(cell);
        }
    }
}