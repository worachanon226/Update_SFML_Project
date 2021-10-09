#include "Bullet.h"

Bullet::Bullet(Texture *texture, Vector2f position, Vector2f Dirc,Vector2f maxVelocity,Vector2f scale)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->maxVelocity = maxVelocity;
	this->sprite.setScale(scale);
	this->sprite.setPosition(position);

	this->Dirc = Dirc;
}

Bullet::~Bullet()
{

}
void Bullet::Movement()
{
	this->sprite.move(20.0f * Dirc.x, 20.0f * Dirc.y);
}
void Bullet::Update()
{
	this->Movement();
}

void Bullet::Draw(RenderWindow& window)
{
	window.draw(this->sprite);
}
