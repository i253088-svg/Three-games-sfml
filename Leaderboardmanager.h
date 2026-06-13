#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std;

struct LeaderboardEntry {
    char playerName[50];
    char gameName[50];
    int score;
    int wins;
};
class LeaderboardManager {
private:
    LeaderboardEntry entries[200];
    int count;
    const char* filename;
public:
    LeaderboardManager();
    void AddRecord(const char* playerName, const char* gameName, int score, int wins);
    void LoadFromFile();
    void SaveToFile();
    void SortRecords();
    void DisplayLeaderboard(sf::RenderWindow& window, sf::Font& font);
    int getCount();
    LeaderboardEntry getEntry(int i);
};