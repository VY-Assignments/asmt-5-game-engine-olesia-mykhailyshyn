#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <cstdlib>
#include <ctime>

GameState::GameState(int width, int height, sf::RenderWindow &window, const std::string &scoreboardPath)
        : board(width, height, window),
          snake("C:/KSE/OOP_design/Assignment_5_6/asmt-5-game-engine-olesia-mykhailyshyn/Head.png",
                "C:/KSE/OOP_design/Assignment_5_6/asmt-5-game-engine-olesia-mykhailyshyn/BodyBlock.png"),
          scoreboard(scoreboardPath),
          isGameOver(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));  // Seed for random food position
    scoreboard.manageScoreboard();
    createNewFood();
}

void GameState::createNewFood() {
    auto *newFood = new NormalFood();
    int x = std::rand() % board.getWidth();
    int y = std::rand() % board.getHeight();
    newFood->setPosition(x, y);

    board.addFood(newFood);
}

void GameState::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        snake.setDirection(Snake::Direction::Up);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        snake.setDirection(Snake::Direction::Down);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        snake.setDirection(Snake::Direction::Left);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        snake.setDirection(Snake::Direction::Right);
    }
}

void GameState::update() {
    if (!isGameOver) {
        snake.move();

        if (!board.isWithinBounds(snake.getHeadPosition()) || snake.hasCollidedWithItself()) {
            isGameOver = true;
            return;
        }

        for (auto &food : board.getFoods()) {
            if (snake.getHeadPosition().x == food->getPosition().getX() &&
                snake.getHeadPosition().y == food->getPosition().getY()) {
                snake.applyFoodEffect(*food);
                board.removeFood(food);
                createNewFood();
                break;
            }
        }
    }
}

void GameState::draw() {
    board.clear();
    board.draw();
    snake.draw(board.getWindow());
}

bool GameState::gameOver() const {
    return isGameOver;
}
