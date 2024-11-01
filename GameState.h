#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Snake.h"
#include "Scoreboard.h"

class GameState {
private:
    Board board;
    Snake snake;
    Scoreboard scoreboard;
    bool isGameOver;

public:
    GameState(int width, int height, sf::RenderWindow &window, const std::string &scoreboardPath);
    void handleInput();
    void update();
    void draw();
    [[nodiscard]] bool gameOver() const;
};

enum class State { RUNNING, GAME_OVER };