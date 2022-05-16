#pragma once
#include "Const.h"
#include "Graph.h"
#include "Cat.h"
class Map
{
public:

	Map();
	~Map() = default;
	void readNextLevel();
	void setGameOver();
	void moveCatToEmptyTile();
	void restartLevel();
	void searchEmptyTile(int& col, int& row) const;
	void cleanMap();
	void insertBlockTile();
	void drawMap(sf::RenderWindow& window);
	void drawInfoBar(sf::RenderWindow& window);
	void addEdgeToGraph();
	void moveCat();
	void checkNeighborsAndInsert(const int row, const int col);
	void createMap();

	size_t getNumOfBlockTiles() const;
	int getLevel() const;

	bool isGameOver() const;
	bool fillTile(sf::Event event, sf::RenderWindow& window);
	bool isCat(const int& , const int& , const sf::Event& , sf::RenderWindow& );

private:

	void setInfoText();
	Graph m_graph = Graph(MAP_SIZE* MAP_SIZE);
	vector<pair <int,int>> m_blockTileOfCurrentMap;
	vector<vector<sf::CircleShape>> m_map;
	size_t m_numberOfClicks = 0;
	size_t m_level = FIRST_LEVEL;
	sf::Text m_infoText[INFORMATION];
	Cat m_catPlayer;
	bool m_GameOver = false;
};
