#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <fstream>
#include "LeaderboardManager.h"
using namespace std;
class Tictactoe {
private:
    int** board;
    int playerturn;
    int gamestate;
    int scoreX = 0;
    int scoreO = 0;
public:
    Tictactoe();
    ~Tictactoe();
    void savescores();
    void resetboard();
    void resetscores();
    int getcell(int r, int c);
    int getgamestate();
    int getplayerturn();
    int getscoreX();
    int getscoreO();
    bool checkwin(int p);
    bool isfull();
    void makemove(int row, int col, sf::Sound& moveSound);
};
class SaanpGame {
private:
    sf::Vector2i body1[500];
    int len1;
    int dir1;
    sf::Vector2i body2[500];
    int len2;
    int dir2;
    sf::Vector2i food;
    float timer, speed;
    bool dead1, dead2;
    int score1, score2;
    int nextdir1, nextdir2;
public:
    SaanpGame();
    void savehighscore(int score);
    void shuru();
    void spawnfood();
    void handleinput();
    void update(float dt, sf::Sound& eatSound);
    void draw(sf::RenderWindow& window, sf::Font& font);
    bool iskhatam();
    int getwinner();
    int getscore1();
    int getscore2();
};
class PingPongGame {
private:
    sf::Vector2f ball, ballVel;
    float p1Y, p2Y;
    int scoreleft, scoreright;
    float paddlespeed = 450.f;
    float ballspeed = 220.f;
    int totalwinsleft = 0;
    int totalwinsright = 0;
    const float pwidth = 15.f, pheight = 100.f;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    bool hasBg = false;
    bool isgameover = false;
    int winner = 0;
public:
    PingPongGame();
    void loadscores();
    void savescores();
    void shuru();
    void resetfull();
    void update(float dt, sf::Sound& hitSound);
    void draw(sf::RenderWindow& window, sf::Font& font);
    bool getisgameover();
    int getwinner();
    int getscoreleft();
    int getscoreright();
};
void getNameInput(sf::RenderWindow& window, sf::Font& font, char* nameOut, int maxLen, const char* prompt, sf::Color bgColor);