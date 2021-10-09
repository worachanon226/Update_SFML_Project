#pragma once
#include "Bullet.h"
#include <iostream>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <string.h>
#include <vector>
#include <iomanip>
using namespace std;
class ScoreBoard
{
private:
    FILE* fp;
    char temp[255];
    unsigned int score[6];
    string name[6];
    vector<pair<int, string>> userScore;
    unsigned int getScore;
    string getName;

    Font font;
    Text playerName[5];
    Text playerScore[5];

    Texture wallpaperTex;
    Sprite wallpaper;

    Sprite CloseButton;
    Texture CloseButtonTex;

    int toMenu = 0;

public:
    ScoreBoard();

    void Update(RenderWindow& window, Event event);
    void Draw(RenderWindow& window);
    void ReadFile();
    void WriteFile(string name, unsigned int score);

    inline int istoMenu() { return toMenu; }
    inline void settoMenu() { toMenu = 0; }
};