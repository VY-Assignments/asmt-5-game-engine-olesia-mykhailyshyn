#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

class GameRenderer {
public:
    explicit GameRenderer(Game& game);

    void render(sf::RenderWindow& window);
    void drawGrid(sf::RenderWindow& window);
    void drawShadows(sf::RenderWindow& window);

private:
    Game& game;
};