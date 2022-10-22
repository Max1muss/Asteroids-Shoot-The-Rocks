#include "Missile.h"
#include <cmath>

void Missile::update(float time)
{
	if (isLaunched)
	{
		m_texture.loadFromImage(m_image);

		if (m_speed < 0.5) // steadily increasing missile's speed
		m_speed += 0.00035 * time;

		distance = sqrt((tempX - getX()) * (tempX - getX()) + (tempY - getY()) * (tempY - getY())); // count the distance to the target

		if (distance > 2) 
		{

			setX(getX() + m_speed * time * (tempX - getX()) / distance);
			setY(getY() + m_speed * time * (tempY - getY()) / distance);
		}

		if (getY() > tempY && (abs(getX() - tempX)) <= 100) // bent sprite accoringly
			m_sprite.setTextureRect(IntRect(0, 0, 15, 25));
		else if (getX() < tempX && (abs(getY() - tempY)) <= 50)
			m_sprite.setTextureRect(IntRect(21, 4, 23, 15));
		else if (getY() < tempY && (abs(getX() - tempX)) <= 100)
			m_sprite.setTextureRect(IntRect(50, 0, 15, 25));
		else if (getX() > tempX && (abs(getY() - tempY)) <= 50)
			m_sprite.setTextureRect(IntRect(73, 4, 23, 15));
		else if ((getX() > tempX) && (getY() > tempY))
			m_sprite.setTextureRect(IntRect(4, 29, 19, 19));
		else if ((getX() < tempX) && (getY() > tempY))
			m_sprite.setTextureRect(IntRect(31, 29, 19, 19));
		else if ((getX() < tempX) && (getY() < tempY))
			m_sprite.setTextureRect(IntRect(57, 28, 19, 19));
		else if ((getX() > tempX) && (getY() < tempY))
			m_sprite.setTextureRect(IntRect(89, 28, 19, 19));
	}

	m_sprite.setPosition(getX(), getY());
}
