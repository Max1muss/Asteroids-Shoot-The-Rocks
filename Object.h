#pragma once
#include <iostream>
#include <SFML/graphics.hpp>
using namespace std;
using namespace sf;

class Object
{
protected:
	Image m_image;
	Texture m_texture;
	Sprite m_sprite;
	float m_x = 0, m_y = 0;
	float m_w, m_h;
	string m_name;
	enum Direction { UP, DOWN, RIGHT, LEFT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };
	Direction m_dir;
	bool isDead = false;
	float m_speed = 0;
	bool isDirectionChanged = false;

public:
	
	Object(string name, float x, float y, int dir, float w, float h)
		: m_name(name), m_x(x), m_y(y), m_w(w), m_h(h)
	{
		m_dir = static_cast<Direction>(dir);
	}


	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	virtual void update() = 0;
	virtual Sprite getSprite() = 0;
	virtual void update(float time) = 0;
	virtual void update(float x, float y){}
	string getName();
	virtual IntRect getRect() = 0;
	void kill();
	bool isDestroyed();
	virtual int getDirection() = 0;
	virtual float getSpeed() = 0;
	void setDirection(int dir) { m_dir = static_cast<Direction>(dir); isDirectionChanged = true;}
	bool isDirChanged() { return isDirectionChanged; }
	virtual void activate(){}
	virtual bool isShieldActive() { return false; }
	virtual void deactivateShield(){}
	virtual void push(int dir1, int dir2, int state){}
	virtual void putAim(){}
	virtual bool isRockAimed() { return false; }
	virtual void pickUp() {}
	virtual bool isMissilePicked() { return false; }
	virtual bool isMissileLaunched() { return false; }
	virtual void setTempX(float x) {}
	virtual void setTempY(float y) {}
	virtual int getState() { return 0; }
	virtual void mark(int markIndex) {}
	virtual bool isBulletAuto() { return false; }
	virtual int getMarkIndex() { return 0; }
	//virtual void update(float time) = 0;
	//virtual void update(RenderWindow window, float time) = 0;

};

