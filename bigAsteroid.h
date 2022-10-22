#pragma once
#include "Object.h"

class BigAsteroid : public Object
{
protected:
	float tempX = 0, tempY = 0;
	float m_speed = 0;
	bool isAimed = false;
	int m_markIndex = 0;

public:

	BigAsteroid(string name, float x, float y, int dir, float w, float h, float speed) 
		: Object(name, x, y, dir, w, h)
	{
		m_image.loadFromFile("images/big_asteroid.png");
		m_texture.loadFromImage(m_image);
		m_sprite.setTexture(m_texture);
		m_speed = speed;
	}

	~BigAsteroid() { std::cout << "Destroyed"; }

	virtual void update(){}
	virtual void update(float time);
	virtual Sprite getSprite();
	virtual IntRect getRect();
	virtual int getDirection();
	virtual float getSpeed();
	virtual void push(int dir1, int dir2, int state);
	virtual void putAim() { isAimed = true; }
	virtual bool isRockAimed() { return isAimed; }
	virtual void mark(int markIndex) { m_markIndex = markIndex; }
	virtual int getMarkIndex() { return m_markIndex; }
};

