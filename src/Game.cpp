#include "Game.hpp"


void Game::initWindown(){
    this->vMode.height = 600;
    this->vMode.width = 800;
    this->window = new sf::RenderWindow(vMode, "Snake", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(10);
}

void Game::initVar(){
    this->window = NULL;
    this->isPlaying = false;

}

void Game::initText(std::string text){

    std::string message = text;
    this->font.loadFromFile("res/Roboto-Black.ttf");
    this->pauseMessage.setString(message);
    this->pauseMessage.setCharacterSize(30);
    this->pauseMessage.setFont(font);
    int lenX = pauseMessage.getGlobalBounds().getSize().x/2;
    int lenY = pauseMessage.getGlobalBounds().getSize().y/2;
    std::cout<<"lenX: " <<lenX << ", lenY: " << lenY << "\n";
    this->pauseMessage.setPosition(sf::Vector2f(400-lenX, 300-lenY));
    this->pauseMessage.setFillColor(sf::Color(200.0f, 200.0f, 200.0f));

}

void Game::initSubText(std::string text){

    std::string message = text;
    this->font.loadFromFile("res/Roboto-Black.ttf");
    this->subMessage.setString(message);
    this->subMessage.setCharacterSize(18);
    this->subMessage.setFont(font);
    int lenX = subMessage.getGlobalBounds().getSize().x/2;
    int lenY = subMessage.getGlobalBounds().getSize().y/2;
    std::cout<<"lenX: " <<lenX << ", lenY: " << lenY << "\n";
    this->subMessage.setPosition(sf::Vector2f(400-lenX, 400-lenY));
    this->subMessage.setFillColor(sf::Color(200.0f, 200.0f, 200.0f));

}


Game::Game(){
    initVar();
    initWindown();
    initText("PRESS SPACE TO START");
    sn.setWinAndEvent(window);
}

Game::~Game(){
    delete window;
}

bool Game::getIsWinOpen(){
    return window->isOpen();
}

void Game::update(){
        
        //pollevents
        while(window->pollEvent(event)){
            if(event.type == event.Closed){
                window->close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window->close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                if(isPlaying && !sn.getGameOver() && !isPaused){
                    std::cout<<"paused!";
                    initText("GAME PAUSED");
                    initSubText("press space to continue");
                    isPaused = true;
                }else if(!isPlaying){
                    isPlaying = true;
                }else if(isPaused){
                    isPlaying = true;
                    isPaused = false;
                }

            }

            
            if(isPlaying)
                 sn.pollEvent(event);
        }

        if(isPlaying && !isPaused){
            sn.update();

        }

        if(sn.getGameOver()){   
            initText("YOU UNALIVED!");
            initSubText("press space to retry");
            //need to reset the game
            endGame();
        }
}

void Game::endGame(){

    isPlaying = false;
    sn.resetGame();
    //add resetting stuff
    sn.setGameOver(false);
}

void Game::render(){

        //update

        if(isPlaying && !isPaused){
            window->clear();
            //draw game
            sn.render();
        }else if(!isPlaying && !isPaused){
            window->clear(sf::Color(20, 20, 20));
            //draw pause messeage
            window->draw(pauseMessage);
            window->draw(subMessage);
        }else if(isPaused){
            window->clear(sf::Color(30, 30, 30));
            window->draw(pauseMessage);
            window->draw(subMessage);
        }



        //render
        window->display();
}