#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Player {
public:
    std::string name;
    int score;

    Player(std::string name, int score) : name(std::move(name)), score(score) {}

    bool operator==(const Player &other) const {
        return name == other.name && score == other.score;
    }
};

class Scoreboard {
private:
    std::string filePath;
    std::vector<Player> players;

public:
    explicit Scoreboard(std::string path);
    bool load();
    [[nodiscard]] bool save() const;
    void addPlayer(const Player &player);
    void display() const;
    [[nodiscard]] const std::vector<Player>& getScores() const;  
};
