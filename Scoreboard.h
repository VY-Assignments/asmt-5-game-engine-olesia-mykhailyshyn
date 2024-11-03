#pragma once
#include <string>
#include <vector>
#include <iostream>
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
    static Scoreboard& getInstance() {
        static Scoreboard instance(R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\Scoreboard.txt)");
        return instance;
    }

    void loadScores();
    void saveScore(const std::string& name, int score);
    [[nodiscard]] std::vector<ScoreEntry> getTopScores(int n) const;
    [[nodiscard]] int getRank(const std::string& name, int score) const;
    [[nodiscard]] int getTotalPlayers() const;
    explicit Scoreboard(const std::string& file);
    Scoreboard(const Scoreboard&) = delete;

private:
    Scoreboard& operator=(const Scoreboard&) = delete;

    std::string file;
    std::vector<ScoreEntry> scores;
};