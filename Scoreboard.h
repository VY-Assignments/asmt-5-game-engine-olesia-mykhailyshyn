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

    std::vector<ScoreEntry> scores;
private:
    std::string file;
};