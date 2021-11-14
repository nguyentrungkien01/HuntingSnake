#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class Object
{
public:
	void setData(const string& link);
	void setPosition(const Vector2f& position);
	void setScale(float width, float heigh);
	void setColor();
	bool causeCollisionObj(Object& part);
	Vector2u getSize()const;
	Vector2f getPosition()const;
	float getWidth()const;
	float getHeigh()const;
	void draw(RenderWindow& window);
private:
	Texture texture;
	Sprite sprite;
};

