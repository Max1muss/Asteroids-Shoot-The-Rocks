#include "Bullet.h"

Sprite Bullet::getSprite()
{
	return m_sprite;
}

void Bullet::update(float time)
{
	if (!m_isAuto) // if bullet is not auto
	{
		if (getX() > 858) // teleport bullet on the opposite side of the map after reaching the edge
			setX(-10);
		else if (getX() < (-10))
			setX(858);

		if (getY() > 487)
			setY(-10);
		else if (getY() < (-10))
			setY(487);


		m_lifeTime += time;
		if (m_lifeTime > 400) // make bullet exist for 0.4 sec, then destroy
			kill();

		switch (m_dir)
		{
		case UP: m_sprite.setTextureRect(IntRect(0, 0, 3, 12));
			setY(getY() - 1 * time); break;
		case DOWN: m_sprite.setTextureRect(IntRect(0, 0, 3, 12));
			setY(getY() + 1 * time); break;
		case LEFT: m_sprite.setTextureRect(IntRect(34, 4, 12, 3));
			setX(getX() - 1 * time); break;
		case RIGHT: m_sprite.setTextureRect(IntRect(34, 4, 12, 3));
			setX(getX() + 1 * time); break;
		case UP_LEFT: m_sprite.setTextureRect(IntRect(22, 2, 9, 10));
			setY(getY() - 1 * time);
			setX(getX() - 1 * time); break;
		case UP_RIGHT: m_sprite.setTextureRect(IntRect(8, 2, 9, 9));
			setY(getY() - 1 * time);
			setX(getX() + 1 * time); break;
		case DOWN_LEFT: m_sprite.setTextureRect(IntRect(9, 2, 9, 9));
			setY(getY() + 1 * time);
			setX(getX() - 1 * time); break;
		case DOWN_RIGHT: m_sprite.setTextureRect(IntRect(22, 2, 9, 10));
			setY(getY() + 1 * time);
			setX(getX() + 1 * time); break;
		}

	}
	else // if bullet is auto
	{

		distance = sqrt((tempX - getX()) * (tempX - getX()) + (tempY - getY()) * (tempY - getY()));//count the distance to the aim

		if (distance > 2)
		{

			setX(getX() + 1 * time * (tempX - getX()) / distance);
			setY(getY() + 1 * time * (tempY - getY()) / distance);
		}

		if (getY() > tempY && (abs(getX() - tempX)) <= 100) //bent bullet to the proper angle
			m_sprite.setTextureRect(IntRect(0, 0, 3, 12));
		else if (getX() < tempX && (abs(getY() - tempY)) <= 50)
			m_sprite.setTextureRect(IntRect(34, 4, 12, 3));
		else if (getY() < tempY && (abs(getX() - tempX)) <= 100)
			m_sprite.setTextureRect(IntRect(0, 0, 3, 12));
		else if (getX() > tempX && (abs(getY() - tempY)) <= 50)
			m_sprite.setTextureRect(IntRect(34, 4, 12, 3));
		else if ((getX() > tempX) && (getY() > tempY))
			m_sprite.setTextureRect(IntRect(22, 2, 9, 10));
		else if ((getX() < tempX) && (getY() > tempY))
			m_sprite.setTextureRect(IntRect(8, 2, 9, 9));
		else if ((getX() < tempX) && (getY() < tempY))
			m_sprite.setTextureRect(IntRect(22, 2, 9, 10));
		else if ((getX() > tempX) && (getY() < tempY))
			m_sprite.setTextureRect(IntRect(8, 2, 9, 9));
	
	}

	m_sprite.setPosition(getX(), getY());
}

IntRect Bullet::getRect()
{
	return IntRect(m_x, m_y, m_w, m_h);
}