#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ScoreBoard.h"
#include "Background.h"
#include <SFML/Audio.hpp>
class Game
{
private:
	Vector2f PlayerPosition;

	//Pause
	int IsPause;
	
	//Window
	RenderWindow *window;
	View view;

	//Score
	int Score;
	Texture scorebackTex;
	Sprite scoreback;

	//Text & Font
	Font font_Pixeboy;
	Text score_text;

	string playerName;
	Text playerNameText;

	Texture playerNameBackTex;
	Sprite playerNameBack;

	//Character
	vector<Player> players;
	vector<Enemy> enemies;

	//Texture
	Texture playerTexture;
	Texture bulletTexture;
	Texture enemyTexture;
	Texture CureBoxTexture;
	Texture BulletBoxTexture;
	Texture ScoreBoxTexture;
	Texture mapTexture;

	Texture hpBarBackTex;
	Texture hpBarTex;
	
	Texture hpBarBackEnemyTex;
	Texture hpBarEnemyTex;

	//UI
	Sprite pause_button;
	Texture pause_buttontex;

	//Mouse
	Sprite mouseCursor;
	Texture mouseCursorTex;

	//Box
	int showing;
	int Boxtype;
	int StopUseBullet;
	int StopUseScore;

	int UsingBulletBox;
	int UsingScoreBox;

	int BulletBoxShowing;
	int CureBoxShowing;
	int ScoreBoxShowing;

	float UsingTimeBox;
	float UsingTimeMaxBox;
	float DelaytimeSpawn;
	float DelaytimeSpawnMax;
	float DelaytimeDel;
	float DelaytimeDelMax;

	RectangleShape CureBox;
	RectangleShape BulletBox;
	RectangleShape ScoreBox;
	RectangleShape AimCursor;

	//PLayer_HP_Bar
	RectangleShape hpBarBack;
	RectangleShape hpBar;
	RectangleShape hpBarBackEnemy;
	RectangleShape hpBarEnemy;

	//Time_Spanw_Enemy
	float MaxTimeSpawnEnemy;
	float NowTimeSpawnEnemy;

	//Health Point
	int Maxhp;
	int hp;

	int isAlive = 1;
	int IsHome = 0;
	int ch = 1;

	//Gameover
	Texture gameoverTex;
	Sprite gameover;
	Sprite home_button;
	Texture home_buttontex;


public:
	Game(RenderWindow* window, View& view);
	virtual ~Game();

	//Accessors
	inline RenderWindow& getWindow() { return *this->window; }
	inline const Vector2i getMousePos() { return Mouse::getPosition(*this->window); }

	//Function
	
	inline Vector2f getPlayerPosition()const { return PlayerPosition; }
	inline int getPause() { return IsPause; }
	inline void resetPause() { IsPause = 0; }

	inline void getPlayerName(string playername) { this->playerName = playername; }
	inline int getHp() { return this->hp; }

	inline int getScore() { return Score; }
	inline string getName() { return playerName; }

	inline int getHome() { return IsHome; }
	void resetHome() { IsHome = 0; }

	void InitUI();
	void UpdateUI(int i,int j);
	void ButtonUI(RenderWindow& window);
	void Update(float deltatime);
	void DrawUI();
	void CombatUpdate();
	void Draw(RenderWindow &window);
	void ResizeView(RenderWindow &windoww, View& view, float VIEW_HEIGHT);
	void ResetGame();
};

