#ifndef BLOC_HPP
#define BLOC_HPP

#include <string.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

/**
 * @brief Class that is one bloc for the entire map
 * 
 */
class Bloc{
    private:
        int coordX;
        int coordY;
        bool isTrapped;
        bool isDoor;
        bool isButton;
    public:
        /**
         * @brief Create a new Bloc Object
         * 
         */
        Bloc(int x, int y){
            coordX = x;
            coordY = y;
            isTrapped = false;
            isDoor = false;
            isButton = false;
        }

        /**
         * @brief Getters from the bloc
         * 
         */
        int getX(){
            return coordX;
        }
        int getY(){
            return coordY;
        }

        
};

#endif