#pragma once
#include <SFML/Graphics.hpp>

enum class WeatherType {
    Clear,
    Rain
};

class Weather {
public:
    Weather();
    void Update();
    [[nodiscard]] WeatherType GetCurrentWeather() const;
    void Render(sf::RenderWindow& window);

private:
    WeatherType currentWeather;
    sf::Clock weatherChangeTimer;
    sf::Clock rainEffectTimer;
    sf::Time weatherDuration;
    std::vector<sf::RectangleShape> raindrops;

    void StartRain();
    void StopRain();
    void UpdateRain();
};