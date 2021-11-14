#include "Snake.h"
#include <iostream>
Snake::Snake()
{
	this->snake.pHead = NULL;
	this->snake.pTail = NULL;
}
Node* Snake::createNode(const float & posX, const float& posY)
{
	Node* node = new Node;
	node->posX = posX;
	node->posY = posY;
	node->pNext = NULL;
	node->pPrevious = NULL;
	return node;
}
void Snake::addHead(Node* node)
{
	if (this->snake.pHead == NULL)
		this->snake.pHead = this->snake.pTail = node;
	else
	{
		node->pNext = this->snake.pHead;
		this->snake.pHead->pPrevious = node;
		this->snake.pHead = node;
	}
}
void Snake::addTail(Node* node)
{
	if (this->snake.pHead == NULL)
		this->snake.pHead = this->snake.pTail = node;
	else
	{
		this->snake.pTail->pNext = node;
		node->pPrevious = this->snake.pTail;
		this->snake.pTail = node;
	}
}
void Snake::delTail()
{
	this->snake.pTail = this->snake.pTail->pPrevious;
	delete this->snake.pTail->pNext;
	this->snake.pTail->pNext = NULL;
}
void Snake::createFirstSnakePlayer1(const string & linkSnakePlayer1)
{
	Node* head;
	head = createNode(850, 700);
	addHead(head);
	Object part;
	part.setData(linkSnakePlayer1);
	part.setPosition(Vector2f(850, 700));

	Node* body;
	part.setScale(0.4f, 0.4f);
	part.setPosition(Vector2f(this->snake.pHead->posX - part.getWidth(), this->snake.pHead->posY));
	body = createNode(part.getPosition().x,part.getPosition().y);
	addTail(body);

	
	Node* tail;
	part.setScale(0.4f, 0.4f);
	part.setPosition(Vector2f(this->snake.pHead->pNext->posX - part.getWidth(), this->snake.pHead->pNext->posY));
	tail = createNode(part.getPosition().x , part.getPosition().y);
	addTail(tail);

}
void Snake::createFirstSnakePlayer2(const string & linkSnakePlayer2)
{
	Node* head;
	head = createNode(750, 550);
	addHead(head);
	Object part;
	part.setData(linkSnakePlayer2);
	part.setPosition(Vector2f(750, 550));
	
	Node* body;
	part.setPosition(Vector2f(this->snake.pHead->posX + part.getWidth(), this->snake.pHead->posY));
	part.setScale(0.4f, 0.4f);
	body = createNode(part.getPosition().x, part.getPosition().y);
	addTail(body);
	
	Node* tail;
	part.setScale(0.4f, 0.4f);
	part.setPosition(Vector2f(this->snake.pHead->pNext->posX + part.getWidth(), this->snake.pHead->pNext->posY));
	tail = createNode(part.getPosition().x , part.getPosition().y);
	addTail(tail);
}
void Snake::controlSnakePlayer1(int& status, const string & linkSnakePlayer1)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && status != 1 && status != 0)
	{
		this->moveLeft(linkSnakePlayer1);
		status = 0;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right) && status != 0 && status != 1)
	{
		this->moveRight(linkSnakePlayer1);
		status = 1;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && status != 2 && status != 3)
	{
		this->moveUp(linkSnakePlayer1);
		status = 2;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down) && status != 3 && status != 2)
	{
		this->moveDown(linkSnakePlayer1);
		status = 3;
		return;
	}
}
void Snake::controlSnakePlayer2(int& status, const string & linkSnakePlayer2)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::A) && status != 1 && status != 0)
	{
		this->moveLeft(linkSnakePlayer2);
		status = 0;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D) && status != 0 && status != 1)
	{
		this->moveRight(linkSnakePlayer2);
		status = 1;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W) && status != 2 && status != 3)
	{
		this->moveUp(linkSnakePlayer2);
		status = 2;
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S) && status != 3 && status != 2)
	{
		this->moveDown(linkSnakePlayer2);
		status = 3;
		return;
	}
}
void Snake::moveLeft(const string & linkSnakePlayer)
{
	Node* newHead;
	Object part;
	part.setData(linkSnakePlayer);
	part.setScale(0.7f, 0.7f);
	this->snake.pHead->posX += 18;
	part.setPosition(Vector2f(this->snake.pHead->posX - part.getWidth(), this->snake.pHead->posY));
	newHead = this->createNode(part.getPosition().x, part.getPosition().y);
	this->addHead(newHead);
	this->snake.pHead->pNext->posY += 10;
	this->delTail();
}
void Snake::moveRight(const string & linkSnakePlayer)
{
	Node* newHead;
	Object part;
	part.setData(linkSnakePlayer);
	part.setScale(0.4f, 0.4f);
	part.setPosition(Vector2f(this->snake.pHead->posX + part.getWidth(), this->snake.pHead->posY));
	newHead = this->createNode(part.getPosition().x, part.getPosition().y);
	this->addHead(newHead);
	this->snake.pHead->pNext->posY += 10;
	this->delTail();
}
void Snake::moveUp(const string & linkSnakePlayer)
{
	Node* newHead;
	Object part;
	part.setData(linkSnakePlayer);
	part.setScale(0.7f, 0.7f);
	part.setPosition(Vector2f(this->snake.pHead->posX, this->snake.pHead->posY - part.getHeigh() + 18));
	this->snake.pHead->posY += 18;
	newHead = this->createNode(part.getPosition().x, part.getPosition().y);
	this->addHead(newHead);
	this->snake.pHead->pNext->posX += 10;
	this->delTail();
}
void Snake::moveDown(const string & linkSnakePlayer)
{
	Node* newHead;
	Object part;
	part.setData(linkSnakePlayer);
	part.setScale(0.7f, 0.7f);
	part.setPosition(Vector2f(this->snake.pHead->posX, this->snake.pHead->posY + part.getHeigh() - 18));
	newHead = this->createNode(part.getPosition().x, part.getPosition().y);
	this->addHead(newHead);
	this->snake.pHead->pNext->posX += 10;
	this->delTail();
}
bool Snake::causeCollisionSnake(RenderWindow& window, const string & linkSnakePlayer)
{
	if (this->snake.pHead->posX >= window.getSize().x - 80 || this->snake.pHead->posX <= 25)
		return true;
	if (this->snake.pHead->posY <= 30 || this->snake.pHead->posY >= window.getSize().y - 70)
		return true;
	Object partHead;
	Object partTest;
	partHead.setData(linkSnakePlayer);
	partHead.setScale(0.7f, 0.7f);
	partHead.setPosition(Vector2f(this->snake.pHead->posX, this->snake.pHead->posY));

	partTest.setData(linkSnakePlayer);
	for (Node* i = this->snake.pHead->pNext->pNext; i != NULL; i = i->pNext)
	{
		partTest.setPosition(Vector2f(i->posX, i->posY));
		partTest.setScale(0.4f, 0.4f);
		if (partHead.causeCollisionObj(partTest))
			return true;
	}
	return false;
}
bool Snake::causeCollisionTwoSnake(const string &linkSnakePlayer1, const Snake& snakePlayer2, const string & linkSnakePlayer2)
{
	Object partPlayer1;
	Object partPlayer2;
	partPlayer1.setData(linkSnakePlayer1);
	partPlayer2.setData(linkSnakePlayer2);
	partPlayer1.setPosition(Vector2f(this->snake.pHead->posX, this->snake.pHead->posY));
	partPlayer1.setScale(0.6f, 0.6f);
	for (Node *i = snakePlayer2.getPositonSnake().pHead; i != NULL; i = i->pNext)
	{
		if (i == snakePlayer2.getPositonSnake().pHead)
			partPlayer2.setScale(0.7f, 0.7f);
		else
			partPlayer2.setScale(0.4f, 0.4f);
		partPlayer2.setPosition(Vector2f(i->posX, i->posY));
		if (partPlayer1.causeCollisionObj(partPlayer2))
			return true;
	}
	partPlayer2.setPosition(Vector2f(snakePlayer2.getPositonSnake().pHead->posX, snakePlayer2.getPositonSnake().pHead->posY));
	partPlayer2.setScale(0.55f, 0.55f);
	for (Node *i = this->snake.pHead; i != NULL; i = i->pNext)
	{
		if (i == this->snake.pHead)
			partPlayer1.setScale(0.7f, 0.7f);
		else
			partPlayer1.setScale(0.4f, 0.4f);
		partPlayer1.setPosition(Vector2f(i->posX, i->posY));
		if (partPlayer2.causeCollisionObj(partPlayer1))
			return true;
	}
	return false;
}
void Snake::eatFoods(const int& status)
{
	if (status == 0)
	{
		Node* newTail = this->createNode(this->snake.pTail->posX - 20, this->snake.pTail->posY);
		this->addTail(newTail);
	}
	else
		if (status == 1)
		{
			Node* newTail = this->createNode(this->snake.pTail->posX + 20, this->snake.pTail->posY);
			this->addTail(newTail);
		}
		else
			if (status == 2)
			{
				Node* newTail = this->createNode(this->snake.pTail->posX, this->snake.pTail->posY - 20);
				this->addTail(newTail);
			}
			else
			{
				Node* newTail = this->createNode(this->snake.pTail->posX, this->snake.pTail->posY + 20);
				this->addTail(newTail);
			}
}
List Snake::getPositonSnake()const
{
	return this->snake;
}
int Snake::count()
{
	int count = 0;
	for (Node* i = this->snake.pHead; i != NULL; i = i->pNext)
		count++;
	return count;
}
void Snake::drawSnake(RenderWindow& window,Object& part)
{
	for (Node* i = this->snake.pHead; i != NULL; i = i->pNext)
	{
		if (i == this->snake.pHead)
			part.setScale(0.7f, 0.7f);
			
		else
			part.setScale(0.4f, 0.4f);
		part.setPosition(Vector2f(i->posX, i->posY));
		part.draw(window);
	}
	part.setScale(0.7f, 0.7f);
	if(this->snake.pHead!=NULL)
		part.setPosition(Vector2f(this->snake.pHead->posX, this->snake.pHead->posY));
}
void Snake::releaseMemor()
{
	while (this->snake.pHead != NULL)
	{
		Node* temp = new Node;
		temp->pNext = this->snake.pHead;
		this->snake.pHead = temp->pNext->pNext;
		delete temp->pNext;
		temp->pNext = NULL;
		delete temp;
		temp = NULL;
	}
}