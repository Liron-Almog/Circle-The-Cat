#include "Cat.h"
#include "Const.h"
#include "GameTexture.h"

//The function returns the global bounds of cat sprite;
//----------------getGlBounds---------------------
sf::FloatRect Cat::getGlBounds()  {
	return m_spriteCat.getGlobalBounds();
}

//------------------drawCat-----------------------
void Cat::drawCat(sf::RenderWindow& window) {

	window.draw(m_spriteCat);
}

//----------getPoslikeOneDimensional-------------
int Cat::getPoslikeOneDimensional() {
	return  m_locationInMap.y + m_locationInMap.x* MAP_SIZE;
}

//------------------setLocation-------------------
void Cat::setLocation(const int& row, const int& col) {
	m_locationInMap.x = row;
	m_locationInMap.y = col;
}

//------------------setPosition-------------------
void Cat::setPosition(int x, int y) {

	m_spriteCat.setPosition(x, y);
}

//------------------Constructor-------------------
Cat::Cat()
{
	m_spriteCat.setTexture(*GameTexture::instance().getCatTexture());
	m_spriteCat.setScale(0.11, 0.11);
	setStartLocation();
}

//------------------setStartLocation--------------
void Cat::setStartLocation() {

	setLocation(MAP_SIZE / 2, MAP_SIZE / 2);//Sets location in map
}

//----------------getPositionInArray------------
const sf::Vector2i* Cat::getLoactionInArray() {
	return &m_locationInMap;
}