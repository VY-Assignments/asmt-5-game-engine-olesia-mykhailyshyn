#include "Point.h"
#include <SFML/Graphics.hpp>

class Player {
public:
    std::string name;
    int score;

    Player(std::string name, int score) : name(std::move(name)), score(score) {}
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
    void manageScoreboard();
};