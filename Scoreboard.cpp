#include "Scoreboard.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

Scoreboard::Scoreboard(const std::string& file)
        : file(file) {}

void Scoreboard::loadScores() {
    scores.clear();
    std::ifstream fileStream(file);
    if (!fileStream.is_open()) {
        std::cerr << "Error: Could not open score file for reading.\n";
        return;
    }

    ScoreEntry entry;
    while (fileStream >> entry) {
        scores.push_back(entry);
    }
    fileStream.close();
    std::sort(scores.begin(), scores.end());
}

void Scoreboard::saveScore(const std::string& name, int score) {
    loadScores();
    scores.push_back({ name, score });
    std::sort(scores.begin(), scores.end());

    std::ofstream fileStream(file);
    for (const auto& entry : scores) {
        fileStream << entry.name << "-" << entry.score << "\n";
    }
    fileStream.close();
}

bool ScoreEntry::operator<(const ScoreEntry& other) const {
    return score > other.score;
}

std::ostream& operator<<(std::ostream& os, const ScoreEntry& entry) {
    os << entry.name << "-" << entry.score;
    return os;
}

std::istream& operator>>(std::istream& is, ScoreEntry& entry) {
    std::getline(is, entry.name, '-');
    is >> entry.score;
    return is;
}