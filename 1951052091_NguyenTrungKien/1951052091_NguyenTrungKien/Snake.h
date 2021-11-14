#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
// create doubly link list
struct Node
{
	float posX;
	float posY;
	struct Node* pNext;
	struct Node* pPrevious;
};
typedef struct Node Node;
struct List
{
	Node* pHead;
	Node* pTail;
};
typedef struct List List;

class Snake
{
public:
	Snake();
	Node* createNode(const float& posX, const float& posY);
	void addHead(Node* node);
	void addTail(Node* node);
	void delTail();
	void createFirstSnakePlayer1(const string & linkSnakePlayer1);
	void createFirstSnakePlayer2(const string & linkSnakePlayer2);
	void controlSnakePlayer1(int& status, const string &linkSnakePlayer1);
	void controlSnakePlayer2(int & status, const string &linkSnakePlayer2);
	void moveLeft(const string & linkSnakePlayer);
	void moveRight(const string & linkSnakePlayer);
	void moveUp(const string & linkSnakePlayer);
	void moveDown(const string & linkSnakePlayer);
	bool causeCollisionSnake(RenderWindow& window, const string & linkSnakeplayer);
	bool causeCollisionTwoSnake(const string &linkSnakePlayer1, const Snake& snakePlayer2, const string & linkSnakePlayer2);
	void eatFoods(const int& status);
	List getPositonSnake()const;
	int count();
	void drawSnake(RenderWindow& window, Object& part);
	void releaseMemor();
private:
	List snake;
};

