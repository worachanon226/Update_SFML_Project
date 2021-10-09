#pragma once
#include "Player.h"
class Enemy
{
private:
	Texture* texture;
	Sprite sprite;
	Vector2f direction;
	Vector2f directionNorm;
	Vector2f EnemyPos;
	Color color;

	int type;
	int hp;
	int hpMax;
	int damage;

	float Upsize;

	float totaltime;
	Vector2u imagecnt;
	float switchtime;
	Vector2u currentimage;
	IntRect uvrect;

public:
	Enemy(Texture* texture, Vector2f position, Vector2f direction, 
		int type, float Upsize, Vector2u imagecnt, float switchtime, int hp, int hpMax, int damage, Color color);
	virtual ~Enemy();
	inline FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition()const { return this->sprite.getPosition(); }
	inline FloatRect getLocalBounds()const { return this->sprite.getLocalBounds(); }
	inline int getMaxhp()const { return this->hpMax; }
	inline int getHp()const { return this->hp; }
	inline int getType()const { return this->type; }
	inline int getDamage()const { return this->damage; }
	inline float getScale()const { return this->Upsize; }
	inline Color getcolor()const { return this->color; }

	void Update(Vector2f PlayerPos,float deltatime);
	void Draw(RenderWindow &window);
};

