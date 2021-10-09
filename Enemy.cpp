#include "Enemy.h"

Enemy::Enemy(Texture* texture,Vector2f position, Vector2f direction, int type, float Upsize, Vector2u imagecnt, float switchtime,int hp, int hpMax, int damage,Color color)
{
	this->texture = texture;
	this->Upsize = Upsize;
	this->sprite.setOrigin(128.f, 88.f);
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(Upsize, Upsize);
	this->color = color;
	this->sprite.setColor(color);
	this->type = type;

	this->direction = direction;
	this->sprite.setPosition(position.x, position.y);

	this->hpMax = hpMax;
	this->hp = hp;
	this->damage = damage;

	this->imagecnt = imagecnt;
	this->switchtime = switchtime;
	totaltime = 0.0f;
	currentimage.x = 0;
	currentimage.y = 0;

	uvrect.width = texture->getSize().x / imagecnt.x;
	uvrect.height = texture->getSize().y / imagecnt.y;
	sprite.setTextureRect(uvrect);
}

Enemy::~Enemy()
{

}

void Enemy::Update(Vector2f PlayerPos, float deltatime)
{
	this->EnemyPos = getPosition();
	direction = PlayerPos - EnemyPos;
	directionNorm = direction / sqrt((direction.x * direction.x + direction.y * direction.y));
	this->sprite.move(directionNorm.x*2, directionNorm.y*2);

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
}

void Enemy::Draw(RenderWindow &window)
{
	window.draw(this->sprite);
}
