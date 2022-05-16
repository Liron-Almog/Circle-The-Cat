#include "const.h"
#include "GameTexture.h"

//------------------constructor----------------
GameTexture::GameTexture()
{
	m_passScreenTexture[GAME_OVER].loadFromFile("GameOver.png");
	m_passScreenTexture[NEXT_LEVEL].loadFromFile("NextLevel.png");
	m_catTexture.loadFromFile("Cat.png");
	
}

//--------------getTexturePassScreen-----------
const sf::Texture* GameTexture::getPassScreenTexture(int num) const {

	return &m_passScreenTexture[num];
}

//------------------instance-----------------
GameTexture& GameTexture::instance() {
	static GameTexture inst;
	return inst;
}

//--------------------getCatTextur---------------------
const sf::Texture* GameTexture::getCatTexture() const {

	return &m_catTexture;
}
