#pragma once
#include "Object.h"

class Aim : public Object
{
public:
	Aim(string name, float x, float y, int dir, float w, float h) : Object(name, x, y, dir, w, h)
	{
		m_image.loadFromFile("images/aim.png");
		m_texture.loadFromImage(m_image);
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(IntRect(0, 0, 25, 25));
		m_sprite.setOrigin(m_w / 2, m_h / 2);
		std::cout << "aim created\n";
	}
	

	virtual void update(){}
	virtual Sprite getSprite() { return m_sprite; }
	virtual void update(float time);
	virtual IntRect getRect() { return IntRect(m_x, m_y, m_w, m_h); }
	virtual int getDirection() { return static_cast<int>(m_dir); }
	virtual float getSpeed() { return m_speed; }
};

