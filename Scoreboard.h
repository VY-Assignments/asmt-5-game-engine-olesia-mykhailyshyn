#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

struct ScoreEntry {
    std::string name;
    int score;

    bool operator<(const ScoreEntry& other) const;
};

class Scoreboard {
public:
    static Scoreboard& GetInstance() {
        static Scoreboard instance(R"(C:\KSE\OOP_design\Assignment_5_6\asmt-5-game-engine-olesia-mykhailyshyn\Scoreboard.txt)");
        return instance;
    }

    void LoadScores();
    void SaveScore(const std::string& name, int score);
    [[nodiscard]] std::vector<ScoreEntry> getTopScores(int n) const;
    [[nodiscard]] int GetRank(const std::string& name, int score) const;
    [[nodiscard]] int GetTotalPlayers() const;

    static std::ostream& PrintScoreEntry(std::ostream& os, const ScoreEntry& entry);
    static std::istream& ReadScoreEntry(std::istream& is, ScoreEntry& entry);

    explicit Scoreboard(const std::string& file);
    Scoreboard(const Scoreboard&) = delete; //not to copy
    Scoreboard& operator=(const Scoreboard&) = delete; //not to assign

private:
    std::string file;
    std::vector<ScoreEntry> scores;
};