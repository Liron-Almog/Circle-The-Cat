#include "GameFont.h"

//-------------------instance--------------------
GameFont& GameFont::instance() {
	static GameFont inst;
	return inst;
}
//----------------getFont-----------------------
const sf::Font& GameFont::getFont(int num) const {

	return m_fontGame[num];
}
//----------------constructor-------------------
GameFont::GameFont() {

	m_fontGame[CANDY_FONT].loadFromFile("Candy_Pop!-demo-font.ttf");
	m_fontGame[ASDONUTS_FONT].loadFromFile("Asdonuts.ttf");
}

