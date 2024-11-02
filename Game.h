#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.h"
#include "Snake.h"
#include "Food.h"
#include "Scoreboard.h"

class Game {
public:
    Game(sf::RenderWindow &window);
    void run();
    void handleInput();
    void draw();

    bool gameOver() const { return state == State::GAME_OVER; }
    int getScore() const { return snake.getScore(); }  // Updated to use snake's getScore

private:
    void createNewFood();
    void saveScore();  // Ensure this method is declared

    enum class State { RUNNING, GAME_OVER };
    State state;

    Board board;
    Snake snake;
    std::unique_ptr<NormalFood> normalFood;
    std::unique_ptr<PoisonousFood> poisonousFood;
    Scoreboard scoreboard;
};
