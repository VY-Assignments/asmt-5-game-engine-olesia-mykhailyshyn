#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

struct ScoreEntry {
    std::string name;
    int score;

    bool operator<(const ScoreEntry& other) const;
    friend std::ostream& operator<<(std::ostream& os, const ScoreEntry& entry);
    friend std::istream& operator>>(std::istream& is, ScoreEntry& entry);
};

class Scoreboard {
public:
    explicit Scoreboard(const std::string& file);
    void loadScores();
    void saveScore(const std::string& name, int score);
    void display(sf::RenderWindow& window, const std::string& playerName, int playerScore);

private:
    std::string file;
    std::vector<ScoreEntry> scores;
};
