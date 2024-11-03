#include "Game.h"
#include "FoodFactory.h"
#include <iostream>

Game::Game(const std::string& playerName) : playerName(playerName) {
    gameOver = false;

    // Ініціалізуємо початкову їжу за допомогою фабрики
    foods.push_back(FoodFactory::createFood(FoodType::Normal, "C:\\KSE\\OOP_design\\Assignment_5_6\\asmt-5-game-engine-olesia-mykhailyshyn\\normal.png"));
    foods.push_back(FoodFactory::createFood(FoodType::Poisonous, "C:\\KSE\\OOP_design\\Assignment_5_6\\asmt-5-game-engine-olesia-mykhailyshyn\\poisonous.png"));

    // Ініціалізація тіней
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
    window.setFramerateLimit(10);

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

    // Перевірка зіткнення з кожною їжею
    for (auto it = foods.begin(); it != foods.end();) {
        if (snake.getHeadPosition() == (*it)->getPosition()) {
            foodEaten = true;

            if (dynamic_cast<NormalFood*>(it->get())) {
                snake.growSnake();
                snake.setFirstFoodEaten();
            } else {
                if (snake.getSize() > 1) {
                    snake.shrinkSnake();
                } else {
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

    if (foodEaten) {
        foods.push_back(FoodFactory::createFood(FoodType::Normal, "C:\\KSE\\OOP_design\\Assignment_5_6\\asmt-5-game-engine-olesia-mykhailyshyn\\normal.png"));
        foods.push_back(FoodFactory::createFood(FoodType::Poisonous, "C:\\KSE\\OOP_design\\Assignment_5_6\\asmt-5-game-engine-olesia-mykhailyshyn\\poisonous.png"));
    }

    if (foodSpawnTimer.getElapsedTime() >= foodSpawnInterval) {
        foods.push_back(FoodFactory::createFood(FoodType::Normal, "C:\\KSE\\OOP_design\\Assignment_5_6\\asmt-5-game-engine-olesia-mykhailyshyn\\normal.png"));
        foodSpawnTimer.restart();
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
    updateFood();
}

void Game::updateFood() {
    for (auto& food : foods) {
        if (auto* movingFood = dynamic_cast<MovingFood*>(food.get())) {
            movingFood->move();
        }

        if (auto* timedFood = dynamic_cast<TimedFood*>(food.get())) {
            if (timedFood->shouldDespawn()) {
                food.reset();
            }
        }
    }
    foods.erase(std::remove(foods.begin(), foods.end(), nullptr), foods.end());
}

void Game::render(sf::RenderWindow& window) {
    window.clear(sf::Color(20, 20, 50));
    drawGrid(window);
    snake.draw(window);

    for (const auto& food : foods) {
        food->draw(window);
    }

    drawShadows(window);
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
    const int SIZE = 50;

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
            shadow.setPosition(
                    std::rand() % (1500 - static_cast<int>(shadow.getRadius()) * 2),
                    std::rand() % (1000 - static_cast<int>(shadow.getRadius()) * 2)
            );
        }
        shadowTimer.restart();
    }
}

void Game::drawShadows(sf::RenderWindow& window) {
    for (const auto& shadow : shadows) {
        window.draw(shadow);
    }
}
