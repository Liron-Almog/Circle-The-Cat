#pragma once
#pragma once
#include "Const.h"
#include <memory>
#include <SFML/Graphics.hpp>
class GameFont

{
public:

	static GameFont& instance();
	~GameFont() = default;
	const sf::Font& getFont(int num) const;

private:

	GameFont();
	GameFont(const GameFont&) = default;
	GameFont& operator=(const GameFont&) = default;
	sf::Font m_fontGame[FONT_NUMBER];
};

