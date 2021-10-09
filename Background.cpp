#include "Background.h"

Background::Background()
{
	this->texture.loadFromFile("Texture/Map/Map.png");
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(float(texture.getSize().x / 2), float(texture.getSize().y / 2));
	this->sprite.setPosition(206.0f, 256.0f);
	this->sprite.setScale(0.4f, 0.4f);
}

void Background::ViewUpdate(View& view, Vector2f PlayerPos)
{
	view.setCenter(PlayerPos);
}

void Background::Draw_map(RenderWindow& window)
{
	window.draw(this->sprite);
}
