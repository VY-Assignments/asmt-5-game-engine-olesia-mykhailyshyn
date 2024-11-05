#include "Weather.h"
#include <cstdlib>

Weather::Weather() : currentWeather(WeatherType::Clear), weatherDuration(sf::seconds(5)) {}

void Weather::Update() {
    if (weatherChangeTimer.getElapsedTime() > weatherDuration) {
        if (currentWeather == WeatherType::Clear) {
            StartRain();
        }
        else {
            StopRain();
        }
        weatherChangeTimer.restart();
    }

    if (currentWeather == WeatherType::Rain) {
        UpdateRain();
    }
}

WeatherType Weather::GetCurrentWeather() const {
    return currentWeather;
}

void Weather::Render(sf::RenderWindow& window) {
    if (currentWeather == WeatherType::Rain) {
        for (auto& drop : raindrops) {
            window.draw(drop);
        }
    }
}

void Weather::StartRain() {
    currentWeather = WeatherType::Rain;
    raindrops.clear();
    for (int i = 0; i < 50; ++i) {
        sf::RectangleShape drop(sf::Vector2f(2, 10));
        drop.setPosition(std::rand() % 1500, std::rand() % 1000);
        drop.setFillColor(sf::Color(150, 150, 255, 150));
        raindrops.push_back(drop);
    }
}

void Weather::StopRain() {
    currentWeather = WeatherType::Clear;
    raindrops.clear();
}

void Weather::UpdateRain() {
    for (auto& drop : raindrops) {
        drop.move(0, 5);
        if (drop.getPosition().y > 1000) {
            drop.setPosition(std::rand() % 1500, 0);
        }
    }
}