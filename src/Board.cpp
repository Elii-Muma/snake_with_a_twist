#include "Board.hpp"

void Board::initSnake(){
    snake.setFillColor(sf::Color::White);
    snake.setSize(sf::Vector2f(scale, scale));
    snake.setPosition(sf::Vector2f(40.0f, 40.f));
}

void Board::initTail(){
    sf::RectangleShape tail;
    
    //to change limit
    color = rand()%200;

    tail.setFillColor(sf::Color(color, color, color));
    tail.setSize(sf::Vector2f(scale, scale));

    //t.emplace(t.begin(), tail);
    //t.insert(t.begin(), tail);

    //find better way(to change method, need to be faster)
    tRev.push_back(tail);    
    //have the new tail go to the beginning of the arr
    //O(n^2), becomes slower as n goes up
    for(int j=tRev.size()-1; j>=0; j--){
        t.push_back(tRev[j]);
    }
}

void Board::initFood(){

    for(int i=0; i<size; i++){
        this->yPos = rand()%row;
        this->xPos = rand()%col;

        yPos *= scale;
        xPos *= scale;

        food.setFillColor(sf::Color::Red);
        food.setSize(sf::Vector2f(scale, scale));
        food.setPosition(xPos, yPos);
        lunchBox.push_back(food);
    }

}

void Board::initVar(){

    this->speed = 1.0f;
    this->scale = 20.0f;

    this->lClick = false;
    this->rClick = false;
    this->uClick = false;
    this->dClick = false;

    this->mLeft = false;
    this->mRight = false;
    this->mDown = false;
    this->mUp = false;

    this->gameOver = false;
    this->isColliding = false;

    this->total = 0;

    this->eaten = false;
    this->drawTail = false;

    this->count = 50;
    this->points = 0;

    this->font.loadFromFile("res/Roboto-Regular.ttf");
    this->pointsText.setCharacterSize(18);
    this->pointsText.setFillColor(sf::Color::White);
    this->pointsText.setFont(font);
    this->pointsText.setPosition(sf::Vector2f(700, 0));

    this->size = 1;

    //OBSTACLES
    /*
        they will be squares on the screen 
        l8r could be updated to levels
        maybe be have them generate @ random positions
    */
    obs1.setFillColor(sf::Color(240, 240, 240));
    obs1.setSize(sf::Vector2f(200.0f, 100.0f));
    obs1.setPosition(sf::Vector2f(100, 200));

    obs2.setFillColor(sf::Color(240, 240, 240));
    obs2.setSize(sf::Vector2f(100, 400));
    obs2.setPosition(sf::Vector2f(600, 60));


    //how many col and rows are on the thing
    row = 600/scale;
    col = 800/scale;

}

//CONTRUCTOR
Board::Board(){

    seed = time(0);
    moveClock = new sf::Clock();

    std::srand(seed);
    clock.restart();

    initVar();
    initSnake();
    initFood();

}

//the "no-eating yourself" bug may have originated from here
void Board::moveSnake(){


        if(lClick && !mRight && !rClick){
            mLeft = true;
            mDown = false;
            mUp = false;

            lClick = false;
        }

        if(rClick && !mLeft && !lClick){
            mRight = true;
            mDown = false;
            mUp = false;

            rClick = false;
        }

        if(uClick && !mDown && !dClick){

            mUp = true;
            mLeft = false;
            mRight = false;

            uClick = false;
        }

        if(dClick && !mUp && !uClick){
            mDown = true;
            mLeft = false;
            mRight = false;

            dClick = false;
        }

        if(mLeft){
            if(snake.getPosition().x > 0){
                snake.move(-scale, 0.0f);//which direction you're moving, either up, down or...
            }else
                gameOver = true;
        }

        if(mRight){
            if(snake.getPosition().x < (800-scale)){
                snake.move(scale, 0.0f);//which direction you're moving, either up, down or...
            }else
                gameOver = true;
        }

        if(mUp){
            if(snake.getPosition().y > 0){
                snake.move(0.0f, -scale);//which direction you're moving, either up, down or...
            }else 
                gameOver = true;
        }

        if(mDown){
            if(snake.getPosition().y < (600-scale)){
                snake.move(0.0f, scale);//which direction you're moving, either up, down or...
            }else
                gameOver = true;
        } 
        
        if(isColliding || isCollide2){
            int rx = rand()%col;
            int ry = rand()%row;
            snake.setPosition(sf::Vector2f(rx*scale, ry*scale));
            //set its position to its current   
        }

}

void Board::eat(){

    //index 0 is the newest snake added
    //so we actually add new snakes at the beginning of the snake array and not the end
    if(eaten){
        drawTail = true;
        //bug of corner blocks starts here to the swaping part
        if(!t.empty()){
            t.clear();
        }
        initTail();
        eaten = false;
    }

}

void Board::hasEaten(){

    for(int i=0; i<lunchBox.size(); i++){

        if(snake.getGlobalBounds().contains(lunchBox[i].getPosition())){
            eaten = true;
            //lunchBox.erase(i);
            lunchBox.erase(lunchBox.begin()+i);
            tailPos.push_back(sf::Vector2f(snake.getPosition()));
            points += 1;
            total+=1;

            if(totalS >= 0 && (points % 5 == 0 )){
                speed -= 0.1;
            }
        }  
    }

}

void Board::tailMovement(){

    if(!t.empty()){
        if(tailPos.size() == total){
            for(int i=0; i<tailPos.size()-1; i++){
                tailPos[i] = tailPos[i+1];
            }
        }

        tailPos[tailPos.size()-1] = snake.getPosition(); //last one to current pos
        
        //the newest pos is at the end of the pos arr
        //the newest tail is at the beginning of the tail arr
        //newest tail gets the first elem of pos array
        for(int i=0; i<t.size(); i++){
            t[i].setPosition(tailPos[i].x, tailPos[i].y);
        }
    }
}

//AABB COLLISION DETECTION
bool Board::checkObsCollision(sf::RectangleShape s1, sf::RectangleShape s2){

    if(s1.getGlobalBounds().contains(s2.getPosition())){
        return true;
    }else
        return false;

    //  if(s1.getPosition().x <= s2.getPosition().x + s2.getGlobalBounds().width &&
    //     s1.getPosition().x + s1.getGlobalBounds().width >= s2.getPosition().x &&
    //     s1.getPosition().y <= s2.getPosition().y + s2.getGlobalBounds().height &&
    //     s1.getPosition().y + s1.getGlobalBounds().height >= s2.getPosition().y){

    //         return true;
    //     }else
    //         return false;

}

//the order of event is apprently very important here
void Board::update(){
    
    float delta = 0.1f;

    if(moveClock->getElapsedTime().asSeconds() >= delta * speed){
        totalS = delta * speed;

        moveClock->restart();
        if(lunchBox.empty()){
            initFood();
        }

        //eat -> move the tail in the arr -> move the snakes pos -> add the score and other stuffs    
        eat();
        tailMovement();
        moveSnake();
        hasEaten();

        if(checkObsCollision(obs1, snake)){
            isColliding = true;
        }else   
            isColliding = false;

        if(checkObsCollision(obs2, snake)){
            isCollide2 = true;
        }else
            isCollide2 = false;   

        for(int i=0; i<lunchBox.size(); i++){

            if(obs1.getGlobalBounds().contains(lunchBox[i].getPosition()) 
            || obs2.getGlobalBounds().contains(lunchBox[i].getPosition())){

                int rx = rand()%col;
                int ry = rand()%row;
                lunchBox[i].setPosition(sf::Vector2f(rx*scale, ry*scale));
                isfoodTrans = true;
            }else   
                isfoodTrans = false;
        }
    }
}



void Board::render(){

        drawText();

        //draw
        for(int i=0; i<lunchBox.size(); i++){
            this->window->draw(lunchBox[i]);
        }

        for(int i=0; i<t.size(); i++){
            this->window->draw(t[i]);
        }
        this->window->draw(snake);
        this->window->draw(pointsText);
        this->window->draw(obs1);
        this->window->draw(obs2);
        
}

void Board::drawText(){

    pointsStr.str("");
    pointsStr << "Points: " << points;
    pointsText.setString(pointsStr.str());
}

void Board::resetGame(){

    initVar();
    tailPos.clear();
    t.clear();
    tRev.clear();
    lunchBox.clear();

    initSnake();
    std::cout<<"size: " << lunchBox.size() << "\n";
    initFood();

}


void Board::pollEvent(sf::Event &event){
        

    switch(event.type){
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Left){
                lClick = true;
            }
            if(event.key.code == sf::Keyboard::Right){
                rClick = true;
            }
            if(event.key.code == sf::Keyboard::Up){
                uClick = true;
            }
            if(event.key.code == sf::Keyboard::Down){
                dClick = true;
            }

            break;

        case sf::Event::KeyReleased:
        
            if(event.key.code == sf::Keyboard::Left){
                lClick = false;
            }
            if(event.key.code == sf::Keyboard::Right){
                rClick = false;
            }
            if(event.key.code == sf::Keyboard::Up){
                uClick = false;
            }
            if(event.key.code == sf::Keyboard::Down){
                dClick = false;
            }

            break;
        default:
            break;
    }
}

void Board::setWinAndEvent(sf::RenderWindow *window){
    this->window = window;
    //this->event = event;
}

sf::RectangleShape Board::getSnake(){
    return snake;
}

bool Board::getGameOver(){
    return gameOver;
}

void Board::setGameOver(bool flag){
    this->gameOver = flag;
}