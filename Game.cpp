#include "Game.h"
#include "Input.h"
#include <cstdlib>
#include <memory>

Game::Game(sf::RenderWindow& windowRef)
        : board(40, 40, windowRef),
          snake(20, 20),
          state(State::RUNNING),
          food(new NormalFood),
          scoreboard("scoreboard.txt")
{
    createNewFood();
}

void Game::run() {
    handleInput();
    snake.move();

    if (snake.getHeadPosition() == food->getPosition()) {
        snake.applyFoodEffect(*food);
        createNewFood();
    }

    if (snake.hasCollidedWithWall(board) || snake.hasCollidedWithItself()) {
        state = State::GAME_OVER;
    }
}

void Game::createNewFood() {
    if (rand() % 2 == 0) {
        food = std::make_unique<NormalFood>();
    }
    else {
        food = std::make_unique<PoisonousFood>();
    }
    food->setPosition(rand() % board.getWidth(), rand() % board.getHeight());
}

void Game::handleInput() {
    Input input = InputHandler::getInput();
    switch (input) {
        case Input::Up: {
            snake.setDirection(Snake::Direction::Up); break;
        }
        case Input::Down: {
            snake.setDirection(Snake::Direction::Down); break;
        }
        case Input::Left: {
            snake.setDirection(Snake::Direction::Left); break;
        }
        case Input::Right: {
            snake.setDirection(Snake::Direction::Right); break;
        }
        default: break;
    }
}

void Game::saveScore() {
    scoreboard.addPlayer({"Player", snake.getScore()});
    scoreboard.save();
}

void Game::draw() {
    board.clear();
    board.draw();
    snake.draw(board.getWindow());
    food->draw(board.getWindow());
}