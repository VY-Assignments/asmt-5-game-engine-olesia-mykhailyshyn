#include <SFML/Graphics.hpp>
#include "GameState.h"

GameState::GameState(int width, int height, sf::RenderWindow &window, const std::string &scoreboardPath)
        : board(width, height, window), snake(width / 2, height / 2), scoreboard(scoreboardPath), isGameOver(false) {
    scoreboard.manageScoreboard();
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
        if (snake.hasCollidedWithWall(board) || snake.hasCollidedWithItself()) {
            isGameOver = true;
        }
        for (auto &food : board.getFoods()) {
            if (snake.getHeadPosition() == food->getPosition()) {
                food->applyEffect();
                board.removeFood(food);
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