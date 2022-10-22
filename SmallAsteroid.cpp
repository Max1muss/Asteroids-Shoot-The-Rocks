#include "SmallAsteroid.h"

void SmallAsteroid::update(float time)
{

	tempX = getX(); //set temp coordinates
	tempY = getY();

	if (!isDead)
	{
		if (getX() > 868)// teleport asteroid on the opposite side of the map after reaching the edge
			setX(-20);
		else if (getX() < (-20))
			setX(868);

		if (getY() > 497)
			setY(-20);
		else if (getY() < (-20))
			setY(497);

		m_sprite.setPosition(getX(), getY());

		if (m_index)
		{
			if (m_dir == UP_LEFT)
			{
				tempX = getX() - m_speed * time;
				tempY = getY() - (m_speed / 2) * time;
			}
			else if (m_dir == UP_RIGHT)
			{
				tempY = getY() - m_speed * time;
				tempX = getX() + (m_speed / 2) * time;
			}
			else if (m_dir == DOWN_LEFT)
			{
				tempY = getY() + m_speed * time;
				tempX = getX() - (m_speed / 2) * time;
			}
			else if (m_dir == DOWN_RIGHT)
			{
				tempX = getX() + m_speed * time;
				tempY = getY() + (m_speed / 2) * time;
			}
		}
		else
		{
			if (m_dir == UP_LEFT)
			{
				tempY = getY() - m_speed * time;
				tempX = getX() - (m_speed / 2) * time;
			}
			else if (m_dir == UP_RIGHT)
			{
				tempX = getX() + m_speed * time;
				tempY = getY() - (m_speed / 2) * time;
			}
			else if (m_dir == DOWN_LEFT)
			{
				tempX = getX() - m_speed * time;
				tempY = getY() + (m_speed / 2) * time;
			}
			else if (m_dir == DOWN_RIGHT)
			{
				tempY = getY() + m_speed * time;
				tempX = getX() + (m_speed / 2) * time;
			}
		}

		setX(tempX);
		setY(tempY);


	}
}



Sprite SmallAsteroid::getSprite()
{
	return m_sprite;
}

IntRect SmallAsteroid::getRect()
{
	return IntRect(m_x, m_y, m_w, m_h);
}


void SmallAsteroid::push(int dir1, int dir2, int state) // push rocks on collision 
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
		setX(getX() - 0.1); // this one is nice!
		setY(getY() - 0.1);
	}
	else if (dir1 == 7 && dir2 == 4 && state == 4)
	{
		setX(getX() + 0.1); // this one is nice!
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
