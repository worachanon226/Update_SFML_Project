#pragma once
#include "Bullet.h"
#include <SFML/Audio.hpp>
class Player
{
private:
	unsigned playerNr;

	int shootTimer;
	int shootTimerMax;

	Texture *texture;
	Sprite sprite;
	RectangleShape hitBox;

	Texture* bulletTexture;
	vector<Bullet> bullets;

	int hp;
	int hpMax;
	int scoremul;
	int damage;

	float totaltime;
	Vector2u imagecnt;
	float switchtime;
	Vector2u currentimage;

	Vector2f aimDir;
	Vector2f aimDirNorm;
	Vector2f MousePos;
	Vector2f PlayerPos;

	SoundBuffer attackBuffer;

	Sound attackSound;

	Color color;

public:
	Player(Texture* texture, Texture* bulletTexture,Vector2u imagecnt, float switchtime, Vector2f position, 
	int hp, int hpMax, int scoremul, int damage, int shootTimerMax);
	virtual ~Player();

	inline vector<Bullet>& getBullets() { return this->bullets; }

	void Movement(float speed);
	void Combat(RenderWindow &window);
	void Update(Vector2u windowBounds,float deltatime);
	inline const int gethp()const { return this->hp; }
	inline const int gethpMax()const { return this->hpMax; }
	inline const int getScoremul()const { return this->scoremul; }
	inline const int getShootTimerMax()const { return this->shootTimerMax; }
	inline const Vector2f& getPosition()const { return this->sprite.getPosition(); }
	inline const FloatRect& getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	
	void SetColorOpa() { this->sprite.setColor(Color(255, 255, 255, 100)); }
	void SetColor() { this->sprite.setColor(Color(255, 255, 255, 225)); }
	void Draw(RenderWindow& window);

	static unsigned players;

public:
	IntRect uvrect;
};

