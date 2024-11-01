#include "Game.h"
#include "Input.h"
#include <cstdlib>
#include <memory>
#include <iostream>

Game::Game(sf::RenderWindow& windowRef)
        : board(40, 40, windowRef),
          snake(20, 20),
          state(State::RUNNING),
          normalFood(std::make_unique<NormalFood>()),
          poisonousFood(std::make_unique<PoisonousFood>()),
          scoreboard("scoreboard.txt")
{
    createNewFood();
}

void Game::run() {
    if (state == State::GAME_OVER) {
        saveScore();
        return;
    }
    handleInput();
    snake.move();

    if (snake.getHeadPosition() == normalFood->getPosition()) {
        snake.applyFoodEffect(*normalFood);
        createNewFood();
    } else if (snake.getHeadPosition() == poisonousFood->getPosition()) {
        snake.applyFoodEffect(*poisonousFood);
        createNewFood();
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
    Input input = InputHandler::getInput();
    switch (input) {
        case Input::Up:
            snake.setDirection(Snake::Direction::Up);
            break;
        case Input::Down:
            snake.setDirection(Snake::Direction::Down);
            break;
        case Input::Left:
            snake.setDirection(Snake::Direction::Left);
            break;
        case Input::Right:
            snake.setDirection(Snake::Direction::Right);
            break;
        case Input::Exit:
            state = State::GAME_OVER;
            break;
        default:
            break;
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