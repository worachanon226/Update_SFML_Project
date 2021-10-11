#include "Player.h"
#include "Background.h"
#include <math.h>

unsigned Player::players = 0;
Player::Player(Texture *texture,Texture *bulletTexture,Vector2u imagecnt,float switchtime,
	Vector2f position, int hp, int hpMax, int scoremul, int damage, int shootTimerMax)
{
	this->texture = texture;
	this->bulletTexture = bulletTexture;

	this->attackBuffer.loadFromFile("Sound/Attacking.wav");
	this->attackSound.setBuffer(attackBuffer);
	this->attackSound.setVolume(100);

	this->sprite.setOrigin(128.0f, 88.0f);
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.175f, 0.175f);
	this->sprite.setPosition(position);

	this->hp = hp; 
	this->hpMax = hpMax;
	this->scoremul = scoremul;
	this->damage = damage;

	this->shootTimerMax = shootTimerMax;
	this->shootTimer = this->shootTimerMax;

	this->imagecnt = imagecnt;
	this->switchtime = switchtime;
	totaltime = 0.0f;
	currentimage.x = 0;
	currentimage.y = 0;

	uvrect.width = texture->getSize().x / imagecnt.x;
	uvrect.height = texture->getSize().y / imagecnt.y;
	sprite.setTextureRect(uvrect);

	this->playerNr = Player::players;
	Player::players++;
}

Player::~Player()
{

}
void Player::Movement(float speed) 
{
	int ch = 0, chr = 0, chl = 0, cht = 0, chb = 0;
	Vector2f CheckMap = getPosition(); float tempSpd = speed;

	if (CheckMap.x > 530) chr = 1;
	else chr = 0;

	if (CheckMap.x < -50) chl = 1;
	else chl = 0;

	if (CheckMap.y < 0) cht = 1;
	else cht = 0;

	if (CheckMap.y > 545) chb = 1;
	else chb = 0;

	if (Keyboard::isKeyPressed(Keyboard::LShift)) 
	{
		speed *= 1.5;
	}

	if (Keyboard::isKeyPressed(Keyboard::W) && cht == 0) 
	{
		this->sprite.move(0.f, -speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && chb == 0)
	{
		this->sprite.move(0.f, speed);
	}
		
	if (Keyboard::isKeyPressed(Keyboard::A) && chl == 0)
	{
		this->sprite.move(-speed, 0.f);
	}
		
	if (Keyboard::isKeyPressed(Keyboard::D) && chr == 0)
	{
		this->sprite.move(speed, 0.f);
	}
}

void Player::Combat(RenderWindow &window)
{
	

	if (Mouse::isButtonPressed(Mouse::Left)  && this->shootTimer >= shootTimerMax)
	{
		attackSound.play();

		PlayerPos = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		MousePos = Vector2f(Mouse::getPosition(window));

		aimDir = MousePos - PlayerPos;

		aimDirNorm = aimDir / sqrt((aimDir.x * aimDir.x + aimDir.y * aimDir.y));

		this->bullets.push_back(Bullet(bulletTexture, this->sprite.getPosition(),aimDirNorm));
		this->shootTimer = 0;
	}

	/*
	if (Keyboard::isKeyPressed(Keyboard::P)) 
	{
		PlayerPos = Vector2f(getPosition());
		cout << "Position: " << PlayerPos.x << " " << PlayerPos.y << endl;
	}
	*/
}

void Player::Update(Vector2u windowBounds,float deltatime)
{

	//Animation 
	uvrect.top = currentimage.y * uvrect.height;
	currentimage.y = 0;
	totaltime += deltatime;

	if (totaltime >= switchtime) {
		totaltime -= switchtime;
		currentimage.x++;
		if (currentimage.x >= imagecnt.x) currentimage.x = 0;
	}

	uvrect.left = currentimage.x * uvrect.width;
	sprite.setTextureRect(uvrect);

	//Time
	if(this->shootTimer < this->shootTimerMax){
		this->shootTimer++;
	}

	//Other
	this->Movement(3.0f);
}

void Player::Draw(RenderWindow &window) 
{
	window.draw(this->sprite);
	for (size_t i = 0; i < this->bullets.size();i++) {
		this->bullets[i].Draw(window);
	}
	this->Combat(window);
}