#include "Scoreboard.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

Scoreboard::Scoreboard(const std::string& file) : file(file) {}

void Scoreboard::LoadScores() {
    scores.clear();
    std::ifstream fileStream(file);
    if (!fileStream.is_open()) {
        std::cout << "Error: Could not open score file for reading.\n";
        return;
    }

    ScoreEntry entry;
    std::string line;
    while (std::getline(fileStream, line)) {
        std::istringstream lineStream(line);
        ReadScoreEntry(lineStream, entry);
        scores.push_back(entry);
    }
    fileStream.close();

    std::sort(scores.begin(), scores.end());
}

void Scoreboard::SaveScore(const std::string& name, int score) {
    LoadScores();
    scores.push_back({ name, score });
    std::sort(scores.begin(), scores.end());

    std::ofstream fileStream(file);
    if (!fileStream.is_open()) {
        std::cout << "Error: Could not open score file for writing.\n";
        return;
    }

    for (const auto& entry : scores) {
        PrintScoreEntry(fileStream, entry) << "\n";
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

int Scoreboard::GetRank(const std::string& name, int score) const {
    for (size_t i = 0; i < scores.size(); ++i) {
        if (scores[i].name == name && scores[i].score == score) {
            return i + 1;
        }
    }
    return -1;
}

int Scoreboard::GetTotalPlayers() const {
    return scores.size();
}

bool ScoreEntry::operator<(const ScoreEntry& other) const {
    return score > other.score;
}

std::ostream& Scoreboard::PrintScoreEntry(std::ostream& os, const ScoreEntry& entry) {
    os << entry.name << "-" << entry.score;
    return os;
}

std::istream& Scoreboard::ReadScoreEntry(std::istream& is, ScoreEntry& entry) {
    std::getline(is, entry.name, '-');
    is >> entry.score;
    return is;
}