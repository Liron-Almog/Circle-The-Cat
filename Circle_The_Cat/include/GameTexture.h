#pragma once
#include "Const.h"

class GameTexture
{
public:

	//------------------get function-------------------
	const sf::Texture* getPassScreenTexture(int num) const;
	~GameTexture() = default;
	static GameTexture& instance();
	const sf::Texture* getCatTexture() const;

private:

	GameTexture();
	GameTexture(const GameTexture&) = default;
	GameTexture& operator=(const GameTexture&) = default;

	sf::Texture m_passScreenTexture[TRANSITION_SCREENS];
	sf::Texture m_catTexture;

};
