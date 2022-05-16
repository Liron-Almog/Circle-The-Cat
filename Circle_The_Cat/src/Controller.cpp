#include "Controller.h"
#include "GameTexture.h"
#include "Const.h"
#include <chrono>
#include <thread>

//----------------runGame------------------
void Controller::runGame() {
    
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE_W, SCREEN_SIZE_H), 
                                "Circle The Cat", sf::Style::Close);

    m_map.createMap();
    m_map.drawMap(window);
    handleEvents(window);
  
}
//The function handles events  
//------------------handleEvents--------------
void Controller::handleEvents(sf::RenderWindow & window) {

    int level = FIRST_LEVEL;
 
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Event::MouseButtonPressed == event.type) {
                if (m_map.fillTile(event, window)) {//if succeed  to filled tile 
                    m_map.addEdgeToGraph();
                    m_map.moveCat();
                    m_map.drawMap(window);
                    gameStatus(level, window);
                }
            }
        }
    }
}

//The function gets the current level and checks if 
// we passed to the next level or we lost .
//--------------gameStatus-------------------
void Controller::gameStatus(int & currentLevel, sf::RenderWindow& window) {

    if (currentLevel != m_map.getLevel()) {
        currentLevel++;
        m_map.readNextLevel();
        drawStatus(window,NEXT_LEVEL);
    }
    if (m_map.isGameOver()) {
        m_map.setGameOver();
        m_map.restartLevel();
        drawStatus(window, GAME_OVER);
    }
}

//The function draws the next level screen or game over screen according to 
// second paramter.
//--------------drawStatus-------------------
void Controller::drawStatus(sf::RenderWindow& window, const int numberOfPhoto) {

    window.clear(sf::Color::Black);
    window.draw(m_transtionScreens[numberOfPhoto]);
    window.display();
    //display for 2 sec
    std::this_thread::sleep_for(std::chrono::seconds(SHOW_TIME));
    m_map.drawMap(window);
}
//--------------Constuctor-------------------
Controller::Controller()
{
    m_transtionScreens[NEXT_LEVEL].setTexture(*GameTexture::instance()
        .getPassScreenTexture(NEXT_LEVEL));
    m_transtionScreens[GAME_OVER].setTexture(*GameTexture::instance()
        .getPassScreenTexture(GAME_OVER));
    m_transtionScreens[NEXT_LEVEL].setScale(PHOTO_SIZE, PHOTO_SIZE);
    m_transtionScreens[GAME_OVER].setScale(PHOTO_SIZE, PHOTO_SIZE);
    m_transtionScreens[NEXT_LEVEL].setPosition(130, 0);
    m_transtionScreens[GAME_OVER].setPosition(130, 0);

}