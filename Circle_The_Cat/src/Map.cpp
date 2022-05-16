#include "Map.h"
#include "GameFont.h"
#include "Graph.h"
#include "Const.h"

//The fucntion creates the map
//--------------createMap-----------------
void Map::createMap() {

	int shift = 0;
	sf::CircleShape tempCir(CIRCLE_SIZE);
	vector<sf::CircleShape> tempVec;

	for (size_t row = 0; row < MAP_SIZE; row++) {
		for (size_t col = 0; col < MAP_SIZE; col++) {
			if (row % 2 != 0)//Checks if the current row it's even
				shift = CIRCLE_SIZE;
			else shift = 0;
			tempCir.setPosition((float)(180 + (col * 1.08) * CIRCLE_SIZE * 2 + shift), 
										(float)(85 + (row * 1.01) * CIRCLE_SIZE * 2));
			tempCir.setFillColor(sf::Color::Black);
			tempVec.push_back(tempCir);
		}
		m_map.push_back(tempVec);
		tempVec.clear();
	}
	//Initializes the place of the cat
	m_catPlayer.setPosition(m_map[MAP_SIZE / 2][MAP_SIZE / 2].getPosition().x,
							m_map[MAP_SIZE / 2][MAP_SIZE / 2].getPosition().y);
	insertBlockTile();
	addEdgeToGraph();
}
//----------drawMap-----------------
void Map::drawMap(sf::RenderWindow& window) {

	window.clear(sf::Color(254, 255, 176));

	for (size_t row = 0; row < MAP_SIZE; row++) 
		for (size_t col = 0; col < MAP_SIZE; col++)
			window.draw(m_map[row][col]);

	drawInfoBar(window);
	m_catPlayer.drawCat(window);
	window.display();
}
//----------drawInfoBar---------------
void Map::drawInfoBar(sf::RenderWindow& window) {

	m_infoText[CLICK_CONTENTÉ_BAR].setString(std::to_string(m_numberOfClicks));
	m_infoText[LEVEL_CONTENT_BAR].setString(std::to_string(m_level));

	for (size_t i = 0; i < INFORMATION; i++)
		window.draw(m_infoText[i]);
}

// The function fills a tile if it is valid
//---------------fillTile-------------
bool Map::fillTile(sf::Event event, sf::RenderWindow& window) {
	
	for (size_t row = 0; row < MAP_SIZE; row++)
		for (size_t col = 0; col < MAP_SIZE; col++){

			if (m_map[row][col].getGlobalBounds().contains(window.mapPixelToCoords
				({ event.mouseButton.x,event.mouseButton.y }))) {//finds The place of click

				if (m_map[row][col].getFillColor() != sf::Color(231, 0, 0) &&
					!isCat(row,col,event,window)) {//checks if valid
					m_map[row][col].setFillColor(sf::Color(231, 0, 0));
					m_numberOfClicks++;
					drawMap(window);
					return true;
				}
				else return false;
				}
	}
	return false;
}
//The function returns random number 
// according the level
//------------getNumOfBlockTiles-------
size_t Map::getNumOfBlockTiles() const {

	if (m_level == 1)
		return (rand() % 4) + 11;//Easy level 11-14

	else if (m_level == 2) //Normal level 7-10
		return (rand() % 4) + 7;

	return (rand() % 3) + 4; //Hard level 4-6
}
//------------insertBlockTile---------
void Map::insertBlockTile() {

	m_blockTileOfCurrentMap.clear();
	size_t numberOfBlockTiles;
	
	numberOfBlockTiles = getNumOfBlockTiles();//Inserts random
											//number of blocks

	for (size_t i = 0; i < numberOfBlockTiles; i++){

		int row,col;

		searchEmptyTile(col, row);
		m_map[row][col].setFillColor(sf::Color(231, 0, 0));
		m_blockTileOfCurrentMap.push_back(make_pair(row, col));//Saves location of block
	}
}
//The function returns empty tile
//-------------searchEmptyTile----------
void Map::searchEmptyTile(int & col,int & row) const  {

	while (true)
	{
		col = rand() % MAP_SIZE;
		row = rand() % MAP_SIZE;
		if (m_map[row][col].getFillColor() != sf::Color(231, 0, 0)
			&& (col != MAP_SIZE / 2 && row != MAP_SIZE / 2))
			break;
	}

}
//-----------readNextLevel---------------
void Map::readNextLevel() {

	cleanMap();
	insertBlockTile();
	m_numberOfClicks = 0;
}
// The function goes over each vertex
//  and inserts the ribs into the graph .
//------------addEdgeToGraph()----------
void Map::addEdgeToGraph() {

	m_graph.clearEdge();
	for (size_t row = 0; row < MAP_SIZE; row++)
		for (size_t col = 0; col < MAP_SIZE; col++) 
			if (m_map[row][col].getFillColor() != sf::Color(231, 0, 0))
				checkNeighborsAndInsert(row,col);
		
}
//----------setGameOver()-------
void Map::setGameOver() {
	m_GameOver = !m_GameOver;
}
//------------isGameOver------------
bool Map::isGameOver() const {
	return m_GameOver;
}
//-------restartLevel--------
void Map::restartLevel() {

	cleanMap();

	for (size_t i = 0; i < m_blockTileOfCurrentMap.size()-1; i++)
		m_map[m_blockTileOfCurrentMap[i].first][m_blockTileOfCurrentMap[i].second]
											.setFillColor(sf::Color(231, 0, 0));

	addEdgeToGraph();
}
//---------clearMap-----------
void Map::cleanMap() {

	for (size_t row = 0; row < MAP_SIZE; row++)
		for (size_t col = 0; col < MAP_SIZE; col++)
			m_map[row][col].setFillColor(sf::Color::Black);

	//resets the cat location 
	m_catPlayer.setStartLocation();//resets location in map
	//sets position On map
	m_catPlayer.setPosition(m_map[MAP_SIZE / 2][MAP_SIZE / 2].getPosition().x,
		m_map[MAP_SIZE / 2][MAP_SIZE / 2].getPosition().y);
}
//the function searches empty tile to move the cat
//-----------moveCatToEmptyTile--------
void Map::moveCatToEmptyTile() {

	const int row = m_catPlayer.getLoactionInArray()->x
			, col = m_catPlayer.getLoactionInArray()->y;
	int evenShift = 0,//for even row
		oddShift = 0;//for odd row

	if (row % 2 == 0)
		evenShift = -1;
	else oddShift = 1;
	
	//top left node
	if (m_map[row - 1][col + evenShift].getFillColor() != sf::Color(231, 0, 0)) {
		m_catPlayer.setPosition(m_map[row - 1][col + evenShift].getPosition().x
			, m_map[row - 1][col + evenShift].getPosition().y);
		m_catPlayer.setLocation(row - 1, col + evenShift);
	}

	//top right node
	else if (m_map[row - 1][col + oddShift].getFillColor() != sf::Color(231, 0, 0)) {
		m_catPlayer.setPosition(m_map[row - 1][col + oddShift].getPosition().x
			, m_map[row - 1][col + oddShift].getPosition().y);
		m_catPlayer.setLocation(row - 1, col + oddShift);
	}

	//bottom left node
	else if (m_map[row + 1][col + evenShift].getFillColor() != sf::Color(231, 0, 0)) {
		m_catPlayer.setPosition(m_map[row + 1][col + evenShift].getPosition().x
			, m_map[row + 1][col + evenShift].getPosition().y);
		m_catPlayer.setLocation(row + 1, col + evenShift);
	}

	//bottom right node
	else if (m_map[row + 1][col + oddShift].getFillColor() != sf::Color(231, 0, 0)) {
		m_catPlayer.setPosition(m_map[row + 1][col + oddShift].getPosition().x
			, m_map[row + 1][col + oddShift].getPosition().y);
		m_catPlayer.setLocation(row + 1, col + oddShift);
	}
	//left node
	else if (m_map[row][col - 1].getFillColor() != sf::Color(231, 0, 0)) {
		m_catPlayer.setPosition(m_map[row][col - 1].getPosition().x
			, m_map[row][col - 1].getPosition().y);
		m_catPlayer.setLocation(row, col - 1);
	}

	//right node
	else if (m_map[row][col + 1].getFillColor() != sf::Color(231, 0, 0)) {
		m_catPlayer.setPosition(m_map[row][col + 1].getPosition().x
			, m_map[row][col + 1].getPosition().y);
		m_catPlayer.setLocation(row, col + 1);
	}
	else m_level++;
}
//The  function does BFS algorithm and
//sends the cat to the required location
//-----------moveCat--------
void Map::moveCat() {

	int rowAndCol = m_graph.BFS(m_catPlayer.getPoslikeOneDimensional()),
		row = rowAndCol / MAP_SIZE, 
		col = rowAndCol % MAP_SIZE;

	if (rowAndCol == CAUGHT_CAT) 
		moveCatToEmptyTile();
	
	else {//moves cat the the required location
		m_catPlayer.setPosition(m_map[row][col].getPosition().x
			, m_map[row][col].getPosition().y);
		m_catPlayer.setLocation(row, col);
	}
	//checks if we lost
	if (m_graph.isEndOfBoard(rowAndCol)) {
		m_GameOver = true;
		m_numberOfClicks = 0;
		m_infoText[CLICK_CONTENTÉ_BAR].setString("0");
	}
}
//-----------getLevel------------
int Map::getLevel() const {
	return m_level;
}
//-----------notCat---------
bool Map::isCat(const int & row, const int& col ,const sf::Event& event,
											sf::RenderWindow& window) {
	
	if (m_catPlayer.getGlBounds().contains(window.mapPixelToCoords
				({ event.mouseButton.x,event.mouseButton.y })))
		return true;
	return false;
}
//The function gets node and checks the neighbors of current node
//, if they empty the function adds the edge to
//linked list of graph
//-------checkNeighborsAndInsert--------
void Map::checkNeighborsAndInsert(const int row, const int col) {

	
	int evenShift = 0,//for even row
		oddShift = 0,//for odd row
		currentNode = col + row * MAP_SIZE;
	if (row % 2 == 0)
		evenShift = -1;
	else oddShift = 1;

	//top left node
	if (col + evenShift > -1 && row - 1 > -1 && 
		m_map[row-1][col + evenShift].getFillColor() != sf::Color(231, 0, 0))
		m_graph.addEdge(currentNode, (row - 1) * MAP_SIZE + col + evenShift);
	//top right node
	if (col + oddShift  < MAP_SIZE && row - 1 > -1 &&
		m_map[row-1][col+ oddShift].getFillColor() != sf::Color(231, 0, 0))
		m_graph.addEdge(currentNode, (row -1)* MAP_SIZE + col + oddShift);

	//bottom left node
	if (col + evenShift > -1 && row +1 < MAP_SIZE &&
		m_map[row+1][col+ evenShift].getFillColor() != sf::Color(231, 0, 0))
		m_graph.addEdge(currentNode, (row + 1) * MAP_SIZE + col + evenShift);
	//bottom right node
	if (col + oddShift  < MAP_SIZE && row + 1 < MAP_SIZE &&
		m_map[row+1][col+ oddShift].getFillColor() != sf::Color(231, 0, 0))
		m_graph.addEdge(currentNode, (row+1) * MAP_SIZE + col + oddShift);
	//left node
	if (col - 1 > -1  && m_map[row][col-1].getFillColor() != sf::Color(231, 0, 0))
		m_graph.addEdge(currentNode, row * MAP_SIZE + col -1);
	//right node
	if (col + 1 < MAP_SIZE && m_map[row][col+1].getFillColor() != sf::Color(231, 0, 0))
		m_graph.addEdge(currentNode, row * MAP_SIZE + col + 1);

}
//------------constructor---------------
Map::Map()
{
	setInfoText();
}
//------------setInfoClickText-------------------
void Map::setInfoText() {

	for (size_t i = 0; i < 4; i++) {
		m_infoText[i].setColor(sf::Color::Black);
		m_infoText[i].setCharacterSize(45);
	}

	m_infoText[CLICK_BAR].setFont(GameFont::instance()
						.getFont(CANDY_FONT));
	m_infoText[CLICK_BAR].setString("Clicks:");
	m_infoText[CLICK_BAR].setPosition(POS_CLICK_INFO);

	m_infoText[CLICK_CONTENTÉ_BAR].setFont(GameFont::instance()
								.getFont(ASDONUTS_FONT));
	m_infoText[CLICK_CONTENTÉ_BAR].setString("0");
	m_infoText[CLICK_CONTENTÉ_BAR].setPosition(480, 25);

	m_infoText[LEVEL_BAR].setFont(GameFont::instance().
								getFont(CANDY_FONT));
	m_infoText[LEVEL_BAR].setString("Level:");
	m_infoText[LEVEL_BAR].setPosition(POS_LEVEL_INFO);

	m_infoText[LEVEL_CONTENT_BAR].setFont(GameFont::instance()
								.getFont(ASDONUTS_FONT));
	m_infoText[LEVEL_CONTENT_BAR].setString("1");
	m_infoText[LEVEL_CONTENT_BAR].setPosition(790, 25);

}
