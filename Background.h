#pragma once
#include "Player.h"
class Background
{

private:
	Sprite sprite;
	Texture texture;

	View view;
	
public:
	Background();

	void ViewUpdate(View &view,Vector2f PlayerPos);

	void Draw_map(RenderWindow &target);
};

