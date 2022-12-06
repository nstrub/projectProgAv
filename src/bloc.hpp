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
        bool isTrapped;
        bool isDoor;
        bool isButton;
        bool isExit;
        bool isFree;
        int haut;
        int larg;
        sf::Texture texture;
        sf::Sprite sprite;

    public:
        /**
         * @brief Create a new Bloc Object
         * 
         */
        Bloc(){
            texture.loadFromFile("ressources/0.png");
            sprite.setPosition(0,0);
        }
        Bloc(int x, int y, bool isWall, char lettre){
            haut = 50;
            larg = 50;

            std::string debut = "ressources/";
            std::string fin = ".png";
            std::string link = debut + lettre + fin;

            texture.loadFromFile(link);
            // if (lettre == 'D') texture.loadFromFile("ressources/mur.png");
            // else if (lettre == 'F') texture.loadFromFile("ressources/arrivee.png");
            // else texture.loadFromFile("ressources/sol.png");
            sprite.setPosition(x, y);
            
            isTrapped = false;
            isDoor = false;
            isButton = false;
            isExit = false;
            isFree = !isWall;
        }

        /**
         * @brief Getters from the bloc
         * 
         */
        //Positions
        int getX(){
            return sprite.getPosition().x;
        }
        int getY(){
            return sprite.getPosition().y;
        }
        //Sizes
        int getW(){
            return sprite.getGlobalBounds().width;
        }
        int getH(){
            return sprite.getGlobalBounds().height;
        }

        void placer(int x, int y){
            sprite.setPosition(x,y);
        }

        sf::Sprite getSprite(){
            return sprite;
        }

        bool getisFree(){
            return isFree;
        }

        void draw(sf::RenderWindow &app){
            sprite.setTexture(texture);
            app.draw(sprite);
        }
};

#endif