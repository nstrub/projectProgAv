#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.hpp"

/**
 * @brief Class that manage the game
 * 
 */
class Game{
    private:
        Player player;

    public:
        /**
         * @brief Construct new game Object
         * 
         */
        Game(){
            player = Player(50,50);
        }
        /**
         * @brief Handle player moves in the game
         * 
         * @param app
         */
        void handleMoves(sf::RenderWindow &app){
            player.handleMoves(app);
        }
        
        /**
         * @brief Show texture on screen
         * 
         * @param app
         */
        void draw(sf::RenderWindow &app){
            app.clear();
            player.draw(app);
            app.display();
        }
};

#endif