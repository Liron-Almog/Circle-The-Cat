#pragma once
#include "Map.h";
class Controller
{
public:

	void runGame();
	Controller();
	~Controller() = default;
	void handleEvents(sf::RenderWindow& window);
	void gameStatus(int& currentLevel, sf::RenderWindow& window) ;
	void drawStatus(sf::RenderWindow& window,const int);

private:

	sf::Sprite m_transtionScreens[TRANSITION_SCREENS];
	Map m_map;

};

