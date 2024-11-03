#pragma once
#include <SFML/Graphics.hpp>

int showWelcomeScreen(sf::RenderWindow& window);
void showScoreboard(sf::RenderWindow& window);
std::string enterPlayerName(sf::RenderWindow& window);
void showGameOverScreen(sf::RenderWindow& window);