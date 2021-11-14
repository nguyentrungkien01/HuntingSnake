///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/////								BAI TAP LON
/////						De tai: Game ran san moi (Version 1.0)
/////		Ho va ten: Nguyen Trung Kien
/////		Mssv: 1951052091
/////		Lop: DH19IT03
/////		Truong: Dai hoc Mo Thanh pho Ho Chi Minh
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


#include <SFML\Graphics.hpp>// use graphic library of sfml
#include <SFML/Audio.hpp>// use audio library of sfml
#include <iostream>// 1 small trick to check bug game (use cout to check bug)
#include <vector>// use to store array of objects, links of object in game(images, links of images in file .txt)
#include <fstream>// read - write file (account, links of images, score, name of players,....)
#include <Windows.h>// use to set speed of game (choose level)
#include <random>// location settings appear randomly foods, stars
#include <string>// string of characters setting (username, password, namePlayer, help, infor, .....)
#include "Object.h"
#include "Snake.h"

// link to audio library
#pragma comment (lib,"openal32.lib")

using namespace std;
using namespace sf;

// create rankAcc struct
struct rankAcc
{
	string name;
	int score;
};
typedef struct rankAcc RankAcc;

// define amount of objects (images in game)
#define AMOUNT_GRASSES 10
#define AMOUNT_FRAMES 4
#define AMOUNT_STONES 15
#define AMOUNT_GROUND 1
#define AMOUNT_SNAKES 5
#define AMOUNT_FOODS 25
#define AMOUNT_STARS 21
#define AMOUNT_SCORE_FRAMES 6
#define AMOUNT_MOVEMENT_BUTTONS 2
#define AMOUNT_CHOICES 10
#define AMOUNT_RANKS 8
#define AMOUNT_OPTIONS 6
#define AMOUNT_INFORMATIONS 2
#define AMOUNT_HELPS 4
#define AMOUNT_ACCOUNTS 13
#define AMOUNT_NAME_PLAYERS 4
#define AMOUNT_GAME_OVER 3
#define AMOUNT0_STUFF 13

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//						============================================== Start declaring functions in program =================================================
//_____ Declare setting data functions for objects_____
void setLink(vector<string>& nameLink, const string& link);
void setObj(vector<Object>& nameObj, const vector<string>& linkObj);
//				++++++++++++++++++++++++++++

//_____Processing collision snake with stones
bool checkCollisionStones(vector<Object> stones, Object & part);
//				++++++++++++++++++++++++++++

//_____Declare grapical display functions in game_____
void drawGround(RenderWindow& window, vector<Object>& ground);
void drawFrame(RenderWindow& window, vector<Object>& frame);
void drawStones(RenderWindow& window, vector<Object>& stones);
void drawGrasses(RenderWindow& window, vector<Object>& grasses);
void drawStuff(RenderWindow& window, vector<Object>& grasses);
void drawDecorateObj(RenderWindow& window, vector<Object>&stuff);
//				++++++++++++++++++++++++++++

//_____Declare functions of Score_____
void drawScoreSingle(RenderWindow& window, vector<Object>& scoreFrame, const string & namePlayer, Text text[]);
void drawScoreMulti(RenderWindow& window, vector<Object>& scoreFrame, const string & namePlayer1, const string & namePlayer2, Text text[]);
void setTextScoreSingleIngame(Text text[]);
void setTextScoreMultiIngame(Text text[]);
//					++++++++++++++++++++++++++++

//_____Declare supporting functions of score (convert type)_____
string convertToChar(const int& number);
string convertToStr(int number);
//			++++++++++++++++++++++++++++

//_____Declare functions of Menu_____
void drawOptionButtons(RenderWindow& window, vector<Object>&choices, Text textStar[], const int & amountText);
void decorateStartMenu(RenderWindow& window, vector<Object>&snakes, vector<Object>&choices, Text textStart[]);
int chooseOptions(RenderWindow& window,vector<Object>&choices, Text textStart[], const int & amountText, Mouse & mouse);
//				++++++++++++++++++++++++++++

//_____Declare functions of Rank_____
void drawBackgroundRank(RenderWindow& window, vector<Object>& ranks);
void setDataRank( RankAcc top[]);
void drawDataRank(RenderWindow& window, RankAcc top[], vector<Object>& ranks, Text& text);
bool backToMenu(RenderWindow& window, vector<Object>& ranks, Text& text, Mouse & mouse);
//				++++++++++++++++++++

//_____Declare functions of Option_____
void drawBackgroundOption(RenderWindow& window, vector<Object>& option, vector<Object>&snakes, Text text[]);
int setMenuOption(RenderWindow& window, Text text[], Mouse & mouse);
void drawMenuMode(RenderWindow& window, vector <Object>& option, Text text[]);
int setMode(RenderWindow& window, Text text[], Mouse& mouse);
void drawMenuLevel(RenderWindow& window, vector<Object>& option, Text text[]);
int setLevel(RenderWindow& window, Text text[], Mouse& mouse);
bool backFromOption(RenderWindow& window, Text text[], Mouse& mouse);
//			++++++++++++++++++++++++++++

//_____Declare functions of Information_____
void drawBackgroundInfor(RenderWindow& window, vector<Object>& infor);
string* setDataInfor();
void drawDataInfor(RenderWindow& window, Text text[], string* strData);
bool backFromInfor(RenderWindow& window, Text text[], Mouse &mouse);
//			++++++++++++++++++++++++++++

//_____Declare functions of Help_____
void drawBackgroundHelp(RenderWindow& window, vector<Object>& help, vector<Object>& movementButtons, Text text[]);
bool backFromHelp(RenderWindow& window, vector<Object>& hekp, Text text[], Mouse& mouse);
//				+++++++++++++++++++++

//_____Declare functions of Account_____
//					background
void drawBackgroundLogIn(RenderWindow& window, vector<Object>& account);
void drawBackgroundRegistration(RenderWindow& window, vector<Object>&account);
//				++++++++++++++++++++++
//					login
int clickLogin(vector <Object> & account, Mouse & mouse);
void drawUsernameLogin(RenderWindow& window, vector<Object>& account, Text text[], const string & username);
void drawPasswordLogin(RenderWindow& window, vector<Object>& account, Text text[], const string & password);
bool confirmLogin(RenderWindow& window, Text text[], Mouse & mouse);
bool checkConfirmLogin(const string & username, const string & password);
//				++++++++++++++++++++++++

//					regist
bool confirmSwitchToRegistration(RenderWindow& window, Text text[], Mouse& mouse);
void drawUsernameRegist(RenderWindow& window, vector<Object>& account, Text text[], const string & username);
void drawPasswordRegist(RenderWindow& window, vector<Object>& account, Text text[], const string & password);
void drawConfirmPasswordRegist(RenderWindow& window, vector<Object>& account, Text text[], const string & password);
bool confirmRegist(RenderWindow& window, Text text[], Mouse & mouse);
bool checkPassAndPassConfirm(const string & password, const string & passwordConfirm);
bool checkConfirmRegist(const string & username, const string & password, const string & passwordConfirm);
void writeNewAccountToFile(const string & username, const string & password);
bool checkBackToLogin(RenderWindow& window, Text text[], Mouse& mouse);
//				++++++++++++++++++++++++++

//_____Declare functions of Name of players_____
void drawNamePlayerSingle(RenderWindow& window, vector<Object>& namePlayer, Text text[], const string & namePlayerSingle);
void drawNamePlayerMulti(RenderWindow& window, vector<Object>& namePlayer, Text text[], const string & namePlayer1, const string & namePlayer2);
bool confirmEnterName(RenderWindow& window, Text text[], Mouse& mouse);
bool checkNamePlayer(const string & namePlayer);
void writeNameAndScorePlayerToFile(const string &namePlayer, const int & score);
//				++++++++++++++++++++++++++

//_____Declare functions of Game over_____
void drawGameOverSingle(RenderWindow& window, vector<Object>& gameOver, Text text[], const string & namePlayerSingle, const int & score);
void drawGameOverMulti(RenderWindow& window, vector<Object> & gameOver, Text text[], const string & namePlayer1, const string & namePlayer2, const int & score1, const int & score2);
bool confirmGameOver(RenderWindow& window, vector<Object>& gameOver, Mouse & mouse);
//				++++++++++++++++++++++++++

//____Declare functions of Sound_____
void setDataSounđ(SoundBuffer & buffer, Sound & sound, const string & linkSound, const float & volume);
//				++++++++++++++++++++++++++
//						============================================== finish declaring functions in program =================================================
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////   START MAIN   ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	RankAcc top[3];
	//			create array of object links
	vector <string> linkGrasses;
	vector <string> linkStones;
	vector <string> linkGround;
	vector <string> linkFrame;
	vector <string> linkSnakes;
	vector <string> linkStars;
	vector <string> linkFoods;
	vector <string> linkScoreFrame;
	vector <string> linkChoice;
	vector <string> linkRanks;
	vector <string> linkOption;
	vector <string> linkInfor;
	vector <string> linkHelp;
	vector <string> linkMovementButtons;
	vector <string> linkAccount;
	vector <string> linkNamePlayers;
	vector <string> linkGameOver;
	vector <string> linkStuff;
	//			creete object array
	vector <Object> grasses;
	vector <Object> stones;
	vector <Object> ground;
	vector <Object> frame;
	vector <Object> snakes;
	vector <Object> stars;
	vector <Object> foods;
	vector <Object> scoreFrame;
	vector<Object> choices;
	vector<Object> ranks;
	vector<Object>option;
	vector<Object> infor;
	vector <Object> help;
	vector<Object> movementButtons;
	vector <Object> account;
	vector <Object> namePlayers;
	vector <Object> gameover;
	vector <Object> stuff;
	//			create size of object array
	grasses.resize(AMOUNT_GRASSES);
	stones.resize(AMOUNT_STONES);
	ground.resize(AMOUNT_GROUND);
	frame.resize(AMOUNT_FRAMES);
	snakes.resize(AMOUNT_SNAKES);
	stars.resize(AMOUNT_STARS);
	foods.resize(AMOUNT_FOODS);
	scoreFrame.resize(AMOUNT_SCORE_FRAMES);
	choices.resize(AMOUNT_CHOICES);
	ranks.resize(AMOUNT_RANKS);
	option.resize(AMOUNT_OPTIONS);
	infor.resize(AMOUNT_INFORMATIONS);
	help.resize(AMOUNT_HELPS);
	movementButtons.resize(AMOUNT_MOVEMENT_BUTTONS);
	account.resize(AMOUNT_ACCOUNTS);
	namePlayers.resize(AMOUNT_NAME_PLAYERS);
	gameover.resize(AMOUNT_GAME_OVER);
	stuff.resize(AMOUNT0_STUFF);
	//			set data from file.txt for link object array
	setLink(linkGrasses, "links/linkGrasses.txt");
	setLink(linkStones, "links/linkStones.txt");
	setLink(linkGround, "links/linkGround.txt");
	setLink(linkFrame, "links/linkFrame.txt");
	setLink(linkSnakes, "links/linkSnakes.txt");
	setLink(linkStars, "links/linkStars.txt");
	setLink(linkFoods, "links/linkFoods.txt");
	setLink(linkScoreFrame, "links/linkScoreFrame.txt");
	setLink(linkChoice, "links/linkChoices.txt");
	setLink(linkRanks, "links/linkRank.txt");
	setLink(linkOption, "links/linkOption.txt");
	setLink(linkInfor, "links/linkInfor.txt");
	setLink(linkHelp, "links/linkHelp.txt");
	setLink(linkMovementButtons, "links/linkMovementButtons.txt");
	setLink(linkAccount, "links/linkAccount.txt");
	setLink(linkNamePlayers, "links/linkNamePlayers.txt");
	setLink(linkGameOver, "links/linkGameOver.txt");
	setLink(linkStuff, "links/linkStuff.txt");
	//			set data for object from link object arrayt
	setObj(grasses, linkGrasses);
	setObj(stones, linkStones);
	setObj(ground, linkGround);
	setObj(frame, linkFrame);
	setObj(snakes, linkSnakes);
	setObj(stars, linkStars);
	setObj(foods, linkFoods);
	setObj(scoreFrame, linkScoreFrame);
	setObj(choices, linkChoice);
	setObj(ranks, linkRanks);
	setObj(option, linkOption);
	setObj(infor, linkInfor);
	setObj(help, linkHelp);
	setObj(movementButtons, linkMovementButtons);
	setObj(account, linkAccount);
	setObj(namePlayers, linkNamePlayers);
	setObj(gameover, linkGameOver);
	setObj(stuff, linkStuff);
	//			create game window
	RenderWindow window(VideoMode(1920, 1080), "HuntingSnake", Style::Close | Style::Fullscreen);
	window.setFramerateLimit(100);
	

	//			create random positions
	random_device seed;
	uniform_int_distribution <int> randFrame(5, 100);
	uniform_real_distribution <float> randPosX(30.f, 1800.f);
	uniform_real_distribution <float> randPosY(20.f, 950.f);

	//			necesary variables in menu start
	Mouse mouse;
	Font font;
	int choose = -1;
	bool flagBack = false;
	int menuOption = -1;
	int flagRunOption = 0;
	int flagRunMode = 0;
	int flagRunLevel = 0;
	int speedGame = 30;
	int modeGame = 1;

	//			index of text in each part of the game (to avoid mislead)
	/*text start 0->6
	text ingame 7(single), 28->29(multiple)
	text rank 8
	text option 9 16
	text infor 17, 19
	text movementButtons 18
	text login 20,21
	text confirm Login 22
	text turn to regist 23
	text namePlayer single 30->31
	text namePlayer multi 32->35
	text namePlayer confirm 36
	text namePlayer ingame 37
	text gameover 38,39
	text back to login 40*/

	//			set data for text
	if (font.loadFromFile("font1.ttf"))
		cout << "font1.ttf successfully! " << endl;
	Text text[41];
	for (int i = 0; i < 41; i++)
	{
		text[i].setStyle(1);
		text[i].setFont(font);
	}
	setTextScoreSingleIngame(text);
	setTextScoreMultiIngame(text);

	//			create snake
	Object partPlayer1;
	Object partPlayer2;
	Snake snakeMainPlayer1;
	Snake snakeMainPlayer2;
	string linkSnakePlayer1 = "images/snakes/head_body_tail1.png";
	string linkSnakePlayer2 = "images/snakes/head_body_tail2.png";
	partPlayer1.setData(linkSnakePlayer1);
	partPlayer2.setData(linkSnakePlayer2);
	snakeMainPlayer1.createFirstSnakePlayer1(linkSnakePlayer1);
	snakeMainPlayer2.createFirstSnakePlayer2(linkSnakePlayer2);
	int statusPlayer1 = 1;
	int statusPlayer2 = 0;
	bool testSnakePlayer1;
	bool testSnakePlayer2;

	//			foods 
	for (int i = 0; i < AMOUNT_FOODS; i++)
		foods[i].setPosition(Vector2f(-100.f, -100.f));
	int countFoods = 0;
	float scaleFood = 1.f;
	int countEleFood = 0;
	float posXFood = randPosX(seed);
	float posYFood = randPosY(seed);

	//			star
	int countEleStars = 0;
	for (int i = 0; i < AMOUNT_STARS; i++)
		stars[i].setPosition(Vector2f(-100.f, -100.f));
	int countTimeAppear = 30;
	float posXStar = randPosX(seed);
	float posYStar = randPosY(seed);
	int flagStar = 0;
	float scaleStar = 1.f;

	//			score
	int scorePlayer1 = 0;
	int scorePlayer2 = 0;

	//			point login, regist
	account[10].setPosition(Vector2f(680.f, 370.f));
	account[10].setScale(0.5f, 0.5f);
	account[11].setPosition(Vector2f(710.f, 450.f));
	account[11].setScale(0.5f, 0.5f);

	//			log in acccount
	int flagClickLogin=-1;
	bool flagCheckConfirmLogin=false;
	string usernameLogin = "";
	string passwordLoginShow = "";
	string passwordLoginHide = "";

	//			resist new account
	bool flagConfirmSwitchToRegistration = false;
	int flagClickRegist =0;
	string usernameRegist = "";
	string passwordRegistShow = "";
	string passwordConfirmRegistShow = "";
	string passwordRegistHide = "";
	string passwordConfirmRegistHide = "";

	//			set namePlayer
	string namePlayerSingle = "";
	string namePlayerMulti1 = "";
	string namePlayerMulti2 = "";
	string namePlayerSingleWriteFile;
	string namePlayerMultiWriteFile1;
	string namePlayerMultiWriteFile2;
	int flagNamePlayer = 0;
	bool checkEnterNameSuccessful = false;

	//			game over
	bool flagGameOver = false;

	//			sound
	vector <SoundBuffer> buffer;
	vector <Sound> sound;
	buffer.resize(3);
	sound.resize(3);
	bool flagSoundBack = true;
	setDataSounđ(buffer[0], sound[0], "Firefly.wav", 50.f);
	sound[0].play();
	sound[0].setLoop(true);
	setDataSounđ(buffer[1], sound[1], "button press.wav", 70.f);
	setDataSounđ(buffer[2], sound[2], "snake_swallow.wav", 70.f);

	//			start game loop
	while (window.isOpen())
	{
		Event event;
		//		catch event
		while (window.pollEvent(event))
		{
			//		when press escape key on keyboard -> close window
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
				window.close();

			//		get character when press key on keyboard
			if (event.type == Event::TextEntered)
				if (event.text.unicode < 128)
				{
					int codeKey = event.text.unicode;
					//				 account
					if (!flagCheckConfirmLogin)
					{
						//		login (username, password)
						//	username
						if (flagConfirmSwitchToRegistration == false)
						{
							if (flagClickLogin == 0)
							{
								//press bacspace to delete character
								if (codeKey == 8 && usernameLogin.length() > 0)
									usernameLogin.pop_back();
								//press key(A->Z, a->z, 0.9)
								if ((codeKey >= 48 && codeKey <= 59) || (codeKey >= 65 && codeKey <= 90) || (codeKey >= 97 && codeKey <= 122))
									usernameLogin.push_back(static_cast<char>(event.text.unicode));
								//press tab (switch to password)
								if (codeKey == 9)
								{
									account[10].setPosition(Vector2f(680.f, 480.f));
									flagClickLogin = 1;
								}
							}
							//	password
							else
								if (flagClickLogin == 1)
								{
									//press bacspace to delete character
									if (codeKey == 8 && passwordLoginHide.length() > 0 && passwordLoginShow.length() > 0)
									{
										passwordLoginShow.pop_back();
										passwordLoginHide.pop_back();
									}
									//press key(A->Z, a->z, 0.9)
									if ((codeKey >= 48 && codeKey <= 59) || (codeKey >= 65 && codeKey <= 90) || (codeKey >= 97 && codeKey <= 122))
									{
										passwordLoginShow.push_back(static_cast<char>(event.text.unicode));
										passwordLoginHide.push_back('*');
									}
									//press tab (switch to username)
									if (codeKey == 9)
									{
										
										account[10].setPosition(Vector2f(680.f, 370.f));
										flagClickLogin = 0;
									}
								}
						}
						//		regist (username, password, confirm password)
						else
						{
							//		create username
							if (flagClickRegist == 0)
							{
								//press bacspace to delete character
								if (codeKey == 8 && usernameRegist.length() > 0)
									usernameRegist.pop_back();
								//press key(A->Z, a->z, 0.9)
								if ((codeKey >= 48 && codeKey <= 59) || (codeKey >= 65 && codeKey <= 90) || (codeKey >= 97 && codeKey <= 122))
									usernameRegist.push_back(static_cast<char>(event.text.unicode));
								//press tab (switch to password)
								if (codeKey == 9)
								{
									account[11].setPosition(Vector2f(710.f, 535.f));
									flagClickRegist = 1;
								}
							}
							//		create password
							else
								if (flagClickRegist == 1)
								{
									//press bacspace to delete character
									if (codeKey == 8 && passwordRegistHide.length() > 0 && passwordRegistShow.length() > 0)
									{
										passwordRegistShow.pop_back();
										passwordRegistHide.pop_back();
									}
									//press key(A->Z, a->z, 0.9)
									if ((codeKey >= 48 && codeKey <= 59) || (codeKey >= 65 && codeKey <= 90) || (codeKey >= 97 && codeKey <= 122))
									{
										passwordRegistShow.push_back(static_cast<char>(event.text.unicode));
										passwordRegistHide.push_back('*');
									}
									//press tab (switch to confirm password)
									if (codeKey == 9)
									{
										account[11].setPosition(Vector2f(710.f, 630.f));
										flagClickRegist = 2;
									}
								}
							//		confirm password
								else
									if (flagClickRegist == 2)
									{
										//press bacspace to delete character
										if (codeKey == 8 && passwordConfirmRegistHide.length() > 0 && passwordConfirmRegistShow.length() > 0)
										{
											passwordConfirmRegistShow.pop_back();
											passwordConfirmRegistHide.pop_back();
										}
										//presss key (A->Z, a->z, 0->9)
										if ((codeKey >= 48 && codeKey <= 59) || (codeKey >= 65 && codeKey <= 90) || (codeKey >= 97 && codeKey <= 122))
										{
											passwordConfirmRegistShow.push_back(static_cast<char>(event.text.unicode));
											passwordConfirmRegistHide.push_back('*');
										}
										//press tab (switch to username)
										if (codeKey == 9)
										{
											account[11].setPosition(Vector2f(710.f, 450.f));
											flagClickRegist = 0;
										}
									}
						}
					}
					//				name player
					else
					{
						//		 single mode
						if (modeGame != 0)
						{
							//press bacspace to delete character
							if (codeKey == 8 && namePlayerSingle.length() > 0)
								namePlayerSingle.pop_back();
							//presss key (A->Z, a->z, 0->9)
							if ((codeKey >= 48 && codeKey <= 59) || (codeKey >= 65 && codeKey <= 90) || (codeKey >= 97 && codeKey <= 122))
								namePlayerSingle.push_back(static_cast<char>(event.text.unicode));
						}
						//		 multi mode
						else
						{
							//		first player
							if (flagNamePlayer == 0)
							{
								//press bacspace to delete character
								if (codeKey == 8 && namePlayerMulti1.length() > 0)
									namePlayerMulti1.pop_back();
								//presss key (A->Z, a->z, 0->9)
								if ((codeKey >= 48 && codeKey <= 59) || (codeKey >= 65 && codeKey <= 90) || (codeKey >= 97 && codeKey <= 122))
									namePlayerMulti1.push_back(static_cast<char>(event.text.unicode));
								//press tab (switch to second player)
								if (codeKey == 9)
									flagNamePlayer = 1;
							}
							//		second player
							else
							{
								//press bacspace to delete character
								if (codeKey == 8 && namePlayerMulti2.length() > 0)
									namePlayerMulti2.pop_back();
								//presss key (A->Z, a->z, 0->9)
								if ((codeKey >= 48 && codeKey <= 59) || (codeKey >= 65 && codeKey <= 90) || (codeKey >= 97 && codeKey <= 122))
									namePlayerMulti2.push_back(static_cast<char>(event.text.unicode));
								//press tab (switch to first player)
								if (codeKey == 9)
									flagNamePlayer = 0;
							}
						}
					}
				}
		}

		//		 login mode 
		//	log in fail
		if (!flagCheckConfirmLogin)
		{
			window.clear();
			if (!flagConfirmSwitchToRegistration)
			{
				drawBackgroundLogIn(window, account);
				//	when user press left button of mouse in username box -> user can fill username 
				if (flagClickLogin == -1)
					flagClickLogin = clickLogin(account, mouse);
				// click on username
				if (flagClickLogin == 0)
				{
					account[4].setScale(1.1f, 1.1f);
					account[4].setPosition(Vector2f(780.f, 490.f));
					account[4].draw(window);
					drawPasswordLogin(window, account, text, passwordLoginHide);
					account[4].setPosition(Vector2f(780.f, 385.f));
					account[4].draw(window);
					drawUsernameLogin(window, account, text, usernameLogin);
				}
				else 
					//	click on password
					if (flagClickLogin == 1)
					{
						account[4].setScale(1.1f, 1.1f);
						account[4].setPosition(Vector2f(780.f, 385.f));
						account[4].draw(window);
						drawUsernameLogin(window, account, text, usernameLogin);
						account[4].setPosition(Vector2f(780.f, 490.f));
						account[4].draw(window);
						drawPasswordLogin(window, account, text, passwordLoginHide);
					}
				//	check user click on login button
				if (confirmLogin(window, text, mouse))
					flagCheckConfirmLogin = checkConfirmLogin(usernameLogin, passwordLoginShow);
				//	check user click  on regist button
				flagConfirmSwitchToRegistration = confirmSwitchToRegistration(window, text, mouse);
				if (flagConfirmSwitchToRegistration||flagCheckConfirmLogin)
					sound[1].play();
				account[10].draw(window);
			}
			//	when user click on regist -> turn over regist mode 
			if (flagConfirmSwitchToRegistration)
			{
				drawBackgroundRegistration(window, account);
				// click to fill new account
				drawUsernameRegist(window, account, text, usernameRegist);
				drawPasswordRegist(window, account, text, passwordRegistHide);
				drawConfirmPasswordRegist(window, account, text, passwordConfirmRegistHide);
				// click to confirm create new account
				//	when fill correctly -> write new accoutn to file -> turn over log in mode
				if (confirmRegist(window, text, mouse))
					if (checkConfirmRegist(usernameRegist, passwordRegistShow, passwordConfirmRegistShow))
					{
						writeNewAccountToFile(usernameRegist, passwordRegistShow);
						flagConfirmSwitchToRegistration = false;
						sound[1].play();
					}
				if (checkBackToLogin(window, text, mouse))
				{
					flagConfirmSwitchToRegistration = false;
					sound[1].play();
				}
				account[11].draw(window);
			}
			window.display();
			if (flagCheckConfirmLogin)
				sound[1].play();
		}
		//	log in successful
		else
		{
			// not finish game 
			if (!flagGameOver)
			{
				// after user click on start button
				if (choose == 0)
					if (checkEnterNameSuccessful)
					{
						// control snake (single mode) , first snake (multi mode)
						if (statusPlayer1 == 0)
							snakeMainPlayer1.moveLeft(linkSnakePlayer1);
						else
							if (statusPlayer1 == 1)
								snakeMainPlayer1.moveRight(linkSnakePlayer1);
							else
								if (statusPlayer1 == 2)
									snakeMainPlayer1.moveUp(linkSnakePlayer1);
								else
									snakeMainPlayer1.moveDown(linkSnakePlayer1);
						// control second snake (multi mode)
						if (modeGame == 0)
							if (statusPlayer2 == 0)
								snakeMainPlayer2.moveLeft(linkSnakePlayer2);
							else
								if (statusPlayer2 == 1)
									snakeMainPlayer2.moveRight(linkSnakePlayer2);
								else
									if (statusPlayer2 == 2)
										snakeMainPlayer2.moveUp(linkSnakePlayer2);
									else
										snakeMainPlayer2.moveDown(linkSnakePlayer2);

						// check snake collion
						testSnakePlayer1 = snakeMainPlayer1.causeCollisionSnake(window, linkSnakePlayer1);
						testSnakePlayer2 = snakeMainPlayer2.causeCollisionSnake(window, linkSnakePlayer2);
						// multi mode
						if (modeGame == 0)
						{
							// when first snake, second snake collide wall, two snakes collide, game over flag turn on
							if (testSnakePlayer1 || testSnakePlayer2 || snakeMainPlayer1.causeCollisionTwoSnake(linkSnakePlayer1, snakeMainPlayer2, linkSnakePlayer2) ||
								checkCollisionStones(stones, partPlayer1) || checkCollisionStones(stones, partPlayer2))
								flagGameOver = true;
							if (partPlayer1.causeCollisionObj(grasses[3]) || partPlayer1.causeCollisionObj(stuff[3])|| partPlayer2.causeCollisionObj(grasses[3]) ||
								partPlayer2.causeCollisionObj(stuff[3]))
								flagGameOver = true;
						}
						else
						{
							// single mode
							// when snake collide wall, game over flag turn on
							if (testSnakePlayer1 || checkCollisionStones(stones, partPlayer1))
								flagGameOver = true;
							if (partPlayer1.causeCollisionObj(grasses[3]) || partPlayer1.causeCollisionObj(stuff[3]))
								flagGameOver = true;
						}
						if (flagGameOver)
							Sleep(100);
						//	text for writting score 
						//single
						if (modeGame != 0)
							text[7].setString(convertToStr(scorePlayer1));
						//multi
						else
						{
							text[28].setString(convertToStr(scorePlayer1));
							text[29].setString(convertToStr(scorePlayer2));
						}

						//	check status of the snake for running direction of snake
						snakeMainPlayer1.controlSnakePlayer1(statusPlayer1, linkSnakePlayer1);
						if (flagRunMode == 0)
							snakeMainPlayer2.controlSnakePlayer2(statusPlayer2, linkSnakePlayer2);

						//	food
						while (checkCollisionStones(stones, foods[countEleFood])|| foods[countEleFood].causeCollisionObj(grasses[3]) || foods[countEleFood].causeCollisionObj(stuff[3]))
						{
							posXFood = randPosX(seed);
							posYFood = randPosY(seed);
							foods[countEleFood].setPosition(Vector2f(posXFood, posYFood));
						}
						foods[countEleFood].setPosition(Vector2f(posXFood, posYFood));
						foods[countEleFood].setScale(scaleFood, scaleFood);

						//	create effect zoom in, zoom out food
						if (scaleFood < 1.1)
							scaleFood += 0.05f;
						else
							scaleFood -= 0.05f;
						// check eat food status of snake (single), first snake(multi)
						if (foods[countEleFood].causeCollisionObj(partPlayer1))
						{
							sound[2].play();
							//increase score (single), score first player (multi) 
							scorePlayer1++;
							//increse length snake
							snakeMainPlayer1.eatFoods(statusPlayer1);
							// switch to new food
							countEleFood++;
							if (countEleFood > 24)
							{
								for (int i = 0; i < AMOUNT_FOODS; i++)
									foods[i].setPosition(Vector2f(-100.f, -100.f));
								countEleFood = 0;
							}
							//create position of new food
							posXFood = randPosX(seed);
							posYFood = randPosY(seed);
						}
						//	check status of the snake for running direction of second snake (multi)
						if (modeGame == 0)
							if (foods[countEleFood].causeCollisionObj(partPlayer2))
							{
								sound[2].play();
								//in crease score second player
								scorePlayer2++;
								//increse length snake
								snakeMainPlayer2.eatFoods(statusPlayer2);
								// switch to new food
								countEleFood++;
								if (countEleFood > 24)
								{
									for (int i = 0; i < AMOUNT_FOODS; i++)
										foods[i].setPosition(Vector2f(-100.f, -100.f));
									countEleFood = 0;
								}
								//create position of new food
								posXFood = randPosX(seed);
								posYFood = randPosY(seed);

							}

						// star
						// create time to appearance of star
						if ((scorePlayer1 % 10 == 0 && scorePlayer1 != 0) || (scorePlayer2 % 10 == 0 && scorePlayer2 != 0))
						{
							while (checkCollisionStones(stones, stars[countEleStars])||stars[countEleStars].causeCollisionObj(grasses[3])||stars[countEleStars].causeCollisionObj(stuff[3]))
							{
								posXStar = randPosX(seed);
								posXStar = randPosY(seed);
								stars[countEleStars].setPosition(Vector2f(posXStar, posYStar));
								stars[countEleStars].setScale(scaleStar, scaleStar);
							}
							stars[countEleStars].setPosition(Vector2f(posXStar, posYStar));
							stars[countEleStars].setScale(scaleStar, scaleStar);
							flagStar = 1;
						}
						//	create effect zoom in, zoom out star
						if (scaleStar < 1.1)
							scaleStar += 0.05f;
						else
							scaleStar -= 0.05f;
						if (flagStar == 1)
							countTimeAppear--;
						if (countTimeAppear == 0)
						{
							stars[countEleStars].setPosition(Vector2f(-100.f, -100.f));
							countTimeAppear = 30;
							flagStar = 0;
						}
						// check eat food status of snake (single), first snake(multi)
						if (stars[countEleStars].causeCollisionObj(partPlayer1))
						{
							sound[2].play();
							countEleStars++;
							//in crease score player (the sooner you eat the higher the score)
							scorePlayer1 += countTimeAppear / 10;
							if (countEleStars > 20)
							{
								for (int i = 0; i < AMOUNT_STARS; i++)
									stars[i].setPosition(Vector2f(-100.f, -100.f));
								countEleStars = 0;
							}
						}
						else
							//	check status of the snake for running direction of second snake (multi)
							if (stars[countEleStars].causeCollisionObj(partPlayer2) && modeGame == 0)
							{
								sound[2].play();
								countEleStars++;
								//in crease score second player (the sooner you eat the higher the score)
								scorePlayer2 += countTimeAppear / 10;
								if (countEleStars > 20)
								{
									for (int i = 0; i < AMOUNT_STARS; i++)
										stars[i].setPosition(Vector2f(-100.f, -100.f));
									countEleStars = 0;
								}

							}
					}

				// start menu
				window.clear();
				// when choose not yet, continue display start menu
				if (choose == -1)
				{
					drawOptionButtons(window, choices, text, 4);
					decorateStartMenu(window, snakes, choices, text);
					choose = chooseOptions(window, choices, text, 4, mouse);
					//play sound when click button
					if (choose != -1)
					{
						flagSoundBack = true;
						sound[1].play();
					}
				}

				// case of menu
				switch (choose)
				{
					//							 start game
				case 0:
					if (!checkEnterNameSuccessful)
					{
						//	multi
						if (modeGame == 0)
						{
							// fill name player first player, second player
							drawNamePlayerMulti(window, namePlayers, text, namePlayerMulti1, namePlayerMulti2);
							if (confirmEnterName(window, text, mouse))
								// check nameplayer
								if (namePlayerMulti1 != namePlayerMulti2)
									if (checkNamePlayer(namePlayerMulti1) && checkNamePlayer(namePlayerMulti2))
									{
										namePlayerMultiWriteFile1 = namePlayerMulti1;
										namePlayerMultiWriteFile2 = namePlayerMulti2;
										checkEnterNameSuccessful = true;
									}
						}
						// single 
						else
						{
							drawNamePlayerSingle(window, namePlayers, text, namePlayerSingle);
							if (confirmEnterName(window, text, mouse))
								//check nam player
								if (checkNamePlayer(namePlayerSingle))
								{
									namePlayerSingleWriteFile = namePlayerSingle;
									checkEnterNameSuccessful = true;
								}
						}
						flagBack = false;
					}
					//name player correct -> start game
					if (checkEnterNameSuccessful)
					{
						//display background ingame
						drawGround(window, ground);
						drawGrasses(window, grasses);
						drawFrame(window, frame);
						drawStones(window, stones);
						drawStuff(window, grasses);
						drawDecorateObj(window, stuff);
						// display frame of score 
						if (modeGame != 0)
							drawScoreSingle(window, scoreFrame, namePlayerSingleWriteFile, text);
						else
							drawScoreMulti(window, scoreFrame, namePlayerMultiWriteFile1, namePlayerMultiWriteFile2, text);
						//display food va star
						foods[countEleFood].draw(window);
						stars[countEleStars].draw(window);
						//display snake
						snakeMainPlayer1.drawSnake(window, partPlayer1);
						if (modeGame == 0)
							snakeMainPlayer2.drawSnake(window, partPlayer2);
						//display score
						if (modeGame != 0)
							window.draw(text[7]);
						else
						{
							window.draw(text[28]);
							window.draw(text[29]);
						}
						//speed game(level)
						Sleep(speedGame);
						flagBack = false;
					}
					break;

					//						 rank
				case 1:
					//display rank
					drawBackgroundRank(window, ranks);
					setDataRank(top);
					drawDataRank(window, top, ranks, text[8]);
					//	confirm back to menu
					flagBack = backToMenu(window, ranks, text[8], mouse);
					break;

					//						option
				case 2:
					//display option
					drawBackgroundOption(window, option, snakes, text);
					menuOption = setMenuOption(window, text, mouse);
					// choose level , mode game
					//maintain display option table of option by sign of flag
					if (flagRunOption == 1)
						menuOption = 1;
					if (flagRunOption == -1)
						menuOption = 0;
					//	mode game
					if (menuOption == 1)
					{
						//display option in mode
						drawMenuMode(window, option, text);
						flagRunMode = setMode(window, text, mouse);
						// switch to multi mode
						if (flagRunMode == 0)
							modeGame = 0;
						//switch to single mode
						if (flagRunMode == 1)
							modeGame = 1;
						// turn on sigh of mode
						flagRunOption = 1;
						// when user have already choose mode, turn off mode table
						if (flagRunMode == 0 || flagRunMode == 1)
						{
							sound[1].play();
							flagRunOption = 0;
						}
					}
					//	level
					if (menuOption == 0)
					{
						//display option in level
						drawMenuLevel(window, option, text);
						flagRunLevel = setLevel(window, text, mouse);
						// switch to level normal
						if (flagRunLevel == 0)
							speedGame = 30;
						//switch to level hard
						if (flagRunLevel == 1)
							speedGame = 20;
						//switch to level nightmare
						if (flagRunLevel == 2)
							speedGame = 10;
						// turn on sign of level
						flagRunOption = -1;
						// when user have already choose level, turn off level table
						if (flagRunLevel == 0 || flagRunLevel == 1 || flagRunLevel == 2)
						{
							sound[1].play();
							flagRunOption = 0;
						}
					}
					// confirm back to menu
					flagBack = backFromOption(window, text, mouse);
					break;

					//						exit
				case 3:
					window.close();
					break;

					//						help
				case 4:
					drawBackgroundInfor(window, infor);
					drawDataInfor(window, text, setDataInfor());
					//confirm back to menu
					flagBack = backFromInfor(window, text, mouse);
					break;

					//						infor
				case 5:
					drawBackgroundHelp(window, help, movementButtons, text);
					//confirm back to menu
					flagBack = backFromHelp(window, help, text, mouse);
					break;
				}

				//after confirm back to menu, turn on sign of menu
				if (flagBack == true)
				{
					if (flagSoundBack)
					{
						sound[1].play();
						flagSoundBack = false;
					}
					choose = -1;
				}
				window.display();
			}
			//game over
			else
			{
				window.clear();
				//display score table
				if (modeGame != 0)
					drawGameOverSingle(window, gameover, text, namePlayerSingleWriteFile, scorePlayer1);
				else
					drawGameOverMulti(window, gameover, text, namePlayerMultiWriteFile1, namePlayerMultiWriteFile2, scorePlayer1, scorePlayer2);
				// confirm back to menu
				if (confirmGameOver(window, gameover, mouse))
				{
					sound[1].play();
					// write information of player to file
					if (modeGame != 0)
						writeNameAndScorePlayerToFile(namePlayerSingleWriteFile, scorePlayer1);
					else
					{
						writeNameAndScorePlayerToFile(namePlayerMultiWriteFile1, scorePlayer1);
						writeNameAndScorePlayerToFile(namePlayerMultiWriteFile2, scorePlayer2);
					}

					// set data again
					flagGameOver = false;
					choose = -1;
					// snake
					snakeMainPlayer1.releaseMemor();
					snakeMainPlayer2.releaseMemor();
					snakeMainPlayer1.createFirstSnakePlayer1(linkSnakePlayer1);
					snakeMainPlayer2.createFirstSnakePlayer2(linkSnakePlayer2);
					statusPlayer1 = 1;
					statusPlayer2 = 0;
					// name, flag mode game, score
					flagNamePlayer = 0;
					scorePlayer1 = 0;
					scorePlayer2 = 0;
					menuOption = -1;
					flagRunOption = 0;
					flagRunMode = 0;
					flagRunLevel = 0;
					speedGame = 30;
					namePlayerSingle = "";
					namePlayerMulti1 = "";
					namePlayerMulti2 = "";
					checkEnterNameSuccessful = false;
				}
				window.display();
			}
		}
	}
	// release memory
	snakeMainPlayer1.releaseMemor();
	snakeMainPlayer2.releaseMemor();
//	system("pause");
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////  END MAIN  ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//						============================================== Start processing the functions declared above    =================================================
//_____Processing setting data functions for Object_____
void setLink(vector<string>& nameLink, const string& link)
{
	ifstream fileIn;
	fileIn.open(link, ios_base::in);
	while (!fileIn.eof())
	{
		string linkObj;
		rewind(stdin);
		getline(fileIn, linkObj);
		nameLink.push_back(linkObj);
		cout << linkObj << "  successfully! " << endl;
		if (fileIn.eof())
			break;
	}
	fileIn.close();
}
void setObj(vector<Object>& nameObj, const vector<string>& linkObj)
{
	for (int i = 0; i < nameObj.size(); i++)
		nameObj[i].setData(linkObj[i]);
}
//				++++++++++++++++++++

//_____Processing graphical display In game_____
void drawGround(RenderWindow& window, vector<Object>& ground)
{
	float posX = 0;
	float posY = 0;
	while (posY <= 1080)
	{
		while (posX <= window.getSize().x)
		{
			ground[0].setPosition(Vector2f(posX, posY));
			posX += 110.f;
			ground[0].draw(window);
		}
		posX = 0;
		posY += 140.f;
	}
}
void drawFrame(RenderWindow& window, vector<Object>& frame)
{
	float posX = -10;
	float posY = -20;
	int count = 0;
	// bien tren, duoi
	while (posX <= window.getSize().x)
	{
		frame[0].setScale(0.7f, 0.7f);
		frame[0].setPosition(Vector2f(posX, posY));
		frame[0].draw(window);
		frame[0].setPosition(Vector2f(posX, window.getSize().y - 60.f));
		frame[0].draw(window);
		posX += 50.f;

	}
	//bien trai, phai
	posX = -10;
	while (posY <= window.getSize().y)
	{
		frame[0].setScale(0.6f, 0.6f);
		frame[0].setPosition(Vector2f(posX, posY));
		frame[0].draw(window);
		frame[0].setPosition(Vector2f(window.getSize().x - 60.f, posY));
		frame[0].draw(window);
		posY += 52.f;

	}

}
void drawStones(RenderWindow& window, vector<Object>& stones)
{
	//stone1
	stones[0].setScale(0.5f, 0.5f);
	stones[0].setPosition(Vector2f(180.f, window.getSize().y - 950.f));
	stones[0].draw(window);
	stones[0].setScale(0.3f, 0.3f);
	stones[0].setPosition(Vector2f(190.f, window.getSize().y - 940.f));

	stones[1].setScale(0.5f, 0.5f);
	stones[1].setPosition(Vector2f(220.f, window.getSize().y - 950.f));
	stones[1].draw(window);
	stones[1].setScale(0.3f, 0.3f);
	stones[1].setPosition(Vector2f(230.f, window.getSize().y - 940.f));

	stones[2].setScale(0.5f, 0.5f);
	stones[2].setPosition(Vector2f(200.f, window.getSize().y - 930.f));
	stones[2].draw(window);
	stones[2].setScale(0.3f, 0.3f);
	stones[2].setPosition(Vector2f(210.f, window.getSize().y - 920.f));

	stones[3].setScale(1.2f, 1.1f);
	stones[3].setPosition(Vector2f(300.f, window.getSize().y - 720.f));
	stones[3].draw(window);
	stones[3].setScale(1.f, 0.9f);
	stones[3].setPosition(Vector2f(310.f, window.getSize().y - 710.f));
	
	//stone2
	stones[4].setScale(1.f, 1.f);
	stones[4].setPosition(Vector2f(1300.f, window.getSize().y - 300.f));
	stones[4].draw(window);

	//stone3
	stones[5].setScale(1.f, 1.f);
	stones[5].setPosition(Vector2f(100.f, window.getSize().y - 1200.f));
	stones[5].draw(window);
	stones[5].setScale(0.8f, 0.8f);
	stones[5].setPosition(Vector2f(115.f, window.getSize().y - 1185.f));

	stones[6].setScale(1.f, 1.f);
	stones[6].setPosition(Vector2f(50.f, window.getSize().y - 300.f));
	stones[6].draw(window);
	stones[6].setScale(0.8f, 0.8f);
	stones[6].setPosition(Vector2f(65.f, window.getSize().y - 285.f));

	//stone4
	stones[7].setScale(1.f, 1.f);
	stones[7].setPosition(Vector2f(1150.f, window.getSize().y - 1060.f));
	stones[7].draw(window);
	stones[7].setScale(0.7f, 0.7f);
	stones[7].setPosition(Vector2f(1175.f, window.getSize().y - 1035.f));

	stones[8].setScale(1.f, 1.f);
	stones[8].setPosition(Vector2f(1137.f, window.getSize().y - 850.f));
	stones[8].draw(window);
	stones[8].setScale(0.7f, 0.7f);
	stones[8].setPosition(Vector2f(1162.f, window.getSize().y - 825.f));

	//stone5
	stones[9].setScale(0.5f, 0.5f);
	stones[9].setPosition(Vector2f(950.f, window.getSize().y - 850.f));
	stones[9].draw(window);
	stones[9].setScale(0.3f, 0.3f);
	stones[9].setPosition(Vector2f(960.f, window.getSize().y - 840.f));

	stones[10].setScale(0.5f, 0.5f);
	stones[10].setPosition(Vector2f(1130.f, window.getSize().y - 100.f));
	stones[10].draw(window);
	stones[10].setScale(0.3f, 0.3f);
	stones[10].setPosition(Vector2f(1140.f, window.getSize().y - 90.f));

	//stone6
	stones[11].setScale(1.3f, 1.f);
	stones[11].setPosition(Vector2f(200.f, window.getSize().y - 350.f));
	stones[11].draw(window);
	stones[11].setScale(1.1f, 0.8f);
	stones[11].setPosition(Vector2f(215.f, window.getSize().y - 335.f));

	//stone temp
	stones[12].setScale(0.9f, 0.9f);
	stones[12].setPosition(Vector2f(1330.f, window.getSize().y - 150.f));

	stones[13].setScale(0.7f, 0.7f);
	stones[13].setPosition(Vector2f(1430.f, window.getSize().y - 210.f));

	stones[14].setScale(0.3f, 0.5f);
	stones[14].setPosition(Vector2f(1530.f, window.getSize().y - 240.f));
}
void drawGrasses(RenderWindow& window, vector<Object>& grasses)
{
	float posX = 0;
	float posY = -20;
	while (posX <= window.getSize().x)
	{
		grasses[2].setPosition(Vector2f(posX, posY));
		posX += 140.f;
		grasses[2].draw(window);
	}
	posX = 0;
	posY = 500;
	grasses[7].setPosition(Vector2f(posX - 70.f, posY + 45.f));
	grasses[7].draw(window);
	grasses[7].setPosition(Vector2f(posX - 70.f, posY - 45.f));
	grasses[7].draw(window);
	while (posX < window.getSize().x)
	{
		grasses[7].setPosition(Vector2f(posX, posY));
		grasses[7].draw(window);
		grasses[7].setPosition(Vector2f(posX + 75, posY + 45));
		grasses[7].draw(window);
		grasses[7].setPosition(Vector2f(posX + 75, posY - 45));
		grasses[7].draw(window);
		posX += 150.f;
	}

	posX = 400;
	posY = 800;
	while (posX < 600)
	{
		grasses[8].setPosition(Vector2f(posX, posY));
		grasses[8].draw(window);
		posX += 75.f;
		posY -= 45;
	}
	posX = 475;
	posY = 845;
	while (posX < 650)
	{
		grasses[8].setPosition(Vector2f(posX, posY));
		grasses[8].draw(window);
		posX += 75.f;
		posY -= 45;
	}
	posX = 550;
	posY = 890;
	while (posX < 710)
	{
		grasses[8].setPosition(Vector2f(posX, posY));
		grasses[8].draw(window);
		posX += 75.f;
		posY -= 45;
	}

	posX = 850;
	posY = 800;
	while (posX < 1050)
	{
		grasses[5].setPosition(Vector2f(posX, posY));
		grasses[5].draw(window);
		posX += 75.f;
		posY -= 45;
	}
	posX = 925;
	posY = 845;
	while (posX < 1125)
	{
		grasses[5].setPosition(Vector2f(posX, posY));
		grasses[5].draw(window);
		posX += 75.f;
		posY -= 45;
	}
	posX = 1000;
	posY = 890;
	while (posX < 1200)
	{
		grasses[5].setPosition(Vector2f(posX, posY));
		grasses[5].draw(window);
		posX += 75.f;
		posY -= 45;
	}


	posX = 400;
	posY = 100;
	while (posY <= 300)
	{
		grasses[9].setPosition(Vector2f(posX, posY));
		grasses[9].draw(window);
		posY += 90;
	}
	posX = 550;
	posY = 100;
	while (posY <= 300)
	{
		grasses[9].setPosition(Vector2f(posX, posY));
		grasses[9].draw(window);
		posY += 90;
	}
	posX = 700;
	posY = 100;
	while (posY <= 300)
	{
		grasses[9].setPosition(Vector2f(posX, posY));
		grasses[9].draw(window);
		posY += 90;
	}
	posX = 850;
	posY = 100;
	while (posY <= 300)
	{
		grasses[9].setPosition(Vector2f(posX, posY));
		grasses[9].draw(window);
		posY += 90;
	}

	grasses[1].setPosition(Vector2f(1200.f, 270.f));
	grasses[1].draw(window);
	grasses[0].setPosition(Vector2f(210.f, window.getSize().y - 360.f));
	grasses[0].draw(window);

	grasses[3].setPosition(Vector2f(1500.f, 170.f));
	grasses[3].setScale(0.5f, 0.9f);
	grasses[3].draw(window);
	grasses[3].setPosition(Vector2f(1570.f, 240.f));
	grasses[3].setScale(0.3f, 0.4f);

}
void drawStuff(RenderWindow& window, vector<Object>& grasses)
{
	grasses[4].setScale(1.f, 1.f);
	grasses[4].setPosition(Vector2f(1150, 220));
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(1200, 50));
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(300, 50));
	grasses[4].setScale(0.8f, 0.7f);
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(340, 50));
	grasses[4].setScale(0.8f, 0.9f);
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(380, 50));
	grasses[4].setScale(0.8f, 0.7f);
	grasses[4].draw(window);
	grasses[4].setScale(0.8f, 0.7f);
	grasses[4].setPosition(Vector2f(380, 800));
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(100, 800));
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(120, 800));
	grasses[4].setScale(1.f, 1.f);
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(1700, 850));
	grasses[4].setScale(1.f, 1.f);
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(1750, 850));
	grasses[4].setScale(0.7f, 0.8f);
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(90, 820));
	grasses[4].setScale(0.6f, 0.8f);
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(800, 850));
	grasses[4].setScale(0.7f, 0.9f);
	grasses[4].draw(window);
	grasses[4].setPosition(Vector2f(1600, 600));
	grasses[4].setScale(0.7f, 0.9f);
	grasses[4].draw(window);
}
void drawDecorateObj(RenderWindow& window, vector<Object>&stuff)
{
	stuff[0].setScale(0.5f, 0.5f);
	stuff[0].setPosition(Vector2f(100.f, 300.f));
	stuff[0].draw(window);
	stuff[0].setScale(0.7f, 0.7f);
	stuff[0].setPosition(Vector2f(850.f, 900.f));
	stuff[0].draw(window);

	stuff[1].setScale(0.7f, 0.7f);
	stuff[1].setPosition(Vector2f(1290.f, 210.f));
	stuff[1].draw(window);

	stuff[2].setScale(0.5f, 0.5f);
	stuff[2].setPosition(Vector2f(50.f, 900.f));
	stuff[2].draw(window);
	stuff[2].setScale(0.8f, 0.8f);
	stuff[2].setPosition(Vector2f(1300.f, 780.f));
	stuff[2].draw(window);

	stuff[3].setScale(0.8f, 0.8f);
	stuff[3].setPosition(Vector2f(500.f, 600.f));
	stuff[3].draw(window);

	stuff[4].setScale(0.5f, 0.5f);
	stuff[4].setPosition(Vector2f(0.f, 760.f));
	stuff[4].draw(window);

	stuff[5].setScale(0.8f, 0.8f);
	stuff[5].setPosition(Vector2f(1000.f, 350.f));
	stuff[5].draw(window);

	stuff[6].setScale(0.3f, 0.3f);
	stuff[6].setPosition(Vector2f(-10.f, 400.f));
	stuff[6].draw(window);
	stuff[6].setPosition(Vector2f(-10.f, 1300.f));
	stuff[6].draw(window);

	stuff[6].setPosition(Vector2f(1730.f, 800.f));
	stuff[6].draw(window);
	stuff[6].setPosition(Vector2f(1750.f, 800.f));
	stuff[6].draw(window);
	stuff[6].setPosition(Vector2f(1720.f, 820.f));
	stuff[6].draw(window);

	stuff[6].setPosition(Vector2f(1200.f, 600.f));
	stuff[6].draw(window);
	stuff[6].setPosition(Vector2f(1300.f, 400.f));
	stuff[6].draw(window);
	stuff[6].setPosition(Vector2f(700.f, 200.f));
	stuff[6].draw(window);
	stuff[6].setPosition(Vector2f(200.f, 100.f));
	stuff[6].draw(window);

	stuff[7].setScale(0.5f, 0.5f);
	stuff[7].setPosition(Vector2f(1500.f, 50.f));
	stuff[7].draw(window);
	stuff[7].setScale(0.5f, 0.5f);
	stuff[7].setPosition(Vector2f(1530.f, 100.f));
	stuff[7].draw(window);

	stuff[8].setScale(0.5f, 0.5f);
	stuff[8].setPosition(Vector2f(1200.f, 500.f));
	stuff[8].draw(window);
	stuff[8].setPosition(Vector2f(100.f, 700.f));
	stuff[8].draw(window);

	stuff[9].setScale(0.7f, 0.7f);
	stuff[9].setPosition(Vector2f(1410.f, 925.f));
	stuff[9].draw(window);
	
	stuff[10].setScale(0.7f, 0.7f);
	stuff[10].setPosition(Vector2f(220.f, 220.f));
	stuff[10].draw(window);
	
	stuff[11].setScale(0.7f, 0.7f);
	stuff[11].setPosition(Vector2f(200.f, 200.f));
	stuff[11].draw(window);
	stuff[11].setScale(0.4f, 0.4f);
	stuff[11].setPosition(Vector2f(300.f, 230.f));
	stuff[11].draw(window);

	stuff[12].setScale(0.7f, 0.7f);
	stuff[12].setPosition(Vector2f(1500.f, 200.f));
	stuff[12].draw(window);
	stuff[12].setPosition(Vector2f(900.f, 500.f));
	stuff[12].draw(window);
}
//				++++++++++++++++++++

//_____Processing collision snake with stones
bool checkCollisionStones(vector<Object> stones, Object & part)
{
	for (int i = 0; i < AMOUNT_STONES; i++)
		if (stones[i].causeCollisionObj(part) && i != 4)
		{
			cout <<i+1<<" +++ "<< stones[i].getPosition().x << " ++++ " << stones[i].getWidth() << endl;
			cout <<i+1<<" +++ "<< stones[i].getPosition().y << " ---- " << stones[i].getHeigh() << endl;
			return true;
		}
	return false;
}
//				++++++++++++++++++++

//_____Processing functions of Score_____
void drawScoreSingle(RenderWindow& window, vector<Object>& scoreFrame, const string & namePlayer, Text text[])
{
	scoreFrame[0].setPosition(Vector2f(440.f, 975.f));
	scoreFrame[0].setScale(1.5f, 0.5f);
	scoreFrame[0].setColor();
	scoreFrame[0].draw(window);

	scoreFrame[3].setScale(0.8f, 0.8f);
	scoreFrame[3].setPosition(Vector2f(1160.f, 960.f));
	scoreFrame[3].draw(window);
	
	text[37].setString(namePlayer);
	text[37].setFillColor(Color::Red);
	text[37].setCharacterSize(50);
	text[37].setPosition(Vector2f(650.f, 1025.f));
	window.draw(text[37]);
}
void drawScoreMulti(RenderWindow& window, vector<Object>& scoreFrame, const string & namePlayer1, const string & namePlayer2, Text text[])
{
	scoreFrame[1].setPosition(Vector2f(-100.f, 975.f));
	scoreFrame[1].setScale(1.5f, 0.5f);
	scoreFrame[1].setColor();
	scoreFrame[1].draw(window);

	scoreFrame[2].setPosition(Vector2f(1000.f, 975.f));
	scoreFrame[2].setScale(1.5f, 0.5f);
	scoreFrame[2].setColor();
	scoreFrame[2].draw(window);

	scoreFrame[3].setScale(0.8f, 0.8f);
	scoreFrame[3].setPosition(Vector2f(630.f, 950.f));
	scoreFrame[3].draw(window);

	scoreFrame[4].setScale(0.5f, 0.55f);
	scoreFrame[4].setPosition(Vector2f(800.f, 970.f));
	scoreFrame[4].draw(window);

	scoreFrame[5].setPosition(Vector2f(960.f, 980.f));
	scoreFrame[5].setScale(0.5f, 0.5f);
	scoreFrame[5].draw(window);

	text[37].setString(namePlayer1);
	text[37].setFillColor(Color::White);
	text[37].setCharacterSize(50);
	text[37].setPosition(Vector2f(150.f, 1025.f));
	window.draw(text[37]);

	text[37].setString(namePlayer2);
	text[37].setFillColor(Color::Black);
	text[37].setPosition(Vector2f(1780.f, 1025.f));
	window.draw(text[37]);
}
void setTextScoreSingleIngame(Text text[])
{
	text[7].setStyle(1);
	text[7].setFillColor(Color::White);
	text[7].setCharacterSize(45);
	text[7].setPosition(Vector2f(970.f, 1020.f));
	text[7].setString("0");
}
void setTextScoreMultiIngame(Text text[])
{
	text[28].setStyle(1);
	text[28].setFillColor(Color::White);
	text[28].setCharacterSize(45);
	text[28].setPosition(Vector2f(420.f, 1020.f));
	text[28].setString("0");

	text[29].setStyle(1);
	text[29].setFillColor(Color::Black);
	text[29].setCharacterSize(45);
	text[29].setPosition(Vector2f(1520.f, 1020.f));
	text[29].setString("0");
}
//			++++++++++++++++++++

//_____Processing supporting functions for Score_____
string convertToChar(const int& number)
{
	char x;
	x = number + '0';
	string str = "";
	str += x;
	return str;
}
string convertToStr(int number)
{
	if (number == 0)
		return "0";
	string str = "";
	while (number != 0)
	{
		int temp = number % 10;
		number /= 10;
		str.insert(0, convertToChar(temp));
	}
	return str;
}
//			++++++++++++++++++++

//_____Processing functions of Menu_____
void drawOptionButtons(RenderWindow& window, vector<Object>&choices, Text textStart[], const int & amountText)
{
	//backround
	choices[4].setScale(1.7f, 1.3f);
	choices[4].draw(window);
	
	//ve chu vietnam voi ou
	choices[5].setScale(1.1f, 1.1f);
	choices[5].setPosition(Vector2f(1500.f, 700.f));
	choices[5].draw(window);
	textStart[0].setString("VIET");
	textStart[0].setFillColor(Color::Red);
	textStart[0].setCharacterSize(35);
	textStart[0].setStyle(1);
	textStart[0].setPosition(Vector2f(1660.f, 790.f));
	window.draw(textStart[0]);
	textStart[0].setString("NAM");
	textStart[0].setPosition(Vector2f(1660.f, 830.f));
	window.draw(textStart[0]);

	choices[8].setScale(0.2f, 0.2f);
	choices[8].setPosition(Vector2f(1685.f, 875.f));
	choices[8].draw(window);

	// ve cac nut lua chon
	choices[0].setPosition(Vector2f(800.f, 300.f));
	for (int i = 1; i < 4; i++)
		choices[i].setPosition(Vector2f(800.f, choices[i - 1].getPosition().y + choices[i - 1].getHeigh() + 50.f));
	for (int i = 0; i < 4; i++)
	{
		choices[i].setScale(0.3f, 0.3f);
		choices[i].draw(window);
	}
	// ve chu lua chon
	textStart[0].setString("PLAY");
	textStart[1].setString("RANK");
	textStart[2].setString("OPTIONS");
	textStart[3].setString("EXIT");
	
	for (int i = 0; i < amountText; i++)
	{
		if (i == 2)
			textStart[i].setPosition(Vector2f(choices[i].getPosition().x + 80.f, choices[i].getPosition().y + 50.f));
		else
			textStart[i].setPosition(Vector2f(choices[i].getPosition().x + 100.f, choices[i].getPosition().y + 50.f));
		textStart[i].setFillColor(Color::Red);
		textStart[i].setCharacterSize(45);
		textStart[i].setStyle(1);
		window.draw(textStart[i]);
	}
	// stuff
	choices[6].setPosition(Vector2f(1600.f, 5.f));
	choices[6].setScale(1.1f, 1.1f);
	choices[6].draw(window);
	choices[7].setPosition(Vector2f(1300.f, 5.f));
	choices[7].setScale(1.1f, 1.1f);
	choices[7].draw(window);
	textStart[4].setString("INFOR");
	textStart[5].setString("HELP");
	for (int i = 4; i < 6; i++)
	{
		textStart[i].setFillColor(Color::Red);
		textStart[i].setCharacterSize(30);
		textStart[i].setStyle(1);
	}
	textStart[4].setPosition(Vector2f(choices[6].getPosition().x +70.f, choices[6].getPosition().y + 140.f));
	window.draw(textStart[4]);
	textStart[5].setPosition(Vector2f(choices[7].getPosition().x + 80.f, choices[6].getPosition().y + 140.f));
	window.draw(textStart[5]);

}
void decorateStartMenu(RenderWindow& window, vector<Object>&snakes,vector<Object>&choices, Text textStart[] )
{
	snakes[1].setPosition(Vector2f(200.f, 700.f));
	snakes[2].setPosition(Vector2f(1200.f, 700.f));
	snakes[1].setScale(1.2f, 1.4f);
	snakes[2].setScale(1.3f, 1.4f);
	snakes[1].draw(window);
	snakes[2].draw(window);
	choices[9].setPosition(Vector2f(400.f, 660.f));
	choices[9].setScale(1.1f, 1.1f);
	choices[9].draw(window);
}
int chooseOptions(RenderWindow & window,vector<Object>&choices, Text textStart[], const int & amountText, Mouse & mouse)
{
	
	//start, rank, oprion, exit
	for (int i = 0; i < 4; i++)
		if (mouse.getPosition().x >= choices[i].getPosition().x && mouse.getPosition().x <= choices[i].getPosition().x + choices[i].getWidth()
			&& mouse.getPosition().y >= choices[i].getPosition().y && mouse.getPosition().y <= choices[i].getPosition().y + choices[i].getHeigh())
		{

			//zoom in the button when mouse move there
			choices[i].setScale(0.4f, 0.4f);
			choices[i].draw(window);
			if (i == 2)
				textStart[i].setPosition(Vector2f(choices[i].getPosition().x + 120.f, choices[i].getPosition().y + 70.f));
			else
				textStart[i].setPosition(Vector2f(choices[i].getPosition().x + 160.f, choices[i].getPosition().y + 70.f));
			window.draw(textStart[i]);
			//check confirm
			if (mouse.isButtonPressed(Mouse::Button::Left))
				return i;
		}
		else
			choices[i].setScale(0.3f, 0.3f);

	//infor, help
	for (int i = 6; i < 8; i++)
		if (mouse.getPosition().x >= choices[i].getPosition().x+30.f && mouse.getPosition().x <= choices[i].getPosition().x + choices[i].getWidth()
			&& mouse.getPosition().y >= choices[i].getPosition().y+60.f && mouse.getPosition().y <= choices[i].getPosition().y + choices[i].getHeigh())
		{
			//zoom in the button when mouse move there+
			choices[i].draw(window);
			textStart[i - 2].setCharacterSize(40);
			window.draw(textStart[i-2]);
			//check confirm
			if (mouse.isButtonPressed(Mouse::Button::Left))
				return i - 2;
		}
		else
			choices[i].setScale(1.1f, 1.1f);
	return -1;
}
//			++++++++++++++++++++

//_____Processing functions of Rank_____
void drawBackgroundRank(RenderWindow& window,vector<Object>& ranks)
{
	ranks[0].setScale(2.f, 2.3f);
	ranks[0].draw(window);

	ranks[4].setScale(1.2f, 0.5f);
	ranks[4].setPosition(Vector2f(470.f, 240.f));
	ranks[4].draw(window);
	ranks[4].setScale(1.1f, 0.45f);
	ranks[4].setPosition(Vector2f(505.f, 540.f));
	ranks[4].draw(window);
	ranks[4].setScale(1.f, 0.35f);
	ranks[4].setPosition(Vector2f(540.f, 810.f));
	ranks[4].draw(window);

	ranks[1].setScale(1.4f, 1.4f);
	ranks[1].setPosition(Vector2f(600.f, 280.f));
	ranks[1].draw(window);
	for (int i = 2; i < 4; i++)
	{
		if (i == 2)
			ranks[i].setScale(1.3f, 1.3f);
		else
			ranks[i].setScale(1.2f, 1.2f);
		ranks[i].setPosition(Vector2f(ranks[i - 1].getPosition().x+20.f, ranks[i - 1].getPosition().y + ranks[i - 1].getHeigh() + 10.f));
		ranks[i].draw(window);
	}
	ranks[5].setPosition(Vector2f(1300.f, 700.f));
	ranks[5].draw(window);
	ranks[6].setPosition(Vector2f(120.f, 580.f));
	ranks[6].draw(window);

}
void setDataRank(RankAcc top[] )
{

	ifstream fileIn;
	top[0].name = "";
	top[1].name = "";
	top[2].name = "";
	top[0].score = 0;
	top[1].score = 0;
	top[2].score = 0;

	//get data of first player in list then set for top 1  
	fileIn.open("rank.txt", ios_base::in);
	rewind(stdin);
	getline(fileIn, top[0].name);
	rewind(stdin);
	fileIn >> top[0].score;
	fileIn.close();
	char x;
	string name;
	int score;

	//top1
	// read file and compare score of top 1 with anothers in list to find greatest score
	fileIn.open("rank.txt", ios_base::in);
	while (!fileIn.eof())
	{
		rewind(stdin);
		getline(fileIn, name);
		rewind(stdin);
		fileIn >> score;

		if (top[0].score < score)
		{
			top[0].score = score;
			top[0].name = name;
		}

		if (fileIn.eof())
			break;
		fileIn >> x;
		fileIn.seekg(-1, 1);
	}
	fileIn.close();
	
	//top2
	// read file and compare score of top 2 with anothers in list to find greatest score (except top 1)
	fileIn.open("rank.txt", ios_base::in);
	while (!fileIn.eof())
	{
		rewind(stdin);
		getline(fileIn, name);
		rewind(stdin);
		fileIn >> score;
		if ((score == top[0].score&&score > top[1].score&&name != top[0].name) || (score<top[0].score && score>top[1].score))
		{
			top[1].score = score;
			top[1].name = name;
		}
		if (fileIn.eof())
			break;
		fileIn >> x;
		fileIn.seekg(-1, 1);
	}
	fileIn.close();

	//top3
	// read file and compare score of top 3 with anothers in list to find greates score (except top 1 and top 2)
	fileIn.open("rank.txt", ios_base::in);
	while (!fileIn.eof())
	{
		rewind(stdin);
		getline(fileIn, name);
		rewind(stdin);
		fileIn >> score;
		if ((score == top[1].score&&name != top[1].name&&name != top[0].name) || (score<top[1].score && score>top[2].score))
		{
			top[2].score = score;
			top[2].name = name;
		}
		if (fileIn.eof())
			break;
		fileIn >> x;
		fileIn.seekg(-1, 1);
	}
	fileIn.close();
	
}
void drawDataRank(RenderWindow& window, RankAcc top[],vector<Object>& ranks,Text& text)
{
	text.setFillColor(Color::Black);
	text.setCharacterSize(80);
	//top1
		//score
	text.setString(convertToStr(top[0].score));
	text.setPosition(Vector2f(ranks[1].getPosition().x + 280.f, ranks[1].getPosition().y + 80.f));
	window.draw(text);

	//top2 
		//score
	text.setString(convertToStr(top[1].score));
	text.setPosition(Vector2f(ranks[2].getPosition().x + 280.f, ranks[1].getPosition().y + 340.f));
	window.draw(text);

	//top3
		//score
	text.setString(convertToStr(top[2].score));
	text.setPosition(Vector2f(ranks[2].getPosition().x + 280.f, ranks[1].getPosition().y + 600.f));
	window.draw(text);

	text.setCharacterSize(50);
	text.setFillColor(Color::Red);
	//top 1
		//name
	text.setString(top[0].name);
	if (top[0].name.length() <= 3)
	text.setPosition(Vector2f(320.f, 650.f));
	else
		text.setPosition(Vector2f(290.f, 650.f));
	window.draw(text);

	//top 2
		//name
	text.setString(top[1].name);
	if(top[1].name.length()<=3)
		text.setPosition(Vector2f(300.f, 790.f));
	else
		text.setPosition(Vector2f(270.f, 790.f));
	window.draw(text);

	//top 3
		//name
	text.setString(top[2].name);
	if(top[2].name.length()<=3)
	text.setPosition(Vector2f(290.f,910.f));
	else
		text.setPosition(Vector2f(260.f, 910.f));
	window.draw(text);
}
bool backToMenu(RenderWindow& window, vector<Object>& ranks, Text& text, Mouse & mouse)
{
	bool flag = false;
	ranks[7].setScale(1.1f, 1.2f);
	ranks[7].setPosition(Vector2f(1500.f, 810.f));
	ranks[7].draw(window);
	text.setString("BACK");
	text.setFillColor(Color::Black);
	text.setPosition(Vector2f(1600.f, 855.f));

	if (mouse.getPosition().x >= text.getPosition().x&&mouse.getPosition().x <= text.getPosition().x + text.getGlobalBounds().width&&
		mouse.getPosition().y >= text.getPosition().y&& mouse.getPosition().y <= text.getPosition().y + text.getGlobalBounds().height)
	{
		//zoom in button when mouse move there
		text.setPosition(Vector2f(1600.f, 845.f));
		text.setCharacterSize(50);
		text.setFillColor(Color::Red);
		//check confirm
		if(mouse.isButtonPressed(Mouse::Button::Left))
			flag = true;
	}
	else
		text.setCharacterSize(40);
	window.draw(text);
	return flag;
}
//			++++++++++++++++++++

//_____Processing functions of Option_____
void drawBackgroundOption(RenderWindow& window, vector<Object>& option, vector<Object>&snakes, Text text[])
{
	option[1].setScale(1.9f, 1.7f);
	option[0].setPosition(Vector2f(650.f, 290.f));
	option[0].setScale(1.f, 1.f);
	option[5].setPosition(Vector2f(200.f, 890.f));
	option[5].setScale(0.5f, 0.5f);
	option[4].setPosition(Vector2f(1600.f, 840.f));
	option[4].setScale(0.6f, 0.6f);
	option[1].draw(window);
	option[0].draw(window);
	option[5].draw(window);
	option[4].draw(window);
	text[9].setString("LEVEL");
	text[10].setString("MODE");
	for (int i = 9; i <= 10; i++)
	{
		text[i].setFillColor(Color::Black);
		text[i].setCharacterSize(50);
	}
	snakes[3].setScale(0.8f, 0.7f);
	snakes[3].setPosition(Vector2f(1570.f, 380.f));
	snakes[0].setPosition(Vector2f(100.f, 450.f));
	snakes[4].setPosition(Vector2f(850.f, 850.f));
	snakes[4].draw(window);
	snakes[0].draw(window);
	snakes[3].draw(window);

	text[16].setString("BACK");
	text[16].setCharacterSize(30);
	text[16].setFillColor(Color::Black);
	text[16].setPosition(Vector2f(1650.f, 900.f));
}
int setMenuOption(RenderWindow& window, Text text[], Mouse & mouse)
{
	int flag = -1;
	// mode
	if (mouse.getPosition().x >= text[9].getPosition().x - 30.f && mouse.getPosition().x <= text[9].getPosition().x + text[9].getGlobalBounds().width + 30.f&&
		mouse.getPosition().y >= text[9].getPosition().y - 30.f&& mouse.getPosition().y <= text[9].getPosition().y + text[9].getGlobalBounds().height + 30.f)
	{
		//zoom in button when mouse move there
		text[9].setCharacterSize(60);
		text[9].setPosition(Vector2f(950.f, 520.f));
		text[9].setFillColor(Color::Red);
		window.draw(text[9]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = 0;
	}
	else
		text[9].setPosition(Vector2f(950.f, 520.f));
	window.draw(text[9]);
	if (flag == 0)
	{
		text[10].setPosition(Vector2f(700.f, 410.f));
		window.draw(text[10]);
		return flag;
	}
	//level
	if (mouse.getPosition().x >= text[10].getPosition().x - 30.f&& mouse.getPosition().x <= text[10].getPosition().x + text[10].getGlobalBounds().width + 30.f&&
		mouse.getPosition().y >= text[10].getPosition().y - 20.f&& mouse.getPosition().y <= text[10].getPosition().y + text[10].getGlobalBounds().height + 20.f)
	{
		//zoom in button when mouse move there
		text[10].setCharacterSize(60);
		text[10].setPosition(Vector2f(700.f, 410.f));
		text[10].setFillColor(Color::Red);
		window.draw(text[10]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = 1;
	}
	else
		text[10].setPosition(Vector2f(700.f, 410.f));
	window.draw(text[10]);
	return flag;
}
void drawMenuMode(RenderWindow& window, vector <Object>& option, Text text[])
{
	option[3].setScale(1.1f, 1.2f);
	option[3].setPosition(Vector2f(200.f, 450.f));
	option[3].draw(window);
	text[11].setString("MULTIPLE");
	text[12].setString("SINGLE");
	
	for (int i = 11; i <= 12; i++)
	{
		text[i].setFillColor(Color::Black);
		text[i].setCharacterSize(30);
	}
}
int setMode(RenderWindow& window, Text text[], Mouse& mouse)
{
	int flag = -1;
	//multi
	if (mouse.getPosition().x >= text[11].getPosition().x - 5.f && mouse.getPosition().x <= text[11].getPosition().x + text[11].getGlobalBounds().width + 5.f&&
		mouse.getPosition().y >= text[11].getPosition().y - 5.f&& mouse.getPosition().y <= text[11].getPosition().y + text[11].getGlobalBounds().height + 5.f)
	{
		//ziim in button when mouse move there
		text[11].setCharacterSize(35);
		text[11].setPosition(Vector2f(350.f, 520.f));
		text[11].setFillColor(Color::Red);
		window.draw(text[11]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = 0;
	}
	else
		text[11].setPosition(Vector2f(360.f, 520.f));
	window.draw(text[11]);
	if (flag == 0)
	{
		text[12].setPosition(Vector2f(380.f, 600.f));
		window.draw(text[12]);
		return flag;
	}
	//single
	if (mouse.getPosition().x >= text[12].getPosition().x - 5.f&& mouse.getPosition().x <= text[12].getPosition().x + text[12].getGlobalBounds().width + 5.f&&
		mouse.getPosition().y >= text[12].getPosition().y - 5.f&& mouse.getPosition().y <= text[12].getPosition().y + text[12].getGlobalBounds().height + 5.f)
	{
		//zoom in button when mouse move there
		text[12].setCharacterSize(40);
		text[12].setPosition(Vector2f(380.f, 600.f));
		text[12].setFillColor(Color::Red);
		window.draw(text[12]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = 1;
	}
	else
		text[12].setPosition(Vector2f(380.f, 600.f));
	window.draw(text[12]);
	return flag;

}
void drawMenuLevel(RenderWindow& window, vector<Object>& option, Text text[])
{
	option[2].setScale(0.8f, 0.7f);
	option[2].setPosition(Vector2f(1200.f, 420.f));
	option[2].draw(window);
	text[13].setString("NORMAL");
	text[14].setString("HARD");
	text[15].setString("NIGHTMARE");
	text[13].setRotation(8.f);
	text[15].setRotation(8.f);
	
	for (int i = 13; i < 16; i++)
	{
		text[i].setFillColor(Color::Black);
		text[i].setCharacterSize(30);
	}
}
int setLevel(RenderWindow& window, Text text[], Mouse& mouse)
{
	int flag = -1;
	//normal
	if (mouse.getPosition().x >= text[13].getPosition().x - 30.f && mouse.getPosition().x <= text[13].getPosition().x + text[13].getGlobalBounds().width + 20.f&&
		mouse.getPosition().y >= text[13].getPosition().y - 5.f&& mouse.getPosition().y <= text[13].getPosition().y + text[13].getGlobalBounds().height + 5.f)
	{
		//zoom in button when mouse move there
		text[13].setCharacterSize(40);
		text[13].setPosition(Vector2f(1350.f, 450.f));
		text[13].setFillColor(Color::Red);
		window.draw(text[13]);
		//check cofirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = 0;
	}
	else
		text[13].setPosition(Vector2f(1350.f, 450.f));
	window.draw(text[13]);
	if (flag == 0)
	{
		text[14].setPosition(Vector2f(1370.f, 540.f));
		window.draw(text[14]);
		text[15].setPosition(Vector2f(1320.f, 625.f));
		window.draw(text[15]);
		return flag;
	}
	//hard
	if (mouse.getPosition().x >= text[14].getPosition().x - 50.f&& mouse.getPosition().x <= text[14].getPosition().x + text[14].getGlobalBounds().width + 20.f&&
		mouse.getPosition().y >= text[14].getPosition().y - 5.f&& mouse.getPosition().y <= text[14].getPosition().y + text[14].getGlobalBounds().height + 5.f)
	{
		//zoom in button when mouse move there
		text[14].setCharacterSize(40);
		text[14].setPosition(Vector2f(1370.f, 540.f));
		text[14].setFillColor(Color::Red);
		window.draw(text[14]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = 1;
	}
	else
		text[14].setPosition(Vector2f(1370.f, 540.f));
	window.draw(text[14]);
	if (flag == 1)
	{
		text[13].setPosition(Vector2f(1350.f, 450.f));
		window.draw(text[13]);
		text[15].setPosition(Vector2f(1320.f, 625.f));
		window.draw(text[15]);
		return flag;
	}
	//nightmare
	if (mouse.getPosition().x >= text[15].getPosition().x - 5.f&& mouse.getPosition().x <= text[15].getPosition().x + text[15].getGlobalBounds().width + 5.f&&
		mouse.getPosition().y >= text[15].getPosition().y - 5.f&& mouse.getPosition().y <= text[15].getPosition().y + text[15].getGlobalBounds().height + 5.f)
	{
		//zoom in button when mouse move there
		text[15].setCharacterSize(35);
		text[15].setPosition(Vector2f(1320.f, 625.f));
		text[15].setFillColor(Color::Red);
		window.draw(text[14]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = 2;
	}
	else
		text[15].setPosition(Vector2f(1320.f, 625.f));
	window.draw(text[15]);
	return flag;
}
bool backFromOption(RenderWindow& window, Text text[], Mouse& mouse)
{
	if (mouse.getPosition().x >= text[16].getPosition().x - 5.f&&mouse.getPosition().x <= text[16].getPosition().x + text[16].getGlobalBounds().width + 5.f&&
		mouse.getPosition().y >= text[16].getPosition().y - 5.f&& mouse.getPosition().y <= text[16].getPosition().y + text[16].getGlobalBounds().height + 5.f)
	{
		//zoom in whe mouse move there
		text[16].setCharacterSize(35);
		text[16].setFillColor(Color::Red);
		window.draw(text[16]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			return true;
	}
	else
		window.draw(text[16]);
	return false;
}
//			++++++++++++++++++++

//_____Processing functions of Information_____
void drawBackgroundInfor(RenderWindow& window, vector<Object>& infor)
{
	infor[0].setScale(2.f, 2.f);
	infor[0].draw(window);
	infor[1].setScale(1.f, 1.f);
	infor[1].setPosition(Vector2f(120.f, 100.f));
	infor[1].draw(window);

	infor[1].setScale(0.2f, 0.2f);
	infor[1].setPosition(Vector2f(1600.f, 900.f));
	infor[1].draw(window);
}
string* setDataInfor()
{
	ifstream fileIn;
	fileIn.open("infor.txt", ios_base::in);
	string* strData=new string [8];
	int countData = 0;
	while (!fileIn.eof())
	{
		rewind(stdin);
		getline(fileIn, strData[countData]);
		if (fileIn.eof())
			break;
		countData++;
	}
	fileIn.close();
	return strData;
}
void drawDataInfor(RenderWindow& window, Text text[], string* strData)
{
	text[17].setCharacterSize(40);
	text[17].setFillColor(Color::Red);
	text[17].setString(strData[0]);
	text[17].setPosition(Vector2f(850.f, 200.f));
	window.draw(text[17]);

	text[17].setString(strData[1]);
	text[17].setPosition(Vector2f(770.f, 250.f));
	window.draw(text[17]);

	text[17].setFillColor(Color::White);
	text[17].setString(strData[2]);
	text[17].setPosition(Vector2f(430.f, 300.f));
	window.draw(text[17]);

	text[17].setString(strData[3]);
	text[17].setPosition(Vector2f(390.f, 350.f));
	window.draw(text[17]);

	text[17].setFillColor(Color::Cyan);
	text[17].setString(strData[4]);
	text[17].setPosition(Vector2f(640.f, 400.f));
	window.draw(text[17]);

	text[17].setString(strData[5]);
	text[17].setPosition(Vector2f(690.f, 450.f));
	window.draw(text[17]);

	text[17].setFillColor(Color::White);
	text[17].setString(strData[6]);
	text[17].setPosition(Vector2f(660.f, 500.f));
	window.draw(text[17]);

	text[17].setFillColor(Color::Magenta);
	text[17].setString(strData[7]);
	text[17].setPosition(Vector2f(790.f, 600.f));
	window.draw(text[17]);
	delete[] strData;
}
bool backFromInfor(RenderWindow& window, Text text[], Mouse &mouse)
{
	bool flag = false;
	text[19].setString("BACK");
	text[19].setCharacterSize(60);
	text[19].setPosition(Vector2f(1670.f, 930.f));
	text[19].setFillColor(Color::Black);
	if (mouse.getPosition().x >= text[19].getPosition().x - 30.f&& mouse.getPosition().x <= text[19].getPosition().x + text[19].getGlobalBounds().width + 30.f&&
		mouse.getPosition().y >= text[19].getPosition().y - 30.f&& mouse.getPosition().y <= text[19].getPosition().y + text[19].getGlobalBounds().height + 40.f)
	{
		//zoom in button when mouse move there
		text[19].setCharacterSize(70);
		text[19].setFillColor(Color::Red);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = true;
	}
	window.draw(text[19]);
	return flag;
}
//			++++++++++++++++++++

//_____Processing function of Help_____
void drawBackgroundHelp(RenderWindow& window,vector<Object>& help, vector<Object>& movementButtons, Text text [])
{
	help[0].setScale(2.3f, 2.3f);
	help[0].draw(window);
	help[1].setScale(1.5f, 1.2f);
	help[1].setPosition(Vector2f(250.f, 200.f));
	help[1].draw(window);
	text[18].setFillColor(Color::Green);
	text[18].setCharacterSize(100);
	text[18].setPosition(Vector2f(700.f, 250.f));
	text[18].setString("TUTORIAL");
	window.draw(text[18]);
	text[18].setCharacterSize(40);
	text[18].setFillColor(Color::Black);
	text[18].setPosition(Vector2f(340.f, 400.f));
	text[18].setString("Control your snake to eat the food that appears randomly on the");
	window.draw(text[18]);
	text[18].setPosition(Vector2f(290.f, 450.f));
	text[18].setString("map without letting the snake's head touch the obstacles and bite ");
	window.draw(text[18]);
	text[18].setPosition(Vector2f(290.f, 500.f));
	text[18].setString("its tail to gain the highest score.");
	window.draw(text[18]);
	text[18].setPosition(Vector2f(340.f, 550.f));
	text[18].setString("To control the snake: ");
	window.draw(text[18]);
	text[18].setString("PLAYER 1");
	text[18].setFillColor(Color::Red);
	text[18].setPosition(Vector2f(500.f, 600.f));
	window.draw(text[18]);
	text[18].setString("PLAYER 2");
	text[18].setPosition(Vector2f(1200.f, 600.f));
	window.draw(text[18]);

	movementButtons[0].setPosition(Vector2f(1120.f, 660.f));
	movementButtons[0].draw(window);
	movementButtons[1].setScale(1.f, 1.3f);
	movementButtons[1].setPosition(Vector2f(400.f, 630.f));
	movementButtons[1].draw(window);

	help[2].setPosition(Vector2f(850.f, 550.f));
	help[2].draw(window);

	help[3].setScale(1.2f, 1.2f);
	help[3].setPosition(Vector2f(800.f, 0.f));
	help[3].draw(window);

}
bool backFromHelp(RenderWindow& window, vector<Object>& hekp, Text text[], Mouse & mouse)
{
	bool flag = false;
	text[18].setCharacterSize(40);
	text[18].setFillColor(Color::Black);
	text[18].setPosition(Vector2f(850.f, 100.f));
	text[18].setString("BACK");
	if (mouse.getPosition().x >= text[18].getPosition().x - 5.f&& mouse.getPosition().x <= text[18].getPosition().x + text[18].getGlobalBounds().width + 5.f&&
		mouse.getPosition().y >= text[18].getPosition().y - 5.f&& mouse.getPosition().y <= text[18].getPosition().y + text[18].getGlobalBounds().height + 5.f)
	{
		//zoom in when mouse move there
		text[18].setCharacterSize(45);
		text[18].setFillColor(Color::Red);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = true;
	}
	window.draw(text[18]);
	return flag;
}
//			++++++++++++++++++++

//_____Processing function of account_____
//				backgourd
void drawBackgroundLogIn(RenderWindow& window, vector<Object>&account)
{
	account[0].setScale(1.9f, 1.7f);
	account[0].setPosition(Vector2f(0.f, -100.f));
	account[0].draw(window);
	account[1].setPosition(Vector2f(450.f, 100.f));
	account[1].draw(window);

	account[2].setScale(0.7f, 0.7f);
	account[2].setPosition(Vector2f(740.f, 370.f));
	account[2].draw(window);

	account[3].setScale(0.7f, 0.7f);
	account[3].setPosition(Vector2f(740.f, 475.f));
	account[3].draw(window);
}
void drawBackgroundRegistration(RenderWindow& window, vector<Object>&account)
{
	account[5].setScale(1.9f, 2.f);
	account[5].setPosition(Vector2f(0.f, -50.f));
	account[5].draw(window);
	account[6].setPosition(Vector2f(450.f, 100.f));
	account[6].draw(window);

	account[7].setPosition(Vector2f(780.f, 455.f));
	account[8].setPosition(Vector2f(780.f, 540.f));
	account[9].setPosition(Vector2f(780.f, 635.f));

	account[7].setScale(1.17f, 0.7f);
	account[7].draw(window);
	account[8].setScale(1.17f, 0.75f);
	account[8].draw(window);
	account[9].setScale(1.17f, 0.7f);
	account[9].draw(window);

	account[12].setPosition(Vector2f(50.f, 10.f));
	account[12].draw(window);
}
//			++++++++++++++++++++

//				log in
int clickLogin(vector <Object> & account, Mouse & mouse)
{
	//username
	if(mouse.getPosition().x>=account[2].getPosition().x&&mouse.getPosition().x<=account[2].getPosition().x+account[2].getWidth()&&
		mouse.getPosition().x>=account[2].getPosition().y&& mouse.getPosition().y<=account[2].getPosition().y+account[2].getHeigh())
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			return 0;
	//password
	if (mouse.getPosition().x >= account[3].getPosition().x&&mouse.getPosition().x <= account[3].getPosition().x + account[3].getWidth() &&
		mouse.getPosition().x >= account[3].getPosition().y&& mouse.getPosition().y <= account[3].getPosition().y + account[3].getHeigh())
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			return 1;
	return -1;
}
void drawUsernameLogin(RenderWindow& window, vector<Object>& account, Text text[], const string & username)
{
	text[20].setCharacterSize(30);
	text[20].setFillColor(Color::Red);
	text[20].setPosition(Vector2f(account[2].getPosition().x + 80.f, account[2].getPosition().y + 10.f));
	text[20].setString(username);
	window.draw(text[20]);
}
void drawPasswordLogin(RenderWindow& window, vector<Object>& account, Text text[], const string & password)
{
	text[21].setCharacterSize(30);
	text[21].setFillColor(Color::Red);
	text[21].setPosition(Vector2f(account[3].getPosition().x + 80.f, account[3].getPosition().y + 20.f));
	text[21].setString(password);
	window.draw(text[21]);
}
bool confirmLogin(RenderWindow& window, Text text[], Mouse & mouse)
{
	text[22].setString("Log In");
	text[22].setFillColor(Color::White);
	//text[22].setPosition(Vector2f(990.f, 560.f));
	text[22].setPosition(Vector2f(825.f, 560.f));
	text[22].setCharacterSize(30);
	if (mouse.getPosition().x >= text[22].getPosition().x - 10.f&& mouse.getPosition().x <= text[22].getPosition().x + text[22].getGlobalBounds().width + 10.f &&
		mouse.getPosition().y >= text[22].getPosition().y - 10.f&&mouse.getPosition().y <= text[22].getPosition().y + text[22].getGlobalBounds().height + 10.f)
	{
		//zoom in when mouse move there
		text[22].setCharacterSize(35);
		text[22].setFillColor(Color::Red);
		//text[22].setPosition(Vector2f(990.f, 560.f));
		text[22].setPosition(Vector2f(825.f, 560.f));
		window.draw(text[22]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			return true;
	}
	else
		window.draw(text[22]);
	return false;
}
bool checkConfirmLogin(const string & username, const string & password)
{
	bool flag = false;
	ifstream fileIn;
	fileIn.open("account.txt", ios_base::in);
	string usernameTemp = "";
	string passwordTemp = "";
	while (!fileIn.eof())
	{
		rewind(stdin);
		getline(fileIn, usernameTemp);
		rewind(stdin);
		getline(fileIn, passwordTemp);
		//check username, password
		if (username == usernameTemp && usernameTemp != "" &&password == passwordTemp && password != "")
			flag = true;
		if (fileIn.eof())
			break;
	}
	fileIn.close();
	return flag;
}
//			++++++++++++++++++++

//				 regist
bool confirmSwitchToRegistration(RenderWindow& window, Text text[], Mouse& mouse)
{
	text[23].setString("Regist");
	text[23].setFillColor(Color::White);
	//text[23].setPosition(Vector2f(825.f, 560.f));
	text[23].setPosition(Vector2f(990.f, 560.f));
	text[23].setCharacterSize(30);
	if (mouse.getPosition().x >= text[23].getPosition().x - 10.f&& mouse.getPosition().x <= text[23].getPosition().x + text[23].getGlobalBounds().width + 10.f &&
		mouse.getPosition().y >= text[23].getPosition().y - 10.f&&mouse.getPosition().y <= text[23].getPosition().y + text[23].getGlobalBounds().height + 10.f)
	{
		//zoom in button when mouse move there
		text[23].setCharacterSize(35);
		text[23].setFillColor(Color::Red);
		//text[23].setPosition(Vector2f(825.f, 560.f));
		text[23].setPosition(Vector2f(990.f, 560.f));
		window.draw(text[23]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			return true;
	}
	else
		window.draw(text[23]);
	return false;
}
void drawUsernameRegist(RenderWindow& window, vector<Object>& account, Text text[], const string & username)
{
	text[24].setCharacterSize(30);
	text[24].setFillColor(Color::Red);
	text[24].setPosition(Vector2f(account[7].getPosition().x + 50.f, account[7].getPosition().y + 10.f));
	text[24].setString(username);
	window.draw(text[24]);
}
void drawPasswordRegist(RenderWindow& window, vector<Object>& account, Text text[], const string & password)
{
	text[25].setCharacterSize(30);
	text[25].setFillColor(Color::Red);
	text[25].setPosition(Vector2f(account[8].getPosition().x + 50.f, account[8].getPosition().y + 20.f));
	text[25].setString(password);
	window.draw(text[25]);
}
void drawConfirmPasswordRegist(RenderWindow& window, vector<Object>& account, Text text[], const string & password)
{
	text[26].setCharacterSize(30);
	text[26].setFillColor(Color::Red);
	text[26].setPosition(Vector2f(account[9].getPosition().x + 50.f, account[9].getPosition().y + 20.f));
	text[26].setString(password);
	window.draw(text[26]);
}
bool confirmRegist(RenderWindow& window, Text text[], Mouse & mouse)
{
	text[27].setString("Create");
	text[27].setFillColor(Color::White);
	text[27].setPosition(Vector2f(900.f, 690.f));
	text[27].setCharacterSize(30);
	if (mouse.getPosition().x >= text[27].getPosition().x - 10.f&& mouse.getPosition().x <= text[27].getPosition().x + text[27].getGlobalBounds().width + 10.f &&
		mouse.getPosition().y >= text[27].getPosition().y - 10.f&&mouse.getPosition().y <= text[27].getPosition().y + text[27].getGlobalBounds().height + 10.f)
	{
		//zoom in button when mouse move there
		text[27].setCharacterSize(35);
		text[27].setFillColor(Color::Red);
		window.draw(text[27]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			return true;
	}
	else
		window.draw(text[27]);
	return false;
}
bool checkPassAndPassConfirm(const string & password, const string & passwordConfirm)
{
	if (password == passwordConfirm&&password != "")
		return true;
	return false;
}
bool checkConfirmRegist(const string & username, const string & password, const string & passwordConfirm)
{
	bool flag = false;
	ifstream fileIn;
	fileIn.open("account.txt", ios_base::in);
	string usernameTemp = "";
	string passwordTemp = "";
	while (!fileIn.eof())
	{
		rewind(stdin);
		getline(fileIn, usernameTemp);
		rewind(stdin);
		getline(fileIn, passwordTemp);\
		//check username, password, confirm password
		if (username != usernameTemp && usernameTemp != ""&& checkPassAndPassConfirm(password, passwordConfirm))
			flag = true;
		else
			if (username == usernameTemp || usernameTemp == ""|| !checkPassAndPassConfirm(password, passwordConfirm))
			{
				flag = false;
				break;
			}
		if (fileIn.eof())
			break;
	}
	fileIn.close();
	return flag;
}
void writeNewAccountToFile(const string & username, const string & password)
{
		ofstream fileOut;
		fileOut.open("account.txt", ios_base::out | ios_base::app);
		fileOut <<endl<< username << endl;
		fileOut << password;
		fileOut.close();
}
bool checkBackToLogin(RenderWindow& window, Text text[], Mouse& mouse)
{
	
	bool flag = false;
	text[40].setCharacterSize(30);
	text[40].setFillColor(Color::Black);
	text[40].setPosition(Vector2f(95.f, 95.f));
	text[40].setString("BACK");
	if (mouse.getPosition().x >= text[40].getPosition().x - 5.f&& mouse.getPosition().x <= text[40].getPosition().x + text[40].getGlobalBounds().width + 5.f&&
		mouse.getPosition().y >= text[40].getPosition().y - 5.f&& mouse.getPosition().y <= text[40].getPosition().y + text[40].getGlobalBounds().height + 5.f)
	{
		//zoom in when mouse move there
		text[40].setCharacterSize(35);
		text[40].setFillColor(Color::Red);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			flag = true;
	}
	window.draw(text[40]);
	return flag;

}
//			++++++++++++++++++++

//_____Processing functions of Name player_____
void drawNamePlayerSingle(RenderWindow& window, vector<Object>& namePlayer, Text text[], const string & namePlayerSingle)
{
	namePlayer[0].setScale(1.9f, 1.2f);
	namePlayer[0].draw(window);

	namePlayer[1].setScale(1.7f, 1.f);
	namePlayer[1].setPosition(Vector2f(750.f, 600.f));
	namePlayer[1].draw(window);

	namePlayer[2].setScale(0.5f, 0.5f);
	namePlayer[2].setPosition(Vector2f(920.f, 900.f));
	namePlayer[2].draw(window);

	text[30].setString("Name Player");
	text[30].setPosition(Vector2f(namePlayer[1].getPosition().x + 80.f, namePlayer[1].getPosition().y - 50.f));
	text[30].setFillColor(Color::White);
	text[30].setCharacterSize(50);
	window.draw(text[30]);

	text[31].setString(namePlayerSingle);
	if (namePlayerSingle.length() <= 5)
		text[31].setPosition(Vector2f(namePlayer[1].getPosition().x + 170.f, namePlayer[1].getPosition().y + 150.f));
	else
		text[31].setPosition(Vector2f(namePlayer[1].getPosition().x + 100.f, namePlayer[1].getPosition().y + 150.f));
	text[31].setFillColor(Color::Black);
	text[31].setCharacterSize(60);
	window.draw(text[31]);
}
void drawNamePlayerMulti(RenderWindow& window, vector<Object>& namePlayer, Text text[], const string & namePlayer1, const string & namePlayer2)
{
	namePlayer[0].setScale(1.9f, 1.2f);
	namePlayer[0].draw(window);

	namePlayer[1].setScale(1.7f, 1.f);
	namePlayer[1].setPosition(Vector2f(750.f, 600.f));
	namePlayer[1].draw(window);

	namePlayer[3].setScale(1.7f, 1.f);
	namePlayer[3].setPosition(Vector2f(750.f, 250.f));
	namePlayer[3].draw(window);

	namePlayer[2].setScale(0.5f, 0.5f);
	namePlayer[2].setPosition(Vector2f(920.f, 900.f));
	namePlayer[2].draw(window);

	text[32].setString("Name Player 1");
	text[32].setPosition(Vector2f(namePlayer[3].getPosition().x + 80.f, namePlayer[3].getPosition().y - 50.f));
	text[32].setFillColor(Color::White);
	text[32].setCharacterSize(50);
	window.draw(text[32]);

	text[33].setString("Name Player 2");
	text[33].setPosition(Vector2f(namePlayer[1].getPosition().x + 80.f, namePlayer[1].getPosition().y - 50.f));
	text[33].setFillColor(Color::Black);
	text[33].setCharacterSize(50);
	window.draw(text[33]);


	text[34].setString(namePlayer1);
	if (namePlayer1.length() <= 5)
		text[34].setPosition(Vector2f(namePlayer[3].getPosition().x + 170.f, namePlayer[3].getPosition().y + 150.f));
	else
		text[34].setPosition(Vector2f(namePlayer[3].getPosition().x + 100.f, namePlayer[3].getPosition().y + 150.f));
	text[34].setFillColor(Color::White);
	text[34].setCharacterSize(60);
	window.draw(text[34]);


	text[35].setString(namePlayer2);
	if (namePlayer2.length() <= 5)
		text[35].setPosition(Vector2f(namePlayer[1].getPosition().x + 170.f, namePlayer[1].getPosition().y + 150.f));
	else
		text[35].setPosition(Vector2f(namePlayer[1].getPosition().x + 100.f, namePlayer[1].getPosition().y + 150.f));
	text[35].setFillColor(Color::Black);
	text[35].setCharacterSize(60);
	window.draw(text[35]);
}
bool confirmEnterName(RenderWindow& window, Text text[], Mouse& mouse)
{
	text[36].setString("OK");
	text[36].setCharacterSize(40);
	text[36].setFillColor(Color::Red);
	text[36].setPosition(Vector2f(950.f, 945.f));
	if (mouse.getPosition().x >= text[36].getPosition().x - 5.f&&mouse.getPosition().x <= text[36].getPosition().x + text[36].getGlobalBounds().width + 5.f&&
		mouse.getPosition().y >= text[36].getPosition().y - 5.f&& mouse.getPosition().y <= text[36].getPosition().y + text[36].getGlobalBounds().height + 5.f)
	{
		//zoom in button when mouse move there
		text[36].setCharacterSize(45);
		text[36].setFillColor(Color::Green);
		window.draw(text[36]);
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
			return true;
	}
	window.draw(text[36]);
	return false;
}
bool checkNamePlayer(const string & namePlayer)
{
	bool flag = true;
	string namePlayerTemp="";
	int scoreTemp;
	ifstream fileIn;
	fileIn.open("rank.txt", ios_base::in);
	char x;
	while (!fileIn.eof())
	{
		rewind(stdin);
		getline(fileIn, namePlayerTemp);
		rewind(stdin);
		fileIn >> scoreTemp;
		//check setting name player
		if (namePlayer == "" || namePlayer == namePlayerTemp)
		{
			flag = false;
			break;
		}
		if (fileIn.eof())
			break;
		fileIn >> x;
		fileIn.seekg(-1, 1);
	}
	fileIn.close();
	return flag;
}
void writeNameAndScorePlayerToFile(const string &namePlayer, const int & score)
{
	ofstream fileOut;
	fileOut.open("rank.txt", ios_base::out | ios_base::app);
	fileOut << endl << namePlayer << endl;
	fileOut << score;
	fileOut.close();
}
//			++++++++++++++++++++

//_____Processing functions of Game over_____
void drawGameOverSingle(RenderWindow& window, vector<Object>& gameOver, Text text[], const string & namePlayerSingle, const int & score)
{
	gameOver[0].draw(window);
	gameOver[1].setScale(1.5f, 1.5f);
	gameOver[1].setPosition(Vector2f(500.f, 300.f));
	gameOver[1].draw(window);

	gameOver[2].setPosition(Vector2f(1400.f, 450.f));
	gameOver[2].setScale(1.f, 1.f);
	text[38].setString(namePlayerSingle);
	text[38].setFillColor(Color::Red);
	text[38].setCharacterSize(50);
	text[38].setPosition(Vector2f(800.f, 200.f));
	window.draw(text[38]);
	text[39].setString(convertToStr(score));
	text[39].setFillColor(Color::Red);
	text[39].setCharacterSize(50);
	text[39].setPosition(Vector2f(1070.f, 200.f));
	window.draw(text[39]);
}
void drawGameOverMulti(RenderWindow& window, vector<Object> & gameOver, Text text[], const string & namePlayer1, const string & namePlayer2, const int & score1, const int & score2)
{
	gameOver[0].draw(window);
	gameOver[1].setScale(1.5f, 1.5f);
	gameOver[1].setPosition(Vector2f(500.f, 300.f));
	gameOver[1].draw(window);

	gameOver[2].setPosition(Vector2f(1400.f, 450.f));
	gameOver[2].setScale(1.f, 1.f);

	text[38].setString(namePlayer1);
	text[38].setFillColor(Color::Red);
	text[38].setCharacterSize(50);
	text[38].setPosition(Vector2f(800.f, 200.f));
	window.draw(text[38]);
	text[39].setString(convertToStr(score1));
	text[39].setFillColor(Color::Red);
	text[39].setCharacterSize(50);
	text[39].setPosition(Vector2f(1070.f, 200.f));
	window.draw(text[39]);

	text[38].setString(namePlayer2);
	text[38].setFillColor(Color::Green);
	text[38].setPosition(Vector2f(800.f, 250.f));
	window.draw(text[38]);

	text[39].setString(convertToStr(score2));
	text[39].setFillColor(Color::Green);
	text[39].setPosition(Vector2f(1070.f, 250.f));
	window.draw(text[39]);

}
bool confirmGameOver(RenderWindow& window, vector<Object>& gameOver, Mouse & mouse)
{
	if (mouse.getPosition().x >= gameOver[2].getPosition().x&&mouse.getPosition().x <= gameOver[2].getPosition().x + gameOver[2].getWidth() &&
		mouse.getPosition().y >= gameOver[2].getPosition().y&&mouse.getPosition().y <= gameOver[2].getPosition().y + 200.f)
	{
		//zoom in the button when mouse move there
		gameOver[2].setScale(1.2f, 1.2f);
		gameOver[2].setPosition(Vector2f(1350.f, 400.f));
		//check confirm
		if (mouse.isButtonPressed(Mouse::Button::Left))
		{
			gameOver[2].draw(window);
			return true;
		}
	}
	gameOver[2].draw(window);
	return false;
}
//			++++++++++++++++++++

//_____Processing functions of Sound _____
void setDataSounđ(SoundBuffer & buffer, Sound & sound, const string & linkSound, const float & volume)
{
	if (!buffer.loadFromFile(linkSound))
		cerr << "Error!" << endl;
	sound.setBuffer(buffer);
	sound.setVolume(volume);
}
//				++++++++++++++++++++
//						============================================== Finish processing functions declared above =================================================
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
