#pragma once
#include "Const.h"

class Cat
{
public:

	Cat();
	~Cat() = default;
	void drawCat(sf::RenderWindow& window);
    
	//-----------set function--------------
	void setPosition(int x, int y);
	void setLocation(const int & , const int& );
	void setStartLocation();

	//-----------get function--------------
	sf::FloatRect getGlBounds();
	int getPoslikeOneDimensional();
	const sf::Vector2i* getLoactionInArray();

	void setDirectionOfAni(const int row, const int  col);
private:
	
	sf::Sprite m_spriteCat;
	sf::Vector2i m_locationInMap;
	
};

