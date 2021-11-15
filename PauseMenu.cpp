#include "PauseMenu.h"
#include "Game.h"
#include "Background.h"
#include "Enemy.h"

PauseMenu::PauseMenu(RenderWindow* window, View& view)
{
	this->position = position;

	this->window = window;
	this->view = view;

	this->IsPlay = IsPlay;

	this->font_Pixeboy.loadFromFile("Font/Pixeboy-z8XGD.ttf");

#pragma region PlayerName & Score

	//Score Back
	this->scorebackTex.loadFromFile("Texture/Box/score_back.png");
	this->scoreback.setTexture(scorebackTex);
	this->scoreback.setOrigin(scorebackTex.getSize().x / 2.0f, scorebackTex.getSize().y / 2.0f);
	this->scoreback.setScale(0.4f, 0.4f);

	this->mouseCursorTex.loadFromFile("Texture/Mouse/MainCursor.png");
	this->mouseCursor.setTexture(mouseCursorTex);
	this->mouseCursor.setOrigin(Vector2f(mouseCursorTex.getSize().x / 2, mouseCursorTex.getSize().y / 2));
	this->mouseCursor.setScale(0.05f, 0.05f);

	//PlayerName Back
	this->playerNameBackTex.loadFromFile("Texture/Box/Button.png");
	this->playerNameBack.setTexture(playerNameBackTex);
	this->playerNameBack.setOrigin(playerNameBackTex.getSize().x / 2.0f, playerNameBackTex.getSize().y / 2.0f);
	this->playerNameBack.setScale(2.2f, 1.5f);

	//Score Text
	this->score_text.setString("Score: " + to_string(Score));
	this->score_text.setFont(font_Pixeboy);
	this->score_text.setFillColor(Color::Black);
	this->score_text.setCharacterSize(1000);
	this->score_text.setScale(0.03f, 0.03f);
	
	//PlayerName Text
	this->playerNameText.setFont(font_Pixeboy);
	this->playerNameText.setFillColor(Color::Black);
	this->playerNameText.setCharacterSize(1000);
	this->playerNameText.setScale(0.03f, 0.03f);
#pragma endregion

	this->play_buttontex.loadFromFile("Texture/Box/Play.png");
	this->play_button.setTexture(play_buttontex);
	this->play_button.setOrigin(Vector2f(play_buttontex.getSize().x / 2, play_buttontex.getSize().y / 2));
	this->play_button.setScale(0.35f, 0.35f);

	this->home_buttontex.loadFromFile("Texture/Box/Home.png");
	this->home_button.setTexture(home_buttontex);
	this->home_button.setOrigin(Vector2f(home_buttontex.getSize().x / 2, home_buttontex.getSize().y / 2));
	this->home_button.setScale(0.35f, 0.35f);

	this->save_buttontex.loadFromFile("Texture/Box/Save.png");
	this->save_button.setTexture(save_buttontex);
	this->save_button.setOrigin(Vector2f(save_buttontex.getSize().x / 2, save_buttontex.getSize().y / 2));
	this->save_button.setScale(0.35f, 0.35f);

	this->wallpaperTex.loadFromFile("Texture/Wallpaper/Pausemenu.png");
	this->wallpaper.setTexture(wallpaperTex);
	this->wallpaper.setOrigin(Vector2f(wallpaperTex.getSize().x / 2, wallpaperTex.getSize().y / 2));
	this->wallpaper.setScale(1.f, 1.f);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update(RenderWindow& window, Vector2f position)
{
	play_button.setPosition(position.x, position.y);
	home_button.setPosition(position.x - 150.0f, position.y);
	save_button.setPosition(position.x + 150.0f, position.y);
	playerNameText.setString("Name: " + this->playerName);
	score_text.setString("Score: " + to_string(this->Score));

	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

	// convert it to world coordinates
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	
	this->mouseCursor.setPosition(worldPos);

	if (play_button.getGlobalBounds().contains(worldPos.x, worldPos.y))
	{
		this->play_button.setScale(0.36f, 0.36f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) IsPlay = 1;
	}
	else {
		this->play_button.setScale(0.35f, 0.35f);
	}

	if (home_button.getGlobalBounds().contains(worldPos.x, worldPos.y))
	{
		this->home_button.setScale(0.36f, 0.36f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) IsHome = 1;
	}
	else {
		this->home_button.setScale(0.35f, 0.35f);
	}

	if (save_button.getGlobalBounds().contains(worldPos.x, worldPos.y))
	{
		this->save_button.setScale(0.36f, 0.36f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			ScoreBoard().WriteFile(playerName, Score);
		}
	}
	else {
		this->save_button.setScale(0.35f, 0.35f);
	}

#pragma region PlayerName & Score
	wallpaper.setPosition(position.x, position.y);
	
	scoreback.setPosition(position.x, position.y - 215.0f);

	score_text.setOrigin(score_text.getLocalBounds().width / 2, score_text.getLocalBounds().height / 2);
	score_text.setPosition(scoreback.getPosition().x,scoreback.getPosition().y-15.0f);

	playerNameBack.setPosition(position.x, position.y + 215.0f);
	playerNameText.setOrigin(playerNameText.getLocalBounds().width / 2, playerNameText.getLocalBounds().height / 2);
	playerNameText.setPosition(playerNameBack.getPosition().x, playerNameBack.getPosition().y - 14.0f);
#pragma endregion
}

void Game::ResizeView(RenderWindow& windoww, View& view, float VIEW_HEIGHT)
{
	float aspectratio = float(windoww.getSize().x) / float(windoww.getSize().y);

	this->view.setSize(VIEW_HEIGHT * aspectratio, VIEW_HEIGHT);

	windoww.setView(view);
}


void PauseMenu::Draw(RenderWindow& window)
{
	this->window->draw(wallpaper);

	this->window->draw(play_button);
	this->window->draw(home_button);
	this->window->draw(save_button);

	this->window->draw(this->scoreback);
	this->window->draw(this->score_text);
	this->window->draw(this->playerNameBack);
	this->window->draw(this->playerNameText);

	this->window->draw(mouseCursor);

	this->window->display();
}
