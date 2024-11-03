#include "Scoreboard.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

Scoreboard::Scoreboard(const std::string& file) : file(file) {}

void Scoreboard::loadScores() {
    scores.clear();
    std::ifstream fileStream(file);
    if (!fileStream.is_open()) {
        std::cerr << "Error: Could not open score file for reading.\n";
        return;
    }

    ScoreEntry entry;
    std::string line;
    while (std::getline(fileStream, line)) {
        std::istringstream lineStream(line);
        std::getline(lineStream, entry.name, ','); // CSV delimiter
        lineStream >> entry.score;
        scores.push_back(entry);
    }
    fileStream.close();

    std::sort(scores.begin(), scores.end());  // Sort in descending order of score
}

int Scoreboard::getTotalPlayers() const {
    return scores.size();  // Total number of entries loaded
}

void Scoreboard::saveScore(const std::string& name, int score) {
    loadScores();
    scores.push_back({ name, score });

    // Sort the scores after adding the new entry
    std::sort(scores.begin(), scores.end());

    std::ofstream fileStream(file);
    if (!fileStream.is_open()) {
        std::cerr << "Error: Could not open score file for writing.\n";
        return;
    }

    // Save all scores in CSV format
    for (const auto& entry : scores) {
        fileStream << entry.name << "," << entry.score << "\n";
    }
    fileStream.close();
}

std::vector<ScoreEntry> Scoreboard::getTopScores(int n) const {
    std::vector<ScoreEntry> topScores;
    int limit = std::min(n, static_cast<int>(scores.size()));
    for (int i = 0; i < limit; i++) {
        topScores.push_back(scores[i]);
    }
    return topScores;
}

int Scoreboard::getRank(const std::string& name, int score) const {
    for (size_t i = 0; i < scores.size(); ++i) {
        if (scores[i].name == name && scores[i].score == score) {
            return i + 1;
        }
    }
    return -1;  // If not found
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