#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

class GameRenderer {
public:
    explicit GameRenderer(Game& game);

    void Render(sf::RenderWindow& window);
    static void DrawGrid(sf::RenderWindow& window);
    void DrawShadows(sf::RenderWindow& window);

private:
    Game& game;
};