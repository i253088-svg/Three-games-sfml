#include "LeaderboardManager.h"
LeaderboardManager::LeaderboardManager() {
    count = 0;
    filename = "leaderboard.txt";
    LoadFromFile();
}
void LeaderboardManager::AddRecord(const char* playerName, const char* gameName, int score, int wins) {
    if (count >= 200) return;
    int i = 0;
    while (playerName[i] != '\0' && i < 49) {
        entries[count].playerName[i] = playerName[i];
        i++; 
    }
    entries[count].playerName[i] = '\0';
    i = 0;
    while (gameName[i] != '\0' && i < 49) { 
        entries[count].gameName[i] = gameName[i]; i++; 
    }
    entries[count].gameName[i] = '\0';
    entries[count].score = score;
    entries[count].wins = wins;
    count++;
    SortRecords();
    SaveToFile();
}
void LeaderboardManager::LoadFromFile() {
    count = 0;
    ifstream inFile(filename);
    if (!inFile.is_open()) return;
    while (count < 200 && inFile >> entries[count].playerName >> entries[count].gameName >> entries[count].score >> entries[count].wins)
        count++;
    inFile.close();
    SortRecords();
}
void LeaderboardManager::SaveToFile() {
    ofstream outFile(filename);
    if (!outFile.is_open()) return;
    for (int i = 0; i < count; i++)
        outFile << entries[i].playerName << " " << entries[i].gameName << " " << entries[i].score << " " << entries[i].wins << "\n";
    outFile.close();
}
void LeaderboardManager::SortRecords() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (entries[j].score < entries[j + 1].score) {
                LeaderboardEntry tmp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = tmp;
            }
        }
    }
}
void LeaderboardManager::DisplayLeaderboard(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape overlay(sf::Vector2f(600.f, 850.f));
    overlay.setFillColor(sf::Color(114, 98, 209, 245));
    window.draw(overlay);
    sf::Text title("LEADERBOARD", font, 48);
    title.setOrigin(title.getLocalBounds().width / 2.0f, 0);
    title.setPosition(300.f, 40.f);
    title.setFillColor(sf::Color::White);
    window.draw(title);
    sf::RectangleShape line(sf::Vector2f(540.f, 2.f));
    line.setPosition(30.f, 110.f);
    line.setFillColor(sf::Color(255, 255, 255, 120));
    window.draw(line);
    sf::Text hdr("Player          Game         Score  Wins", font, 18);
    hdr.setPosition(30.f, 120.f);
    hdr.setFillColor(sf::Color(220, 220, 255));
    window.draw(hdr);
    sf::RectangleShape line2(sf::Vector2f(540.f, 2.f));
    line2.setPosition(30.f, 148.f);
    line2.setFillColor(sf::Color(255, 255, 255, 80));
    window.draw(line2);
    int show = count < 10 ? count : 10;
    for (int i = 0; i < show; i++) {
        char row[100];
        int ri = 0;
        for (int k = 0; entries[i].playerName[k] && ri < 15; k++, ri++) row[ri] = entries[i].playerName[k];
        while (ri < 15) row[ri++] = ' ';
        for (int k = 0; entries[i].gameName[k] && ri < 28; k++, ri++) row[ri] = entries[i].gameName[k];
        while (ri < 28) row[ri++] = ' ';
        int s = entries[i].score < 0 ? 0 : entries[i].score;
        row[ri++] = (s / 100) % 10 + '0';
        row[ri++] = (s / 10) % 10 + '0';
        row[ri++] = s % 10 + '0';
        row[ri++] = ' '; row[ri++] = ' '; row[ri++] = ' '; row[ri++] = ' ';
        int w = entries[i].wins < 0 ? 0 : entries[i].wins;
        row[ri++] = (w / 10) % 10 + '0';
        row[ri++] = w % 10 + '0';
        row[ri] = '\0';
        sf::RectangleShape rowbg(sf::Vector2f(540.f, 48.f));
        rowbg.setPosition(30.f, 158.f + i * 52.f);
        rowbg.setFillColor(i % 2 == 0 ? sf::Color(255, 255, 255, 20) : sf::Color(0, 0, 0, 20));
        window.draw(rowbg);
        sf::Text rowTxt(row, font, 18);
        rowTxt.setPosition(36.f, 166.f + i * 52.f);
        rowTxt.setFillColor(sf::Color::White);
        window.draw(rowTxt);
    }
    if (count == 0) {
        sf::Text empty("No records yet!", font, 28);
        empty.setOrigin(empty.getLocalBounds().width / 2.0f, 0);
        empty.setPosition(300.f, 420.f);
        empty.setFillColor(sf::Color(200, 200, 255));
        window.draw(empty);
    }
    sf::RectangleShape backBtn(sf::Vector2f(300.f, 50.f));
    backBtn.setPosition(150.f, 770.f);
    backBtn.setFillColor(sf::Color(255, 255, 255, 50));
    backBtn.setOutlineThickness(1);
    backBtn.setOutlineColor(sf::Color::White);
    window.draw(backBtn);
    sf::Text backTxt("Back to Menu", font, 28);
    backTxt.setOrigin(backTxt.getLocalBounds().width / 2.0f, 0);
    backTxt.setPosition(300.f, 778.f);
    window.draw(backTxt);
}
int LeaderboardManager::getCount() { return count; }
LeaderboardEntry LeaderboardManager::getEntry(int i) { return entries[i]; }