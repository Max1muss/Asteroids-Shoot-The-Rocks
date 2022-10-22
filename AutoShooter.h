#pragma once
#include "Object.h"

class AutoShooter : public Object
{
public:
	AutoShooter(string name, float x, float y, int dir, float w, float h) : Object(name, x, y, dir, w, h)
	{
		m_image.loadFromFile("images/autoShooter.png");
		m_image.createMaskFromColor(Color(255, 255, 255));
		m_texture.loadFromImage(m_image);
		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin(m_w / 2, m_h / 2);
	}

	virtual Sprite getSprite() { return m_sprite; }
	virtual void update(float time);
	virtual void update() {}
	virtual IntRect getRect() { return IntRect(m_x, m_y, m_w, m_h); }
	virtual int getDirection() { return static_cast<int>(m_dir); }
	virtual float getSpeed() { return m_speed; }
};

