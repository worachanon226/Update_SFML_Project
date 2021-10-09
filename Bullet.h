#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

class Bullet
{
private:

	Texture *texture;
	Sprite sprite;

	Vector2f maxVelocity;
	Vector2f Dirc;

public:
	Bullet(Texture *texture,Vector2f position,Vector2f Dirc,Vector2f maxVelocity = Vector2f(10.0f,10.0f),Vector2f scale = Vector2f(0.045f,0.045f));
	virtual ~Bullet();

	//Accessors
	inline const FloatRect& getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline const Vector2f& getPosition()const { return this->sprite.getPosition(); }
	
	//Functions
	void Movement();
	void Update();
	void Draw(RenderWindow& window);
};

