#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "choixNiveaux.hpp"


int main() {
    sf::RenderWindow app(sf::VideoMode(WINDOW_X, WINDOW_Y), "Tesoro");
    app.setFramerateLimit(60);

    Menu menu = Menu();
    ChoixNiveaux choixLvl = ChoixNiveaux();

    int niveau = 1;

    Game game = Game(); 

    while (app.isOpen()) {
        while(menu.getMenuUpdate() == 1){           //Ouverture du premier menu
            menu.handleMoves(app);
            menu.draw(app);
        }
        if(game.getIsContruct() == 0){
            while(choixLvl.getMenuUpdate() == 1){   //Ouverture du menu de selection de niveau
                choixLvl.handleMoves(app);
                choixLvl.draw(app);
            }
            game = Game(5, choixLvl.getChoix());    //Creation du jeu en fonction du niveau choisi
        }

        game.handleMoves(app);
        game.draw(app);
    }

    return 0;
}