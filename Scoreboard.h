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

    [[nodiscard]] std::vector<ScoreEntry> getTopScores(int n) const;
    [[nodiscard]] int getRank(const std::string& name, int score) const;
    [[nodiscard]] int getTotalPlayers() const;

private:
    std::string file;
    std::vector<ScoreEntry> scores;
};