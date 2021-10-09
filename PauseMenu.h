#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
class PauseMenu
{
private:
	
	Vector2f position;

	//Window
	RenderWindow* window;
	View view;

	Font font_Pixeboy;
	
	//Score
	int Score;
	Text score_text;
	Texture scorebackTex;
	Sprite scoreback;

	//PlayerName
	Texture playerNameBackTex;
	Sprite playerNameBack;
	string playerName;
	Text playerNameText;


	Sprite play_button;
	Texture play_buttontex;

	Sprite home_button;
	Texture home_buttontex;

	Sprite save_button;
	Texture save_buttontex;

	Sprite wallpaper;
	Texture wallpaperTex;

	int IsPlay = 0;
	int IsHome = 0;
	int IsSave = 0;

public:
	PauseMenu(RenderWindow* window, View& view);
	virtual ~PauseMenu();

	inline int getHome() { return IsHome; }
	inline int getPlay() { return IsPlay; }

	inline void getPlayerName(string playername) { this->playerName = playername; }
	inline void getScore(int score) { this->Score = score; }

	void resetPlay() { IsPlay = 0; }
	void resetHome() { IsHome = 0; }

	void Update(RenderWindow& window,Vector2f position);
	void Draw(RenderWindow& window);
};

