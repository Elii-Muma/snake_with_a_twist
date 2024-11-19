#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <list>
#include "List.hpp"
#include <sstream>

class Board{

    private:

        struct snk{
            sf::RectangleShape box;
            int x, y;
            int scale;
        };

        sf::RenderWindow *window;

        //sf::RectangleShape tail;
        std::vector<sf::Vector2f> tailPos;
        std::vector<sf::RectangleShape> t;
        std::vector<sf::RectangleShape> tRev;
        std::vector<sf::RectangleShape> lunchBox;//cotainer for food
        sf::RectangleShape snake, food, obs1, obs2;
        sf::Clock clock;
        sf::Clock *moveClock;
        std::ostringstream pointsStr;
        sf::Text pointsText;
        sf::Font font;
        
        //std::list<sf::RectangleShape> tails;

        bool lClick, rClick, dClick, uClick;
        bool mLeft, mRight, mUp, mDown;
        bool eaten, drawTail;
        bool clicked;
        bool isColliding, isCollide2, isfoodTrans;
        bool gameOver;
        float currentX, currentY;
        float scale;
        float xPos, yPos;
        float speed, totalS;
        int col, row;
        int color;
        int points;
        int count, tyme;
        int total, size;

        unsigned seed;

        void initSnake();
        void initVar();
    public:
        Board();

        void addObstacles();
        void initTail();
        void initFood();
        void moveSnake();
        void eat();
        void hasEaten();
        void tailMovement();
        bool checkObsCollision(sf::RectangleShape s1, sf::RectangleShape s2);
        void update();
        void render();
        void drawText();
        void pollEvent(sf::Event &event);
        void resetGame();
        void setWinAndEvent(sf::RenderWindow *window);
        sf::RectangleShape getSnake();
        bool getGameOver();
        void setGameOver(bool flag);
};