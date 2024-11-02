#include "Game.h"
#include "Input.h"
#include <cstdlib>
#include <memory>
#include <iostream>

Game::Game(sf::RenderWindow& window)
        : board(40, 40, window),
          snake("C:/KSE/OOP_design/Assignment_5_6/asmt-5-game-engine-olesia-mykhailyshyn/Head.png",
                "C:/KSE/OOP_design/Assignment_5_6/asmt-5-game-engine-olesia-mykhailyshyn/BodyBlock.png"),
          state(State::RUNNING),
          normalFood(std::make_unique<NormalFood>()),
          poisonousFood(std::make_unique<PoisonousFood>()),
          scoreboard("scoreboard.txt")
{
    createNewFood();
}

void Game::run() {
    if (state == State::GAME_OVER) {
        scoreboard.save();
        return;
    }

    handleInput();
    snake.move();

    // Check food interactions
    if (snake.getHeadPosition() == normalFood->getPosition()) {
        snake.grow();
        createNewFood();
    } else if (snake.getHeadPosition() == poisonousFood->getPosition()) {
        if (snake.getSize() > 1) {
            snake.shrink();
            createNewFood();
        } else {
            state = State::GAME_OVER;
        }
    }

    if (snake.hasCollidedWithItself()) {
        state = State::GAME_OVER;
    }
}


void Game::createNewFood() {
    normalFood->setPosition(rand() % board.getWidth(), rand() % board.getHeight());
    poisonousFood->setPosition(rand() % board.getWidth(), rand() % board.getHeight());
}

void Game::handleInput() {
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

void Game::saveScore() {
    scoreboard.addPlayer({"Player", snake.getScore()});
    if (!scoreboard.save()) {
        std::cout << "Score saving failed." << std::endl;
    }
}


void Game::draw() {
    board.clear();
    board.draw();
    snake.draw(board.getWindow());
    normalFood->draw(board.getWindow());
    poisonousFood->draw(board.getWindow());
}
