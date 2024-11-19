#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"


int main(){
    Game g;

   // unsigned seed = time(0);
    //std::srand(seed);
    
    while(g.getIsWinOpen()){

        g.update();

        g.render();

    }

    return 0;
}