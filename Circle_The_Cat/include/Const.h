#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <iomanip>


const float PHOTO_SIZE = 0.4;

using namespace std;
const int MAP_SIZE = 11
		, CIRCLE_SIZE = 30
		,CAT_SIZE = 25
		, GAME_FONT = 1
		,SCREEN_SIZE_W = 1100,
		SCREEN_SIZE_H = 800,
		SHOW_TIME =2,
		CAUGHT_CAT = -1,
		FIRST_LEVEL = 1;

const sf::Vector2f POS_CLICK_INFO = sf::Vector2f(280, 20)
, POS_LEVEL_INFO = sf::Vector2f(610, 20);
		

enum inforamtionBar_t{

	CLICK_BAR,
	CLICK_CONTENTÉ_BAR,
	LEVEL_BAR,
	LEVEL_CONTENT_BAR,
	INFORMATION
};
enum passScreen_t {
	GAME_OVER,
	NEXT_LEVEL,
	TRANSITION_SCREENS
};

enum gameFont_t {

	CANDY_FONT,
	ASDONUTS_FONT,
	FONT_NUMBER
};

