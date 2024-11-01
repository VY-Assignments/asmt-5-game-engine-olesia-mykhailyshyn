#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Snake Game");
    Game game(window);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (clock.getElapsedTime().asSeconds() > 0.1f) {
            game.handleInput();
            game.run();
            clock.restart();
        }

        window.clear();
        game.draw();
        window.display();
    }

    return 0;
}