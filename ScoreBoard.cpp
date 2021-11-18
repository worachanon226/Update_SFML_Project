#define _CRT_SECURE_NO_WARNINGS
#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
    this->font.loadFromFile("Font/Pixeboy-z8XGD.ttf");
    this->wallpaperTex.loadFromFile("Texture/Wallpaper/ScoreMenu.png");
    this->wallpaper.setTexture(wallpaperTex);
    this->wallpaper.setOrigin(Vector2f(wallpaperTex.getSize().x / 2, wallpaperTex.getSize().y / 2));
    this->wallpaper.setPosition(640.0f, 360.0f);

    this->CloseButtonTex.loadFromFile("Texture/Box/Close_Button.png");
    this->CloseButton.setTexture(CloseButtonTex);
    this->CloseButton.setScale(0.8f, 0.8f);
    this->CloseButton.setOrigin(Vector2f(CloseButtonTex.getSize().x / 2, CloseButtonTex.getSize().y / 2));
    this->CloseButton.setPosition(1450.0f,-50.0f);

    this->mouseCursorTex.loadFromFile("Texture/Mouse/MainCursor.png");
    this->mouseCursor.setTexture(mouseCursorTex);
    this->mouseCursor.setOrigin(Vector2f(mouseCursorTex.getSize().x / 2, mouseCursorTex.getSize().y / 2));
    this->mouseCursor.setScale(0.1f, 0.1f);
}

void ScoreBoard::ReadFile()
{
    this->fp = fopen("./Resource/Score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
        fscanf(fp, "%s", &temp); name[i] = temp;
        fscanf(fp, "%d", &score[i]);

        this->userScore.push_back(make_pair(this->score[i], this->name[i]));
    }
}

void ScoreBoard::WriteFile(string name, unsigned int score)
{
    ReadFile(); 
    this->name[5] = name;
    this->score[5] = score;
    this->userScore.push_back(make_pair(this->score[5], this->name[5]));
    sort(this->userScore.begin(), this->userScore.end());
    fclose(this->fp);

    fopen("./Resource/Score.txt", "w");
    for (int i = 5; i > 0; i--)
    {
        //cout << userScore[i].second.c_str() << " " << userScore[i].first << endl;
        strcpy(temp, userScore[i].second.c_str());
        fprintf(fp, "%s %d\n", temp, userScore[i].first);
    }
    fclose(this->fp);

}

void ScoreBoard::Update(RenderWindow& window, Event event)
{
    ReadFile(); fclose(this->fp);
    for (int i = 0; i < 5; i++) {
        strcpy(temp, userScore[i].second.c_str());
        playerName[i].setFont(this->font);
        playerName[i].setFillColor(Color::Black);
        playerName[i].setCharacterSize(100);
        playerName[i].setPosition(100.0f, 150.0f + (i * 140));
        playerName[i].setString(to_string(i + 1) + ". " + name[i]);
        playerName[i].setOrigin(0, playerName[i].getLocalBounds().height);

        playerScore[i].setFont(this->font);
        playerScore[i].setFillColor(Color::Black);
        playerScore[i].setCharacterSize(100);
        playerScore[i].setPosition(1150.0f, 150.0f + (i * 140));
        playerScore[i].setString(to_string(score[i]));
        playerScore[i].setOrigin(playerScore[i].getLocalBounds().width, playerScore[i].getLocalBounds().height);
    
        //cout << "Show: " << name[i] << " " << score[i] << endl;
    }

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    this->mouseCursor.setPosition(worldPos);

    if (CloseButton.getGlobalBounds().contains(worldPos.x, worldPos.y))
    {
        this->CloseButton.setScale(0.9f, 0.9f);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) toMenu = 1;

    }
    else {
        this->CloseButton.setScale(0.8f, 0.8f);
    }
}

void ScoreBoard::Draw(RenderWindow& window)
{
    window.clear();
    window.draw(this->wallpaper);
    window.draw(CloseButton);
    for (int i = 0; i < 5; i++) {
        window.draw(playerName[i]);
        window.draw(playerScore[i]);
    }
    window.draw(mouseCursor);
    window.display();
}