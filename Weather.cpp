#include "Weather.h"
#include <cstdlib>

Weather::Weather() : currentWeather(WeatherType::Clear), weatherDuration(sf::seconds(5)) {}

void Weather::update() {
    if (weatherChangeTimer.getElapsedTime() > weatherDuration) {
        if (currentWeather == WeatherType::Clear) {
            startRain();
        } else {
            stopRain();
        }
        weatherChangeTimer.restart();
    }

    if (currentWeather == WeatherType::Rain) {
        updateRain();
    }
}

WeatherType Weather::getCurrentWeather() const {
    return currentWeather;
}

void Weather::render(sf::RenderWindow& window) {
    if (currentWeather == WeatherType::Rain) {
        for (auto& drop : raindrops) {
            window.draw(drop);
        }
    }
}

void Weather::startRain() {
    currentWeather = WeatherType::Rain;
    raindrops.clear();
    for (int i = 0; i < 50; ++i) {
        sf::RectangleShape drop(sf::Vector2f(2, 10));
        drop.setPosition(std::rand() % 1500, std::rand() % 1000);
        drop.setFillColor(sf::Color(150, 150, 255, 150));
        raindrops.push_back(drop);
    }
}

void Weather::stopRain() {
    currentWeather = WeatherType::Clear;
    raindrops.clear();
}

void Weather::updateRain() {
    for (auto& drop : raindrops) {
        drop.move(0, 5);
        if (drop.getPosition().y > 1000) {
            drop.setPosition(std::rand() % 1500, 0);
        }
    }
}