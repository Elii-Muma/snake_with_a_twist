#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class List{

    private:
        typedef struct node{
            sf::RectangleShape data;
            node *next;
        }* nodePtr;

        nodePtr head;
        nodePtr curr, temp;
        nodePtr tail;

    public:
        List();

        void insertAtStart(sf::RectangleShape data);
        void insertAtEnd();
        void deleteNode();
        sf::RectangleShape operator[](int i);
        int size();
        bool isEmpty();



};