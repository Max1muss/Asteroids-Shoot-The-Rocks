#pragma once
#include "Object.h"

class Bullet : public Object
{
	float m_lifeTime = 0;
	bool m_isAuto = false;
	int m_markIndex = 0;
	float distance, tempX, tempY;

public:
	Bullet(string name, float x, float y, int dir, float w, float h, bool isAuto, int markIndex) : Object(name, x, y, dir, w, h)
	{
		m_image.loadFromFile("images/bullet.png");
		m_image.createMaskFromColor(Color(255, 255, 255));
		m_texture.loadFromImage(m_image);
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(IntRect(0, 0, 3, 12));
		m_sprite.setOrigin(m_w / 2, m_h / 2);
		m_isAuto = isAuto;
		m_markIndex = markIndex;
	}

	virtual Sprite getSprite();
	virtual void update(float time);
	virtual void update() {}
	virtual IntRect getRect();
	virtual int getDirection(){ return static_cast<int>(m_dir); }
	virtual float getSpeed() { return m_speed; }
	virtual bool isBulletAuto() { return m_isAuto; }
	virtual int getMarkIndex() { return m_markIndex; }
	virtual void setTempX(float x) { tempX = x; }
	virtual void setTempY(float y) { tempY = y; }
};

