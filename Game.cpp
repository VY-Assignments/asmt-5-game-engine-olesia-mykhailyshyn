#include "Game.h"
#include "GameRenderer.h"
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

void Game::Run(sf::RenderWindow& window) {
    GameRenderer renderer(*this);
    window.setFramerateLimit(7);

    while (window.isOpen() && !gameOver) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else {
                Command command = InputHandler::HandleInput(event);
                HandleCommand(command);
            }
        }

        weather.Update();

        if (weather.GetCurrentWeather() == WeatherType::Rain) {
            window.setFramerateLimit(12);
        }
        else {
            window.setFramerateLimit(7);
        }

        Update();
        renderer.Render(window);
    }

    Scoreboard::GetInstance().SaveScore(playerName, snake.GetSize());
}

int Game::GetFinalScore() const {
    return snake.GetSize();
}

void Game::Update() {
    snake.Move();

    for (auto it = foods.begin(); it != foods.end();) {
        if (snake.GetHead() == (*it)->GetPosition()) {

            if (dynamic_cast<NormalFood*>(it->get())) {
                snake.Grow();
            }
            else if (dynamic_cast<PoisonousFood*>(it->get())) {
                if (snake.GetSize() > 1) {
                    snake.Shrink();
                }
                else {
                    Scoreboard::GetInstance().SaveScore(playerName, snake.GetSize());
                    gameOver = true;
                    return;
                }
            }
            it = foods.erase(it);
        }
        else {
            ++it;
        }
    }

    FoodCount();

    if (foodRespawnTimer.getElapsedTime().asSeconds() > 5) {
        RelocateFood();
        foodRespawnTimer.restart();
    }

    if (snake.Collision()) {
        Scoreboard::GetInstance().SaveScore(playerName, snake.GetSize());
        gameOver = true;
    }

    if (snake.MaxSize()) {
        Scoreboard::GetInstance().SaveScore(playerName, snake.GetSize());
        std::cout << "Congratulations! You reached the maximum size!" << std::endl;
        gameOver = true;
    }

    UpdateShadows();
}

void Game::FoodCount() {
    int normalFoodCount = 0;
    int poisonousFoodCount = 0;

    for (const auto& food : foods) {
        if (dynamic_cast<NormalFood*>(food.get())) {
            ++normalFoodCount;
        }
        else if (dynamic_cast<PoisonousFood*>(food.get())) {
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

void Game::RelocateFood() {
    for (auto& food : foods) {
        food->Relocate();
    }
}

void Game::HandleCommand(Command command) {
    switch (command) {
        case Command::MoveUp: {
            snake.ChangeDirection(Up);
            break;
        }
        case Command::MoveDown: {
            snake.ChangeDirection(Down);
            break;
        }
        case Command::MoveLeft: {
            snake.ChangeDirection(Left);
            break;
        }
        case Command::MoveRight: {
            snake.ChangeDirection(Right);
            break;
        }
        case Command::Confirm: {
            gameOver = true;
            break;
        }
        default:
            break;
    }
}

void Game::UpdateShadows() {
    if (shadowTimer.getElapsedTime() >= shadowUpdateInterval) {
        for (auto& shadow : shadows) {
            auto newSize = static_cast<float>((std::rand() % 200) + 100);
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