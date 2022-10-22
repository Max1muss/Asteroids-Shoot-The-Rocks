#pragma once
#include "Object.h"

class SmallAsteroid : public Object
{
	float tempX = 0, tempY = 0;
	int m_index;
	bool isAimed = false;
	int m_markIndex = 0;

public:

	SmallAsteroid(string name, float x, float y, int dir, float w, float h, int index, float speed) : Object(name, x, y, dir, w, h)
	{
		m_image.loadFromFile("images/small_asteroid.png");
		m_texture.loadFromImage(m_image);
		m_sprite.setTexture(m_texture);
		m_speed = speed;
		m_index = index;
	}


	virtual void update(){};
	virtual Sprite getSprite();
	virtual void update(float time);
	virtual IntRect getRect();
	virtual int getDirection(){ return static_cast<int>(m_dir); }
	virtual float getSpeed() { return m_speed; }
	virtual void push(int dir1, int dir2, int state);
	virtual void putAim() { isAimed = true; }
	virtual bool isRockAimed() { return isAimed; }
	virtual void mark(int markIndex) { m_markIndex = markIndex; }
	virtual int getMarkIndex() { return m_markIndex; }
};


