#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

#include "Board.hpp"


class Game{

    private:

        sf::RenderWindow *window;
        sf::VideoMode vMode;
        sf::Event event;
        Board sn;

        bool isPlaying, isPaused;
        sf::Font font;
        sf::Text pauseMessage;
        sf::Text subMessage;


        void initWindown();
        void initVar();
        void initText(std::string text);
        void initSubText(std::string text);

    public: 
        Game();
        virtual ~Game();

        bool getIsWinOpen();
        void endGame();
        void update();
        void render();

};