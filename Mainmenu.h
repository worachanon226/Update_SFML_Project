#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
class Mainmenu
{
private:
	Event event;

	//Window
	RenderWindow* window;
	View view;

	Sprite mouseCursor;
	Texture mouseCursorTex;

	//Text & Font
	Font font_Pixeboy;
	Text mainmenu_text;
	Text Play_text;
	Text Leader_text;
	Text Quit_text;

	Text InputName_text;
	Text PlayerName;
	Text OnlyEight;
	Text PuNename;
	String Name;

	//Sprite
	Sprite Mainmenu_Play;
	Texture Mainmenu_PlayTex;

	Sprite Mainmenu_Leader;
	Texture Mainmenu_LeaderTex;

	Sprite Mainmenu_Quit;
	Texture Mainmenu_QuitTex;

	Sprite play_button;
	Texture play_buttontex;

	Sprite InputName;
	Texture InputNameTex;

	Sprite CloseInputNameButton;
	Texture CloseInputNameButtonTex;

	//Wallpaper
	Sprite wallpaper;
	Texture wallpaperTex;

	int IsPlay = 0;
	int IsScore = 0;
	int IsNameInput = 0;

	float delaynow;
	float delayMax;

public:
	Mainmenu(RenderWindow* window, View& view);
	virtual ~Mainmenu();

	inline int getPlay() { return IsPlay; }
	inline int getScore() { return IsScore; }
	inline string getName() { return Name; }

	inline void setScore() { IsScore = 0; }

	void resetPlay() { IsPlay = 0; IsScore = 0; this->IsNameInput = 0;  Name.clear(); PlayerName.setString(Name); }


	void Update(RenderWindow& window, Event event,float deltatime);
	void Draw(RenderWindow& window);
};

