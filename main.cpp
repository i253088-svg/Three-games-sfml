#include "GameHub.h"
Tictactoe::Tictactoe() {
    board = new int* [3];
    for (int i = 0; i < 3; i++) {
        board[i] = new int[3];
    }
    resetboard();
}
Tictactoe::~Tictactoe() {
    for (int i = 0; i < 3; i++) {
        delete[] board[i];
    }
    delete[] board;
}
void Tictactoe::savescores() {
    ofstream outFile("ttt_scores.txt");
    if (outFile.is_open()) {
        outFile << "Score Stats:" << endl;
        outFile << "Player X: " << scoreX << endl;
        outFile << "Player O: " << scoreO << endl;
        outFile.close();
    }
}
void Tictactoe::resetboard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
    playerturn = 1;
    gamestate = 0;
}
void Tictactoe::resetscores() {
    scoreX = 0;
    scoreO = 0;
}
int Tictactoe::getcell(int r, int c) {
    return board[r][c];
}
int Tictactoe::getgamestate() {
    return gamestate;
}
int Tictactoe::getplayerturn() {
    return playerturn;
}
int Tictactoe::getscoreX() {
    return scoreX;
}
int Tictactoe::getscoreO() {
    return scoreO;
}
bool Tictactoe::checkwin(int p) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p) {
            return true;
        }
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p) {
            return true;
        }
    }
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p) {
        return true;
    }
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p) {
        return true;
    }
    return false;
}
bool Tictactoe::isfull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}
void Tictactoe::makemove(int row, int col, sf::Sound& moveSound) {
    if (gamestate == 0 && board[row][col] == 0) {
        board[row][col] = playerturn;
        moveSound.play();
        if (checkwin(playerturn)) {
            gamestate = playerturn;
            if (playerturn == 1) {
                scoreX++;
            }
            else {
                scoreO++;
            }
            savescores();
        }
        else if (isfull()) {
            gamestate = 3;
        }
        else {
            playerturn = (playerturn == 1) ? 2 : 1;
        }
    }
}
SaanpGame::SaanpGame() {
    shuru();
}
void SaanpGame::savehighscore(int score) {
    int currenthigh = 0;
    ifstream inFile("snake_highscore.txt");
    if (inFile >> currenthigh);
    inFile.close();
    if (score > currenthigh) {
        ofstream outFile("snake_highscore.txt");
        if (outFile.is_open()) {
            outFile << score;
            outFile.close();
        }
    }
}
void SaanpGame::shuru() {
    len1 = 4;
    for (int i = 0; i < len1; i++) {
        body1[i] = sf::Vector2i(5 - i, 10);
    }
    dir1 = 1; nextdir1 = 1;
    len2 = 4;
    for (int i = 0; i < len2; i++) {
        body2[i] = sf::Vector2i(24 + i, 20);
    }
    dir2 = 3; nextdir2 = 3;
    spawnfood();
    timer = 0; speed = 0.12f;
    dead1 = false; dead2 = false;
    score1 = 0; score2 = 0;
}
void SaanpGame::spawnfood() {
    bool onsnake = true;
    while (onsnake) {
        food.x = rand() % 30;
        food.y = rand() % 30;
        onsnake = false;
        for (int i = 0; i < len1; i++) {
            if (body1[i] == food) {
                onsnake = true;
                break;
            }
        }
        if (!onsnake) {
            for (int i = 0; i < len2; i++) {
                if (body2[i] == food) {
                    onsnake = true;
                    break;
                }
            }
        }
    }
}
void SaanpGame::handleinput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && dir1 != 2) { nextdir1 = 0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && dir1 != 3) { nextdir1 = 1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && dir1 != 0) { nextdir1 = 2; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dir1 != 1) { nextdir1 = 3; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir2 != 2) { nextdir2 = 0; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir2 != 3) { nextdir2 = 1; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dir2 != 0) { nextdir2 = 2; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir2 != 1) { nextdir2 = 3; }
}
void SaanpGame::update(float dt, sf::Sound& eatSound) {
    if (dead1 || dead2) {
        return;
    }

    timer += dt;
    if (timer < speed) {
        return;
    }
    timer = 0;
    dir1 = nextdir1;
    dir2 = nextdir2;
    for (int i = len1 - 1; i > 0; i--) {
        body1[i] = body1[i - 1];
    }
    if (dir1 == 0) body1[0].y--;
    else if (dir1 == 1) body1[0].x++;
    else if (dir1 == 2) body1[0].y++;
    else if (dir1 == 3) body1[0].x--;
    if (body1[0].x < 0) body1[0].x = 29;
    if (body1[0].x >= 30) body1[0].x = 0;
    if (body1[0].y < 0) body1[0].y = 29;
    if (body1[0].y >= 30) body1[0].y = 0;
    for (int i = len2 - 1; i > 0; i--) {
        body2[i] = body2[i - 1];
    }
    if (dir2 == 0) body2[0].y--;
    else if (dir2 == 1) body2[0].x++;
    else if (dir2 == 2) body2[0].y++;
    else if (dir2 == 3) body2[0].x--;
    if (body2[0].x < 0) body2[0].x = 29;
    if (body2[0].x >= 30) body2[0].x = 0;
    if (body2[0].y < 0) body2[0].y = 29;
    if (body2[0].y >= 30) body2[0].y = 0;
    if (body1[0] == food) {
        if (len1 < 500) len1++;
        score1++;
        eatSound.play();
        spawnfood();
    }
    if (body2[0] == food) {
        if (len2 < 500) len2++;
        score2++;
        eatSound.play();
        spawnfood();
    }
    if (body1[0] == body2[0]) {
        dead1 = true;
        dead2 = true;
    }
    if (!dead1) {
        for (int i = 1; i < len1; i++) {
            if (body1[0] == body1[i]) { dead1 = true; break; }
        }
        for (int i = 0; i < len2; i++) {
            if (body1[0] == body2[i]) { dead1 = true; break; }
        }
    }
    if (!dead2) {
        for (int i = 1; i < len2; i++) {
            if (body2[0] == body2[i]) { dead2 = true; break; }
        }
        for (int i = 0; i < len1; i++) {
            if (body2[0] == body1[i]) { dead2 = true; break; }
        }
    }
    if (dead1) { savehighscore(score1); }
    if (dead2) { savehighscore(score2); }
}
void SaanpGame::draw(sf::RenderWindow& window, sf::Font& font) {
    const float size = 18.f;
    const float ox = 30.f, oy = 150.f;
    char p1Arr[] = "P1: 000";
    p1Arr[4] = (score1 / 100) % 10 + '0';
    p1Arr[5] = (score1 / 10) % 10 + '0';
    p1Arr[6] = score1 % 10 + '0';
    sf::Text p1Text(p1Arr, font, 26);
    p1Text.setFillColor(sf::Color::Green);
    p1Text.setPosition(60, 60);
    window.draw(p1Text);
    char p2Arr[] = "P2: 000";
    p2Arr[4] = (score2 / 100) % 10 + '0';
    p2Arr[5] = (score2 / 10) % 10 + '0';
    p2Arr[6] = score2 % 10 + '0';
    sf::Text p2Text(p2Arr, font, 26);
    p2Text.setFillColor(sf::Color::Cyan);
    p2Text.setPosition(360, 60);
    window.draw(p2Text);
    sf::RectangleShape ground(sf::Vector2f(30 * size, 30 * size));
    ground.setPosition(ox, oy);
    ground.setFillColor(sf::Color(0, 0, 0, 50));
    window.draw(ground);
    if (!dead2) {
        for (int i = 0; i < len2; i++) {
            sf::RectangleShape s(sf::Vector2f(size - 1, size - 1));
            s.setPosition(ox + body2[i].x * size, oy + body2[i].y * size);
            s.setFillColor(i == 0 ? sf::Color::Cyan : sf::Color(0, 150, 255));
            window.draw(s);
        }
    }
    if (!dead1) {
        for (int i = 0; i < len1; i++) {
            sf::RectangleShape s(sf::Vector2f(size - 1, size - 1));
            s.setPosition(ox + body1[i].x * size, oy + body1[i].y * size);
            s.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color(0, 255, 100));
            window.draw(s);
        }
    }
    sf::CircleShape k(size / 2.5f);
    k.setFillColor(sf::Color::Red);
    k.setPosition(ox + food.x * size + 2, oy + food.y * size + 2);
    window.draw(k);
}
bool SaanpGame::iskhatam() { return dead1 || dead2; }
int SaanpGame::getwinner() {
    if (dead1 && dead2) { return 3; }
    if (dead1) { return 2; }
    if (dead2) { return 1; }
    return 0;
}
int SaanpGame::getscore1() { return score1; }
int SaanpGame::getscore2() { return score2; }
PingPongGame::PingPongGame() {
    loadscores();
    if (bgTexture.loadFromFile("D:/2ndsemesterprojects/SFML_VS_Setup_2026/SFML_VS_Setup_2026/x64/Debug/pong.png")) {
        bgSprite.setTexture(bgTexture);
        bgSprite.setScale(600.f / bgTexture.getSize().x, 850.f / bgTexture.getSize().y);
        hasBg = true;
    }
    scoreleft = 0; scoreright = 0;
    shuru();
}
void PingPongGame::loadscores() {
    ifstream inFile("pingpong_stats.txt");
    if (inFile.is_open()) {
        inFile >> totalwinsleft >> totalwinsright;
        inFile.close();
    }
}
void PingPongGame::savescores() {
    ofstream outFile("pingpong_stats.txt");
    if (outFile.is_open()) {
        outFile << totalwinsleft << " " << totalwinsright;
        outFile.close();
    }
}
void PingPongGame::shuru() {
    ball = sf::Vector2f(300.f, 425.f);
    float dirX = (rand() % 2 == 0) ? -1.f : 1.f;
    float dirY = (rand() % 2 == 0) ? -1.f : 1.f;
    ballVel = sf::Vector2f(ballspeed * dirX, ballspeed * dirY);
    p1Y = p2Y = 375.f;
    isgameover = false; winner = 0;
}
void PingPongGame::resetfull() {
    scoreleft = 0;
    scoreright = 0;
    shuru();
}
void PingPongGame::update(float dt, sf::Sound& hitSound) {
    if (isgameover) { return; }
    ball += ballVel * dt;
    if (ball.y <= 150.f || ball.y >= 835.f) {
        ballVel.y = -ballVel.y;
    }
    if (ball.x < 0) {
        scoreright++;
        if (scoreright >= 10) {
            isgameover = true;
            winner = 2;
            totalwinsright++;
            savescores();
        }
        else {
            shuru();
        }
    }
    if (ball.x > 600) {
        scoreleft++;
        if (scoreleft >= 10) {
            isgameover = true;
            winner = 1;
            totalwinsleft++;
            savescores();
        }
        else {
            shuru();
        }
    }
    sf::FloatRect p1R(50.f, p1Y, pwidth, pheight);
    sf::FloatRect p2R(535.f, p2Y, pwidth, pheight);
    sf::FloatRect bR(ball.x, ball.y, 12.f, 12.f);

    if (bR.intersects(p1R) && ballVel.x < 0) {
        ballVel.x = -ballVel.x * 1.05f;
        hitSound.play();
    }
    if (bR.intersects(p2R) && ballVel.x > 0) {
        ballVel.x = -ballVel.x * 1.05f;
        hitSound.play();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && p1Y > 155.f) { p1Y -= paddlespeed * dt; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && p1Y < 845.f - pheight) { p1Y += paddlespeed * dt; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && p2Y > 155.f) { p2Y -= paddlespeed * dt; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && p2Y < 845.f - pheight) { p2Y += paddlespeed * dt; }
}
void PingPongGame::draw(sf::RenderWindow& window, sf::Font& font) {
    if (hasBg) { window.draw(bgSprite); }
    char scoreArr[] = "00 : 00";
    scoreArr[0] = (scoreleft / 10) % 10 + '0';
    scoreArr[1] = (scoreleft % 10) + '0';
    scoreArr[5] = (scoreright / 10) % 10 + '0';
    scoreArr[6] = (scoreright % 10) + '0';
    sf::Text sText(scoreArr, font, 40);
    sText.setOrigin(sText.getLocalBounds().width / 2.f, 0);
    sText.setPosition(300.f, 50.f);
    window.draw(sText);
    sf::RectangleShape net(sf::Vector2f(2.f, 700.f));
    net.setPosition(300.f, 150.f);
    net.setFillColor(sf::Color(255, 255, 255, 50));
    window.draw(net);
    sf::RectangleShape p1(sf::Vector2f(pwidth, pheight)), p2(sf::Vector2f(pwidth, pheight));
    p1.setPosition(50.f, p1Y);
    p2.setPosition(535.f, p2Y);
    p1.setFillColor(sf::Color::Cyan);
    p2.setFillColor(sf::Color::Magenta);
    window.draw(p1);
    window.draw(p2);
    if (!isgameover) {
        sf::CircleShape b(8.f);
        b.setPosition(ball);
        b.setFillColor(sf::Color::Yellow);
        window.draw(b);
    }
    else {
        sf::RectangleShape overlay(sf::Vector2f(600.f, 850.f));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);
        const char* winMsg = (winner == 1 ? "LEFT PLAYER WINS!" : "RIGHT PLAYER WINS!");
        sf::Text resTxt(winMsg, font, 40);
        resTxt.setOrigin(resTxt.getLocalBounds().width / 2.0f, 0.5f);
        resTxt.setPosition(300.f, 400.f);
        window.draw(resTxt);
        sf::Text restartTxt("Click to Reset Game", font, 20);
        restartTxt.setOrigin(restartTxt.getLocalBounds().width / 2.0f, 0);
        restartTxt.setPosition(300.f, 480.f);
        window.draw(restartTxt);
    }
}
bool PingPongGame::getisgameover() { return isgameover; }
int PingPongGame::getwinner() { return winner; }
int PingPongGame::getscoreleft() { return scoreleft; }
int PingPongGame::getscoreright() { return scoreright; }
void getNameInput(sf::RenderWindow& window, sf::Font& font, char* nameOut, int maxLen, const char* prompt, sf::Color bgColor) {
    int len = 0;
    nameOut[0] = '\0';
    sf::Event ev;
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (ev.type == sf::Event::TextEntered) {
                if (ev.text.unicode == 8 && len > 0) {
                    len--;
                    nameOut[len] = '\0';
                }
                else if (ev.text.unicode == 13 && len > 0) {
                    return;
                }
                else if (ev.text.unicode >= 32 && ev.text.unicode < 127 && len < maxLen - 1) {
                    nameOut[len++] = (char)ev.text.unicode;
                    nameOut[len] = '\0';
                }
            }
        }
        window.clear(bgColor);
        sf::Text pTxt(prompt, font, 32);
        pTxt.setOrigin(pTxt.getLocalBounds().width / 2.f, 0);
        pTxt.setPosition(300.f, 320.f);
        window.draw(pTxt);
        sf::RectangleShape inputBox(sf::Vector2f(300.f, 50.f));
        inputBox.setPosition(150.f, 370.f);
        inputBox.setFillColor(sf::Color(255, 255, 255, 40));
        inputBox.setOutlineThickness(1);
        inputBox.setOutlineColor(sf::Color::White);
        window.draw(inputBox);
        sf::Text nTxt(nameOut, font, 32);
        nTxt.setOrigin(nTxt.getLocalBounds().width / 2.f, 0);
        nTxt.setPosition(300.f, 378.f);
        nTxt.setFillColor(sf::Color::Yellow);
        window.draw(nTxt);
        sf::Text hint("Press Enter to confirm", font, 18);
        hint.setOrigin(hint.getLocalBounds().width / 2.f, 0);
        hint.setPosition(300.f, 440.f);
        hint.setFillColor(sf::Color(200, 200, 200));
        window.draw(hint);
        window.display();
    }
}
int main() {
    srand(static_cast<unsigned>(time(NULL)));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(600, 850), "Game Hub", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("D:/2ndsemesterprojects/SFML_VS_Setup_2026/SFML_VS_Setup_2026/x64/Debug/arial.ttf")) {
        return -1;
    }
    sf::Music music;
    if (music.openFromFile("D:/2ndsemesterprojects/SFML_VS_Setup_2026/SFML_VS_Setup_2026/x64/Debug/long.ogg")) {
        music.setLoop(true);
        music.setVolume(50);
    }
    sf::SoundBuffer bufferShort, bufferOver;
    sf::Sound soundShort, soundOver;
    bufferShort.loadFromFile("D:/2ndsemesterprojects/SFML_VS_Setup_2026/SFML_VS_Setup_2026/x64/Debug/short.wav");
    bufferOver.loadFromFile("D:/2ndsemesterprojects/SFML_VS_Setup_2026/SFML_VS_Setup_2026/x64/Debug/.wav");
    soundShort.setBuffer(bufferShort);
    soundOver.setBuffer(bufferOver);
    LeaderboardManager lb;
    Tictactoe game;
    SaanpGame saanp;
    PingPongGame pong;
    int currentScreen = 0;
    sf::Clock clock;
    bool tttOverPlayed = false, snakeOverPlayed = false, pongOverPlayed = false;
    sf::Color xColor(255, 99, 71);
    sf::Color oColor(60, 179, 113);
    sf::Color overlayColor(114, 98, 209, 230);
    sf::Color bgColor(114, 98, 209);
    char p1name[50] = "Player1";
    char p2name[50] = "Player2";
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (currentScreen == 0) {
            if (music.getStatus() != sf::Music::Playing) { music.play(); }
        }
        else {
            if (music.getStatus() == sf::Music::Playing) { music.stop(); }
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mPos = sf::Mouse::getPosition(window);
                float mx = (float)mPos.x, my = (float)mPos.y;
                if (currentScreen == 0) {
                    if (sf::FloatRect(150, 280, 300, 50).contains(mx, my)) {
                        getNameInput(window, font, p1name, 50, "Player 1 (X) Name:", bgColor);
                        getNameInput(window, font, p2name, 50, "Player 2 (O) Name:", bgColor);
                        game.resetboard();
                        game.resetscores();
                        tttOverPlayed = false;
                        currentScreen = 1;
                    }
                    if (sf::FloatRect(150, 390, 300, 50).contains(mx, my)) {
                        getNameInput(window, font, p1name, 50, "Player 1 (Left) Name:", bgColor);
                        getNameInput(window, font, p2name, 50, "Player 2 (Right) Name:", bgColor);
                        pong.resetfull();
                        pongOverPlayed = false;
                        currentScreen = 3;
                    }
                    if (sf::FloatRect(150, 500, 300, 50).contains(mx, my)) {
                        getNameInput(window, font, p1name, 50, "Player 1 (WASD) Name:", bgColor);
                        getNameInput(window, font, p2name, 50, "Player 2 (Arrows) Name:", bgColor);
                        saanp.shuru();
                        snakeOverPlayed = false;
                        currentScreen = 2;
                    }
                    if (sf::FloatRect(150, 610, 300, 50).contains(mx, my)) {
                        currentScreen = 4;
                    }
                    if (sf::FloatRect(150, 720, 300, 50).contains(mx, my)) {
                        window.close();
                    }
                }
                else if (currentScreen == 1) {
                    sf::FloatRect stopBtnBounds(20, 20, 100, 40);
                    if (stopBtnBounds.contains(mx, my)) {
                        game.resetboard();
                        currentScreen = 0;
                    }
                    else if (game.getgamestate() != 0) {
                        int gs = game.getgamestate();
                        if (gs == 1) { lb.AddRecord(p1name, "TicTacToe", game.getscoreX(), 1); }
                        else if (gs == 2) { lb.AddRecord(p2name, "TicTacToe", game.getscoreO(), 1); }
                        else {
                            lb.AddRecord(p1name, "TicTacToe", game.getscoreX(), 0);
                            lb.AddRecord(p2name, "TicTacToe", game.getscoreO(), 0);
                        }
                        game.resetboard();
                        tttOverPlayed = false;
                    }
                    else {
                        for (int i = 0; i < 3; i++) {
                            for (int j = 0; j < 3; j++) {
                                sf::FloatRect bounds(95.f + j * 140.f, 175.f + i * 140.f, 120.f, 120.f);
                                if (bounds.contains(mx, my) && game.getcell(i, j) == 0) {
                                    game.makemove(i, j, soundShort);
                                }
                            }
                        }
                    }
                }
                else if (currentScreen == 2) {
                    if (sf::FloatRect(20, 20, 100, 40).contains(mx, my)) {
                        currentScreen = 0;
                    }
                    else if (saanp.iskhatam()) {
                        int w = saanp.getwinner();
                        if (w == 1) { lb.AddRecord(p1name, "Snake", saanp.getscore1(), 1); }
                        else if (w == 2) { lb.AddRecord(p2name, "Snake", saanp.getscore2(), 1); }
                        else {
                            lb.AddRecord(p1name, "Snake", saanp.getscore1(), 0);
                            lb.AddRecord(p2name, "Snake", saanp.getscore2(), 0);
                        }
                        currentScreen = 0;
                    }
                }
                else if (currentScreen == 3) {
                    if (sf::FloatRect(20, 20, 100, 40).contains(mx, my)) {
                        currentScreen = 0;
                    }
                    else if (pong.getisgameover()) {
                        int w = pong.getwinner();
                        if (w == 1) { lb.AddRecord(p1name, "PingPong", pong.getscoreleft(), 1); }
                        else { lb.AddRecord(p2name, "PingPong", pong.getscoreright(), 1); }
                        pong.resetfull();
                        pongOverPlayed = false;
                    }
                }
                else if (currentScreen == 4) {
                    if (sf::FloatRect(150, 770, 300, 50).contains(mx, my)) {
                        currentScreen = 0;
                    }
                }
            }
        }
        window.clear(bgColor);
        if (currentScreen == 0) {
            sf::Text menuTitle("Game Menu", font, 60);
            menuTitle.setOrigin(menuTitle.getLocalBounds().width / 2.0f, 0);
            menuTitle.setPosition(300.f, 100.f);
            window.draw(menuTitle);
            const char* labels[] = { "Tic Tac Toe", "Ping Pong", "Snake", "Leaderboard", "Exit" };
            float yPositions[] = { 280, 390, 500, 610, 720 };
            for (int i = 0; i < 5; i++) {
                sf::RectangleShape btn(sf::Vector2f(300.f, 50.f));
                btn.setPosition(150.f, yPositions[i]);
                btn.setFillColor(sf::Color(255, 255, 255, 30));
                btn.setOutlineThickness(1);
                btn.setOutlineColor(sf::Color(255, 255, 255, 80));
                window.draw(btn);
                sf::Text btnText(labels[i], font, 34);
                btnText.setOrigin(btnText.getLocalBounds().width / 2.0f, 0);
                btnText.setPosition(300.f, yPositions[i] + 6.f);
                window.draw(btnText);
            }
        }
        else if (currentScreen == 1) {
            if (game.getgamestate() != 0 && !tttOverPlayed) {
                soundOver.play();
                tttOverPlayed = true;
            }
            sf::RectangleShape stopBtn(sf::Vector2f(100, 40));
            stopBtn.setPosition(20, 20);
            stopBtn.setFillColor(sf::Color(255, 255, 255, 50));
            stopBtn.setOutlineThickness(1);
            window.draw(stopBtn);
            sf::Text stopText("STOP", font, 18);
            stopText.setPosition(45, 30);
            window.draw(stopText);
            char scoreTextArr[] = "X: 0 - O: 0";
            scoreTextArr[3] = (char)(game.getscoreX() % 10 + '0');
            scoreTextArr[10] = (char)(game.getscoreO() % 10 + '0');
            sf::Text scoreDisplay(scoreTextArr, font, 35);
            scoreDisplay.setOrigin(scoreDisplay.getLocalBounds().width / 2.0f, 0);
            scoreDisplay.setPosition(300.f, 30.f);
            window.draw(scoreDisplay);
            if (game.getgamestate() == 0) {
                const char* turnName = game.getplayerturn() == 1 ? p1name : p2name;
                sf::Text turnText(turnName, font, 28);
                turnText.setFillColor(game.getplayerturn() == 1 ? xColor : oColor);
                turnText.setOrigin(turnText.getLocalBounds().width / 2.0f, 0);
                turnText.setPosition(300.f, 100.f);
                window.draw(turnText);
                sf::Text turnSub(game.getplayerturn() == 1 ? "(X)" : "(O)", font, 22);
                turnSub.setFillColor(game.getplayerturn() == 1 ? xColor : oColor);
                turnSub.setOrigin(turnSub.getLocalBounds().width / 2.0f, 0);
                turnSub.setPosition(300.f, 135.f);
                window.draw(turnSub);
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    sf::RectangleShape cell(sf::Vector2f(120.f, 120.f));
                    float x = 95.f + j * 140.f, y = 175.f + i * 140.f;
                    cell.setPosition(x, y);
                    cell.setFillColor(sf::Color(248, 248, 255));
                    window.draw(cell);
                    int val = game.getcell(i, j);
                    if (val == 1) {
                        sf::RectangleShape l(sf::Vector2f(90.f, 8.f));
                        l.setFillColor(xColor);
                        l.setOrigin(45.f, 4.f);
                        l.setPosition(x + 60.f, y + 60.f);
                        l.setRotation(45.f); window.draw(l);
                        l.setRotation(-45.f); window.draw(l);
                    }
                    else if (val == 2) {
                        sf::CircleShape c(35.f);
                        c.setOutlineThickness(8.f);
                        c.setOutlineColor(oColor);
                        c.setFillColor(sf::Color::Transparent);
                        c.setOrigin(35.f, 35.f);
                        c.setPosition(x + 60.f, y + 60.f);
                        window.draw(c);
                    }
                }
            }
            if (game.getgamestate() != 0) {
                sf::RectangleShape overlay(sf::Vector2f(600.f, 850.f));
                overlay.setFillColor(overlayColor);
                window.draw(overlay);
                int gs = game.getgamestate();
                const char* winName = (gs == 1) ? p1name : (gs == 2) ? p2name : "IT'S A DRAW!";
                sf::Text resTxt(winName, font, 45);
                resTxt.setOrigin(resTxt.getLocalBounds().width / 2.0f, 0);
                resTxt.setPosition(300.f, 340.f);
                window.draw(resTxt);
                if (gs != 3) {
                    sf::Text sub("WINS!", font, 35);
                    sub.setOrigin(sub.getLocalBounds().width / 2.0f, 0);
                    sub.setPosition(300.f, 400.f);
                    window.draw(sub);
                }
                sf::Text restrt("Click to Play Again", font, 20);
                restrt.setOrigin(restrt.getLocalBounds().width / 2.0f, 0);
                restrt.setPosition(300.f, 460.f);
                window.draw(restrt);
            }
        }
        else if (currentScreen == 2) {
            sf::RectangleShape sBtn(sf::Vector2f(100, 40));
            sBtn.setPosition(20, 20);
            sBtn.setFillColor(sf::Color(255, 255, 255, 50));
            sBtn.setOutlineThickness(1);
            window.draw(sBtn);
            sf::Text sTxt("STOP", font, 18);
            sTxt.setPosition(45, 30);
            window.draw(sTxt);
            saanp.handleinput();
            saanp.update(dt, soundShort);
            saanp.draw(window, font);
            if (saanp.iskhatam()) {
                if (!snakeOverPlayed) {
                    soundOver.play();
                    snakeOverPlayed = true;
                }
                sf::RectangleShape over(sf::Vector2f(600, 850));
                over.setFillColor(sf::Color(0, 0, 0, 160));
                window.draw(over);
                int w = saanp.getwinner();
                const char* winName = (w == 1) ? p1name : (w == 2) ? p2name : "IT'S A DRAW!";
                sf::Text resTxt(winName, font, 48);
                resTxt.setOrigin(resTxt.getLocalBounds().width / 2.f, 0);
                resTxt.setPosition(300.f, 310.f);
                window.draw(resTxt);
                if (w != 3) {
                    sf::Text ws("WINS!", font, 36);
                    ws.setOrigin(ws.getLocalBounds().width / 2.f, 0);
                    ws.setPosition(300.f, 370.f);
                    window.draw(ws);
                }
                char finalScores[] = "P1: 000    P2: 000";
                finalScores[4] = (saanp.getscore1() / 100) % 10 + '0';
                finalScores[5] = (saanp.getscore1() / 10) % 10 + '0';
                finalScores[6] = saanp.getscore1() % 10 + '0';
                finalScores[15] = (saanp.getscore2() / 100) % 10 + '0';
                finalScores[16] = (saanp.getscore2() / 10) % 10 + '0';
                finalScores[17] = saanp.getscore2() % 10 + '0';
                sf::Text scTxt(finalScores, font, 30);
                scTxt.setOrigin(scTxt.getLocalBounds().width / 2.f, 0);
                scTxt.setPosition(300.f, 420.f);
                window.draw(scTxt);
                sf::Text wapas("Click to go back!", font, 20);
                wapas.setOrigin(wapas.getLocalBounds().width / 2.f, 0);
                wapas.setPosition(300.f, 480.f);
                window.draw(wapas);
            }
        }
        else if (currentScreen == 3) {
            pong.update(dt, soundShort);
            pong.draw(window, font);
            if (pong.getisgameover() && !pongOverPlayed) {
                soundOver.play();
                pongOverPlayed = true;
            }
            sf::RectangleShape stopBtn(sf::Vector2f(100, 40));
            stopBtn.setPosition(20, 20);
            stopBtn.setFillColor(sf::Color(255, 255, 255, 100));
            stopBtn.setOutlineThickness(1);
            window.draw(stopBtn);

            sf::Text sT("STOP", font, 18);
            sT.setPosition(45, 30);
            window.draw(sT);
        }
        else if (currentScreen == 4) {
            lb.DisplayLeaderboard(window, font);
        }
        window.display();
    }
    return 0;
}