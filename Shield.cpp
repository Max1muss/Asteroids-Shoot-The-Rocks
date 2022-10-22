#include "Shield.h"

IntRect Shield::getRect()
{
	return IntRect(m_x, m_y, m_w, m_h);
}

Sprite Shield::getSprite()
{
	return m_sprite;
}

void Shield::update(float x, float y)
{
	setX(x - 30);
	setY(y - 32);
	m_sprite.setPosition(getX(), getY());
}

void Shield::update(float time)
{
	m_sprite.setPosition(getX(), getY());
}

void Shield::activate()
{
	isActive = true;
	m_texture.loadFromImage(m_image);
	m_sprite.setColor(Color(153, 217, 234, 128));
	m_w = 80;
	m_h = 80;
	m_sprite.setTextureRect(IntRect(0, 0, m_w, m_h));
}
