#pragma once
#include "Object.h"

class Missile : public Object
{
	Image bonusImage;
	bool isPicked = false;
	bool isLaunched = false;
	float tempX = 0, tempY = 0, distance = 0;
	int m_state = 0;

public:
	Missile(string name, float x, float y, int dir, float w, float h, int state) : Object(name, x, y, dir, w, h)
	{
		m_image.loadFromFile("images/homing_missile.png");
		m_image.createMaskFromColor(Color(255, 255, 255));
		bonusImage.loadFromFile("images/bonusImage.png");
		bonusImage.createMaskFromColor(Color(255, 255, 255));
		m_texture.loadFromImage(bonusImage);
		m_sprite.setTexture(m_texture);

		m_state = state;
		
		if (state)
		{
			launchMissile();
		}
		
	}

	virtual void update() {}
	virtual Sprite getSprite() { return m_sprite; }
	virtual void update(float time);
	virtual IntRect getRect() { return IntRect(m_x, m_y, m_w, m_h); }
	virtual int getDirection() { return static_cast<int>(m_dir); }
	virtual float getSpeed() { return m_speed; }
	virtual void pickUp() { isPicked = true; }
	virtual bool isMissilePicked() { return isPicked; }
	void launchMissile() { isLaunched = true; }
	virtual void setTempX(float x) { tempX = x; }
	virtual void setTempY(float y) { tempY = y; }
	virtual bool isMissileLaunched() { return isLaunched; }
	virtual int getState() { return m_state; }
};

