#include "bigAsteroid.h"

void BigAsteroid::update(float time)
{

	if (!isDead) 
	{

		if (getX() > 873) // teleport asteroid on the opposite side of the map after reaching the edge
			setX(-25);
		else if (getX() < (-25))
			setX(873);

		if (getY() > 502)
			setY(-25);
		else if (getY() < (-25))
			setY(502);

		m_sprite.setPosition(getX(), getY());


		if (m_dir == UP)
			tempY = getY() - m_speed * time;
		else if (m_dir == DOWN)
			tempY = getY() + m_speed * time;
		else if (m_dir == RIGHT)
			tempX = getX() + m_speed * time;
		else if (m_dir == LEFT)
			tempX = getX() - m_speed * time;
		else if (m_dir == UP_LEFT)
		{
			tempX = getX() - m_speed * time;
			tempY = getY() - m_speed * time;
		}
		else if (m_dir == UP_RIGHT)
		{
			tempX = getX() + m_speed * time;
			tempY = getY() - m_speed * time;
		}
		else if (m_dir == DOWN_LEFT)
		{
			tempX = getX() - m_speed * time;
			tempY = getY() + m_speed * time;
		}
		else if (m_dir == DOWN_RIGHT)
		{
			tempX = getX() + m_speed * time;
			tempY = getY() + m_speed * time;
		}

		setX(tempX); // set coordinates
		setY(tempY);

	}

	
}

Sprite BigAsteroid::getSprite()
{
	return m_sprite;
}

IntRect BigAsteroid::getRect()
{
	return IntRect(m_x, m_y, m_w, m_h);
}

int BigAsteroid::getDirection()
{
	return static_cast<int>(m_dir);
}

float BigAsteroid::getSpeed()
{
	return m_speed;
}

void BigAsteroid::push(int dir1, int dir2, int state) // push rocks on collision 
{
	if (dir1 == 7 && dir2 == 4 && state == 0)
	{
		setX(getX() - 0.5);
		setY(getY() + 0.5);
	}
	else if (dir1 == 7 && dir2 == 4 && state == 1)
	{
		setX(getX() + 0.5); 
		setY(getY() - 0.5);
	}
	else if (dir1 == 7 && dir2 == 4 && state == 2)
	{
		setX(getX() - 0.5); 
		setY(getY() + 0.5);
	}
	else if (dir1 == 7 && dir2 == 4 && state == 3)
	{
		setX(getX() - 0.1); 
		setY(getY() - 0.1);
	}
	else if (dir1 == 7 && dir2 == 4 && state == 4)
	{
		setX(getX() + 0.1); 
		setY(getY() + 0.1);
	}
	if (dir1 == 7 && dir2 == 6 && state == 3)
	{
		setX(getX() - 0.1);
		setY(getY() + 0.1);
	}
	if (dir1 == 7 && dir2 == 6 && state == 4)
	{
		setX(getX() + 0.1);
		setY(getY() + 0.1);
	}
	else if (dir1 == 4 && dir2 == 7 && state == 0)
	{
		setX(getX() - 0.5);
		setY(getY() + 0.5);
	}
	else if (dir1 == 4 && dir2 == 7 && state == 1)
	{
		setX(getX() + 0.5);
		setY(getY() - 0.5);
	}
	else if (dir1 == 4 && dir2 == 7 && state == 2)
	{
		setX(getX() - 0.5);
		setY(getY() + 0.5);
	}
	else if (dir1 == 6 && dir2 == 5 && state == 0)
	{
		setX(getX() + 0.5);
		setY(getY() + 0.5);
	}
	else if (dir1 == 6 && dir2 == 5 && state == 1)
	{
		setX(getX() + 0.5);
		setY(getY() + 0.5);
	}
	else if (dir1 == 6 && dir2 == 5 && state == 2)
	{
		setX(getX() - 0.5);
		setY(getY() - 0.5);
	}
	else if (dir1 == 6 && dir2 == 5 && state == 3)
	{
		setX(getX() + 0.1);
		setY(getY() - 0.1);
	}
	else if (dir1 == 6 && dir2 == 5 && state == 4)
	{
		setX(getX() - 0.1);
		setY(getY() + 0.1);
	}
	else if (dir1 == 5 && dir2 == 4 && state == 3)
	{
		setX(getX() - 0.1);
		setY(getY() - 0.1);
	}
	else if (dir1 == 5 && dir2 == 4 && state == 4)
	{
		setX(getX() + 0.1);
		setY(getY() - 0.1);
	}
	else if (dir1 == 5 && dir2 == 4)
	{
		setX(getX() - 0.5);
		setY(getY() - 0.5);
	}
	else if (dir1 == 7 && dir2 == 5 && state == 3)
	{
		setX(getX() + 0.1);
		setY(getY() - 0.1);
	}
	else if (dir1 == 7 && dir2 == 5 && state == 4)
	{
		setX(getX() + 0.1);
		setY(getY() + 0.1);
	}
	else if (dir1 == 6 && dir2 == 4 && state == 3)
	{
		setX(getX() - 0.1);
		setY(getY() - 0.1);
	}
	else if (dir1 == 6 && dir2 == 4 && state == 4)
	{
		setX(getX() - 0.1);
		setY(getY() + 0.1);
	}
	else if (dir1 == 5 && dir2 == 7)
	{
		setX(getX() + 0.5);
		setY(getY() + 0.5);
	}
	else if (dir1 == 7 && dir2 == 7 && state == 3)
	{
		setX(getX() + 0.1);
		setY(getY() - 0.1);
	}
	else if (dir1 == 7 && dir2 == 7 && state == 4)
	{
		setX(getX() - 0.1);
		setY(getY() + 0.1);
	}
	else if (dir1 == 7 && dir2 == 7 && state == 5)
	{
		setX(getX() + 0.1);
		setY(getY() - 0.1);
	}
	else if (dir1 == 7 && dir2 == 7)
	{
		setY(getY() - 0.5);
		setX(getX() + 0.5);
	}
	else if (dir1 == 6 && dir2 == 6 && state == 3)
	{
	setX(getX() - 0.1);
	setY(getY() - 0.1);
	}
	else if (dir1 == 6 && dir2 == 6 && state == 4)
	{
	setX(getX() + 0.1);
	setY(getY() + 0.1);
	}
	else if (dir1 == 6 && dir2 == 6 && state == 5)
	{
	setX(getX() - 0.1);
	setY(getY() - 0.1);
	}
	else if (dir1 == 6 && dir2 == 6)
	{
		setY(getY() - 0.5);
		setX(getX() - 0.5);
	}
	else if (dir1 == 5 && dir2 == 7 && state == 0)
	{
	setX(getX() + 0.1);
	setY(getY() + 0.1);
	}
	else if (dir1 == 5 && dir2 == 5 && state == 3)
	{
	setX(getX() - 0.1);
	setY(getY() - 0.1);
	}
	else if (dir1 == 5 && dir2 == 5 && state == 4)
	{
	setX(getX() + 0.1);
	setY(getY() + 0.1);
	}
	else if (dir1 == 5 && dir2 == 5 && state == 5)
	{
	setX(getX() - 0.1);
	setY(getY() - 0.1);
	}
	else if (dir1 == 5 && dir2 == 5)
	{
		setY(getY() - 0.5);
		setX(getX() - 0.5);
	}
	else if (dir1 == 4 && dir2 == 4 && state == 3)
	{
	setX(getX() + 0.1);
	setY(getY() - 0.1);
	}
	else if (dir1 == 4 && dir2 == 4 && state == 4)
	{
	setX(getX() - 0.1);
	setY(getY() + 0.1);
	}
	else if (dir1 == 4 && dir2 == 4 && state == 5)
	{
	setX(getX() + 0.1);
	setY(getY() - 0.1);
	}
	else if (dir1 == 4 && dir2 == 4)
	{
		setY(getY() - 0.5);
		setX(getX() + 0.5);
	}
}