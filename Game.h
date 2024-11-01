#pragma once
#include "Board.h"
#include "Snake.h"
#include "Food.h"
#include "Scoreboard.h"
#include "GameState.h"
#include <memory>

class Game {
private:
    Board board;
    Snake snake;
    std::unique_ptr<Food> normalFood;
    std::unique_ptr<Food> poisonousFood;
    Scoreboard scoreboard;
    State state;

public:
    explicit Game(sf::RenderWindow& windowRef);
    void run();
    void handleInput();
    void createNewFood();
    void saveScore();
    void draw();
};