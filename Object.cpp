#include "Object.h"
#include <iostream>



float Object::getX()
{
	return m_x;
}

float Object::getY()
{
	return m_y;
}

void Object::setX(float x)
{
	m_x = x;
}

void Object::setY(float y)
{
	m_y = y;
}

string Object::getName()
{
	return m_name;
}

void Object::kill()
{
	isDead = true;
}

bool Object::isDestroyed()
{
	return isDead;
}


