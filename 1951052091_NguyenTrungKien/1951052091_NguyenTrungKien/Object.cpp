#include "Object.h"
void Object:: setData(const string& link)
{
	
	this->texture.loadFromFile(link);
	this->sprite.setTexture(texture);
}
void Object::setPosition(const Vector2f& position)
{
	this->sprite.setPosition(position.x, position.y);
}
void Object::setScale(float width, float heigh)
{
	this->sprite.setScale(width, heigh);
}
void Object::setColor()
{
	this->sprite.setColor(Color::Cyan);
}
bool Object::causeCollisionObj(Object& part)
{
	if (this->sprite.getGlobalBounds().intersects(part.sprite.getGlobalBounds()))
		return true;
	return false;
}
Vector2u Object:: getSize()const
{
	return this->texture.getSize();
}
Vector2f Object::getPosition()const
{
	return this->sprite.getPosition();
}
float Object::getWidth()const
{
	return this->sprite.getGlobalBounds().width;
}
float Object::getHeigh()const
{
	return this->sprite.getGlobalBounds().height;
}
void Object::draw(RenderWindow& window)
{
	window.draw(this->sprite);
}