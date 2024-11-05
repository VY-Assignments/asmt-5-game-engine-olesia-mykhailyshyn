#pragma once
#include <SFML/Graphics.hpp>

int ShowWelcome(sf::RenderWindow& window);
void ShowScoreboard(sf::RenderWindow& window, const std::string& playerName, int playerScore);
std::string EnterName(sf::RenderWindow& window);
void ShowGameOver(sf::RenderWindow& window);