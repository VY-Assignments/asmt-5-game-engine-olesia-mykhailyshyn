#include "Scoreboard.h"
#include <iostream>
#include <fstream>
#include <sstream>

Scoreboard::Scoreboard(std::string path) : filePath(std::move(path)) {}

bool Scoreboard::load() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filePath << std::endl;
        return false;
    }

    players.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        if (!(iss >> name >> score)) {
            std::cerr << "Invalid data format in file." << std::endl;
            players.clear();
            return false;
        }
        players.emplace_back(name, score);
    }

    file.close();
    return true;
}

bool Scoreboard::save() const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filePath << std::endl;
        return false;
    }

    for (const auto &player : players) {
        file << player.name << " " << player.score << "\n";
    }

    file.close();
    return true;
}

void Scoreboard::addPlayer(const Player &player) {
    players.push_back(player);
}

void Scoreboard::display() const {
    std::cout << "--- Player Rankings ---" << std::endl;
    for (const auto &player : players) {
        std::cout << "Name: " << player.name << ", Score: " << player.score << std::endl;
    }
}

const std::vector<Player>& Scoreboard::getScores() const {
    return players;
}
