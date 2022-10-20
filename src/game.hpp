#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "map.hpp"

/**
 * @brief Class that manage the game
 * 
 */
class Game{
    private:
        Player player;
        Map map;
        int **tab;
        int sizeTab;

    public:
        /**
         * @brief Construct new game Object
         * 
         */
        Game(int size){
            sizeTab = size;
            player = Player(100,100,0,0);
            map = Map();
            tab[sizeTab][sizeTab];    //Récup les données de maps
            //Placer player au coordonnée de son départ (0,0 par défaut)
        }

        /**
         * @brief Handle player moves in the game
         * 
         * @param app
         */
        void handleMoves(sf::RenderWindow &app){
            // if (player.getdirection() == 1){
            //     if(player.getposTabX() + 1 < sizeTab){  //Aussi ajouter les murs etc...
            //         player.changeGo(true);
            //     }
            // }
            player.handleMoves(app);
        }
        
        /**
         * @brief Show texture on screen
         * 
         * @param app
         */
        void draw(sf::RenderWindow &app){
            app.clear();
            map.draw(app);
            player.draw(app);
            app.display();
        }
};

#endif