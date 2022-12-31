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
        bool isClosed;
        bool isButton;
        bool isExit;
        // bool isFree;
        bool isWall;
        char letter;
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
        Bloc(int x, int y, char lettre){
            haut = 50;
            larg = 50;
            letter = lettre;
            isTrapped = false;
            isClosed = false;
            isButton = false;
            isExit = false;
            isWall = false;

            switch (lettre) {
                case '@': isButton = true; break;
                case 'F': isExit = true; break;
                case '#': isWall = true; break;
                case '=': isClosed = true; lettre = '#';
            }

            std::string debut = "ressources/";
            std::string fin = ".png";
            std::string link = debut + lettre + fin;

            texture.loadFromFile(link);
            sprite.setPosition(x, y);
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

        /**
         * @brief place the bloc in the right position
         * 
         * @param x 
         * @param y 
         */
        void placer(int x, int y){
            sprite.setPosition(x,y);
        }

        sf::Sprite getSprite(){
            return sprite;
        }

        bool getisFree(){
            return !getIsWall();
        }

        bool getIsExit(){
            return isExit;
        }

        bool getIsWall(){
            return isWall;
        }

        bool getIsButton(){
            return isButton;
        }

        bool getIsClosed(){
            return isClosed;
        }

        char getChar(){
            return letter;
        }

        void changeClosed() {
            isClosed = !isClosed;
        }

        /**
         * @brief Change the texture of the blocs from its char on the .map
         * 
         * @param c 
         */
        void changeTexture(char c) {
            std::string debut = "ressources/";
            std::string fin = ".png";
            std::string link = debut + c + fin;
            texture.loadFromFile(link);
        }

        /**
         * @brief Draw the bloc on the screen
         * 
         * @param app 
         */
        void draw(sf::RenderWindow &app){
            sprite.setTexture(texture);
            app.draw(sprite);
        }
};

#endif