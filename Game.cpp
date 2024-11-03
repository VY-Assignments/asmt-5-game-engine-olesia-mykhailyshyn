#include "Game.h"
#include "FoodFactory.h"
#include <iostream>

Game::Game(const std::string& playerName) : playerName(playerName) {
    gameOver = false;

    for (int i = 0; i < 3; ++i) {
        foods.push_back(FoodFactory::createFood(FoodType::Normal, R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\normal.png)"));
    }
    for (int i = 0; i < 4; ++i) {
        foods.push_back(FoodFactory::createFood(FoodType::Poisonous, R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\poisonous.png)"));
    }

    for (int i = 0; i < 5; ++i) {
        sf::CircleShape shadow(150);
        shadow.setFillColor(sf::Color(0, 0, 0, 200));
        shadow.setPosition(
                std::rand() % (1500 - static_cast<int>(shadow.getRadius()) * 2),
                std::rand() % (1000 - static_cast<int>(shadow.getRadius()) * 2)
        );
        shadows.push_back(shadow);
    }
}

void Game::run(sf::RenderWindow& window) {
    window.setFramerateLimit(8);

    while (window.isOpen() && !gameOver) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else {
                Command command = InputHandler::handleInput(event);
                handleCommand(command);
            }
        }

        weather.update();

        if (weather.getCurrentWeather() == WeatherType::Rain) {
            window.setFramerateLimit(12);
        } else {
            window.setFramerateLimit(8);
        }

        update();
        render(window);
    }

    Scoreboard::getInstance().saveScore(playerName, snake.getSize());
}


int Game::getFinalScore() const {
    return snake.getSize();
}

void Game::update() {
    snake.move();

    bool foodEaten = false;

    for (auto it = foods.begin(); it != foods.end();) {
        if (snake.getHeadPosition() == (*it)->getPosition()) {
            foodEaten = true;

            if (dynamic_cast<NormalFood*>(it->get())) {
                snake.growSnake();
                snake.setFirstFoodEaten();
            }
            else if (dynamic_cast<PoisonousFood*>(it->get())) {
                if (snake.getSize() > 1) {
                    snake.shrinkSnake();
                }
                else {
                    Scoreboard::getInstance().saveScore(playerName, snake.getSize());
                    gameOver = true;
                    return;
                }
            }
            it = foods.erase(it);
        } else {
            ++it;
        }
    }

    maintainFoodCount();

    if (foodRespawnTimer.getElapsedTime().asSeconds() > 5) {
        respawnAllFood();
        foodRespawnTimer.restart();
    }

    if (snake.checkCollision()) {
        Scoreboard::getInstance().saveScore(playerName, snake.getSize());
        gameOver = true;
    }

    if (snake.reachedMaxSize()) {
        Scoreboard::getInstance().saveScore(playerName, snake.getSize());
        std::cout << "Congratulations! You reached the maximum size!" << std::endl;
        gameOver = true;
    }

    updateShadows();
}

void Game::maintainFoodCount() {
    int normalFoodCount = 0;
    int poisonousFoodCount = 0;

    for (const auto& food : foods) {
        if (dynamic_cast<NormalFood*>(food.get())) {
            ++normalFoodCount;
        } else if (dynamic_cast<PoisonousFood*>(food.get())) {
            ++poisonousFoodCount;
        }
    }

    while (normalFoodCount < 3) {
        foods.push_back(FoodFactory::createFood(FoodType::Normal, R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\normal.png)"));
        ++normalFoodCount;
    }
    while (poisonousFoodCount < 4) {
        foods.push_back(FoodFactory::createFood(FoodType::Poisonous, R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\poisonous.png)"));
        ++poisonousFoodCount;
    }
}

void Game::respawnAllFood() {
    for (auto& food : foods) {
        food->respawn();
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear(sf::Color(20, 20, 50));
    drawGrid(window);
    snake.draw(window);

    for (const auto& food : foods) {
        food->draw(window);
    }

    drawShadows(window);
    weather.render(window);
    window.display();
}

void Game::handleCommand(Command command) {
    switch (command) {
        case Command::MoveUp:
            snake.changeDirection(Up);
            break;
        case Command::MoveDown:
            snake.changeDirection(Down);
            break;
        case Command::MoveLeft:
            snake.changeDirection(Left);
            break;
        case Command::MoveRight:
            snake.changeDirection(Right);
            break;
        case Command::Confirm:
            gameOver = true;
            break;
        default:
            break;
    }
}

void Game::drawGrid(sf::RenderWindow& window) {
    const int WIDTH = 1500;
    const int HEIGHT = 1000;
    const int SIZE = 50;  // Increased cell size

    for (int x = 0; x < WIDTH; x += SIZE) {
        for (int y = 0; y < HEIGHT; y += SIZE) {
            sf::RectangleShape cell(sf::Vector2f(SIZE, SIZE));
            cell.setPosition(x, y);
            cell.setFillColor(sf::Color::Transparent);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(75, 0, 130));
            window.draw(cell);
        }
    }
}


void Game::updateShadows() {
    if (shadowTimer.getElapsedTime() >= shadowUpdateInterval) {
        for (auto& shadow : shadows) {
            float newSize = static_cast<float>((std::rand() % 200) + 100);
            shadow.setRadius(newSize);

            shadow.setPosition(
                    std::rand() % (1500 - static_cast<int>(shadow.getRadius()) * 2),
                    std::rand() % (1000 - static_cast<int>(shadow.getRadius()) * 2)
            );

            int opacity = (std::rand() % 100) + 150;
            shadow.setFillColor(sf::Color(0, 0, 0, opacity));
        }
        shadowTimer.restart();
    }
}

void Game::drawShadows(sf::RenderWindow& window) {
    for (const auto& shadow : shadows) {
        window.draw(shadow);
    }
}