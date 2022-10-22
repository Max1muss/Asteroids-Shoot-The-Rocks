#pragma once
#include "Object.h"


class Shield : public Object
{
	Image shieldIcon;
	bool isActive = false;

public:

	Shield(string name, float x, float y, int dir, float w, float h) : Object(name, x, y, dir, w, h)
	{
		m_image.loadFromFile("images/shield.png");
		m_image.createMaskFromColor(Color(255, 255, 255));
		shieldIcon.loadFromFile("images/shieldIcon.png");
		shieldIcon.createMaskFromColor(Color(255, 255, 255));
		m_texture.loadFromImage(shieldIcon);
		m_sprite.setTexture(m_texture);
	}

	virtual Sprite getSprite();
	virtual void update(float time);
	virtual void update() {}
	void update(float x, float y);
	virtual IntRect getRect();
	virtual int getDirection() { return static_cast<int>(m_dir); }
	virtual float getSpeed() { return m_speed; }
	virtual void activate();
	virtual bool isShieldActive(){ return isActive; }
	virtual void deactivateShield() { isActive = false; isDead = true; }
	
};

