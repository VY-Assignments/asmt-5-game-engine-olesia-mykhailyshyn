#pragma once
#include <SFML/Graphics.hpp>

int showWelcomeScreen(sf::RenderWindow& window);
void showScoreboard(sf::RenderWindow& window, const std::string& playerName, int playerScore);
std::string enterPlayerName(sf::RenderWindow& window);
void showGameOverScreen(sf::RenderWindow& window);