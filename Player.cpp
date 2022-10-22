#include "Player.h"

void Player::update(RenderWindow& window, float time)
{

	if (!isDead) // check if player alive
	{
		if (getX() > 868) // teleport player on the opposite side of the map after reaching the edge
			setX(-20);
		else if (getX() < (-20))
			setX(868);

		if (getY() > 497)
			setY(-20);
		else if (getY() < (-20))
			setY(497);

		m_sprite.setPosition(getX(), getY());

		if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left)) // add speed for the chosen direction
		{
			setDirection(4);
			if (upSpeed < 0.3)
				upSpeed += 0.0015;
			if (leftSpeed < 0.3)
				leftSpeed += 0.0015;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right))
		{
			setDirection(5);
			if (upSpeed < 0.3)
				upSpeed += 0.0015;
			if (rightSpeed < 0.3)
				rightSpeed += 0.0015;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left))
		{
			setDirection(6);
			if (downSpeed < 0.3)
				downSpeed += 0.0015;
			if (leftSpeed < 0.3)
				leftSpeed += 0.0015;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right))
		{
			setDirection(7);
			if (downSpeed < 0.3)
				downSpeed += 0.0015;
			if (rightSpeed < 0.3)
				rightSpeed += 0.0015;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			setDirection(0);
			if (upSpeed < 0.3)
				upSpeed += 0.0015;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			setDirection(1);
			if (downSpeed < 0.3)
				downSpeed += 0.0015;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			setDirection(2);
			if (rightSpeed < 0.3)
				rightSpeed += 0.0015;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			setDirection(3);
			if (leftSpeed < 0.3)
				leftSpeed += 0.0015;
		}


		if (m_dir == UP) // turn sprite accordingly to the player's direction
			m_sprite.setTextureRect(IntRect(0, 0, 40, 37));
		else if (m_dir == DOWN)
			m_sprite.setTextureRect(IntRect(78, 0, 40, 37));
		else if (m_dir == RIGHT)
			m_sprite.setTextureRect(IntRect(40, 0, 38, 37));
		else if (m_dir == LEFT)
			m_sprite.setTextureRect(IntRect(116, 0, 38, 37));
		else if (m_dir == UP_LEFT)
			m_sprite.setTextureRect(IntRect(0, 37, 50, 50));
		else if (m_dir == UP_RIGHT)
			m_sprite.setTextureRect(IntRect(50, 37, 50, 50));
		else if (m_dir == DOWN_LEFT)
			m_sprite.setTextureRect(IntRect(110, 37, 50, 50));
		else if (m_dir == DOWN_RIGHT)
			m_sprite.setTextureRect(IntRect(160, 37, 50, 50));

		setY(getY() - upSpeed * time); // set player's coordinates 
		setY(getY() + downSpeed * time);
		setX(getX() + rightSpeed * time);
		setX(getX() - leftSpeed * time);


		if (upSpeed > 0) // slowing down player gradually until 0 speed
			upSpeed -= 0.001 * (time / 10);
		if (downSpeed > 0)
			downSpeed -= 0.001 * (time / 10);
		if (leftSpeed > 0)
			leftSpeed -= 0.001 * (time / 10);
		if (rightSpeed > 0)
			rightSpeed -= 0.001 * (time / 10);
		if (upSpeed < 0)
			upSpeed = 0;
		if (downSpeed < 0)
			downSpeed = 0;
		if (leftSpeed < 0)
			leftSpeed = 0;
		if (rightSpeed < 0)
			rightSpeed = 0;
	}
	else // explode animation after death
	{
	    currentFrame += 0.02 * time;
		if (currentFrame > 3)
		{
			m_sprite.setTextureRect(IntRect(60 * frameCount, 0, 60, 60));
			++frameCount;
			currentFrame = 0;
		}

		if (frameCount > 5)
		{
			isDead = false;
			setX(window.getSize().x / 2.0f);
			setY(window.getSize().y / 2.0f);
			upSpeed = 0; downSpeed = 0; rightSpeed = 0; leftSpeed = 0;
			isImmune = true;
			m_texture.loadFromImage(m_image);
			frameCount = 0;
		}
    }
}

Sprite Player::getSprite()
{
	return m_sprite;
}

void Player::setDirection(int dir)
{
	m_dir = static_cast<Direction>(dir);
}

int Player::getDirection()
{
	return static_cast<int>(m_dir);
}

IntRect Player::getRect()
{
	return IntRect(m_x, m_y, m_w, m_h);
}
void Player::explode()
{
	m_texture.loadFromImage(m_explosion);
    isDead = true;
}

bool Player::isPlayerImmune()
{
	return isImmune;
}

void Player::setVulnerable()
{
	isImmune = false;
}

void Player::setImmune()
{
	isImmune = true;
}

void Player::paintBlue() // like we are under shield
{
	m_sprite.setColor(Color(153, 217, 234));
}

void Player::removeBlue()
{
	m_sprite.setColor(Color::White);
}

