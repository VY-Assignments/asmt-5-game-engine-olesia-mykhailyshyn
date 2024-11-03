#pragma once
#include <SFML/Graphics.hpp>

enum class WeatherType {
    Clear,
    Rain
};

class Weather {
public:
    Weather();
    void update();
    [[nodiscard]] WeatherType getCurrentWeather() const;
    void render(sf::RenderWindow& window);

private:
    WeatherType currentWeather;
    sf::Clock weatherChangeTimer;
    sf::Clock rainEffectTimer;
    sf::Time weatherDuration;
    std::vector<sf::RectangleShape> raindrops;

    void startRain();
    void stopRain();
    void updateRain();
};