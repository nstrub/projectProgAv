#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/**
 * @brief Class that manage what is related to the player
 * 
 */
class Player{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        int posY;
        int posX;
        int larg;
        int haut;
        int posTabX;
        int posTabY;
        int direction;
        bool canGo;

    public:
        /**
         * @brief Create a new player Object 
         *   
         */
        Player(){}

        /**
         * @brief Create a new player Object
         * @param coordX Coordinate X
         * @param coordY Coordinate Y 
         */
        Player(int coordX, int coordY, int postabX, int postabY){
            haut = 50;
            larg = 50;
            canGo = false;
            posX = coordX;
            posY = coordY;
            posTabX = postabX;
            posTabY = postabY;
            sprite.setPosition(coordX,coordY);
            texture.loadFromFile("ressources/perso.png");
        }

        /**
         * @brief Get the x position in the tab
         * 
         */
        int getposTabX(){
            return posTabX;
        }

        /**
         * @brief Get the y position in the tab
         * 
         */
        int getposTabY(){
            return posTabY;
        }


        /**
         * @brief Get the x coordinate of the Player
         * 
         * @return int 
         */
        int getX() {
            return sprite.getPosition().x;
        }

        /**
         * @brief Get the y coordinate of the Player
         * 
         * @return int 
         */
        int getY() {
            return sprite.getPosition().y;
        }

        /**
         * @brief Get the Sprite object
         * 
         * @return sf::Sprite 
         */
        sf::Sprite getSprite() {
            return sprite;
        }

        // A EFFACER MTN ON GERE COLLISION PAR LES SPRITES
        bool isOut(int maxX,int maxY){
            if (posX > maxX | posX < 0 | posY > maxY | posY < 0){
                return true;
            }
            return false;
        }

        // ////Quand il sort, c'est dans les mooves à gérer
        // ////FCT COLLISION QQU PART ET DANS
        /**
         * @brief Move the player on the x axis
         * 
         */
        void moveLeft(){
            int ancienX = posX;
            int ancianY = posY;
            if(!isOut(500,500)){
                posX += -MOVEMENT;
                sprite.setPosition(posX, posY);
            }
            else{
                posX = ancienX;
                posY = ancianY;
            }
        }

        void moveRight(){
            int ancienX = posX;
            int ancianY = posY;
            if(!isOut(500,500)){
                posX += MOVEMENT;
                sprite.setPosition(posX, posY);
            }
            else{
                posX = ancienX;
                posY = ancianY;
            }
        }

        /**
         * @brief Move the player on the x axis
         * 
         */
        void moveDown(){
            int ancienX = posX;
            int ancianY = posY;
            if(!isOut(500,500)){
                posY = posY + MOVEMENT;
                sprite.setPosition(posX, posY);
            }
            else{
                posX = ancienX;
                posY = ancianY;
            }
        }

        void moveUp(){
            int ancienX = posX;
            int ancianY = posY;
            if(!isOut(500,500)){
                posY = posY - MOVEMENT;
                sprite.setPosition(posX, posY);
            }
            else{
                posX = ancienX;
                posY = ancianY;
            }
        }


        /**
         * @brief Show texture of the Player on screen
         * 
         * @param app 
         */
        void draw(sf::RenderWindow &app) {
            sprite.setTexture(texture);
            app.draw(sprite);
        }

        /**
         * @brief Change direction :
         * - 1 --> Left
         * - 2 --> Right
         * - 3 --> Up
         * - 4 --> Down
        */
        void changeDirection(int dir){
            direction = dir;
        }

        /**
         * @brief autorize the player to move or not
         * 
         */
        void changeGo(bool go){
            canGo = go;
        }

        /**
         * @brief Send to the world where the player is gonna move
         * 
         */
        int getdirection(){
            return direction;
        }

        //ATTENTION : BUG LORSQUE S ET D ou autre appuyés en même temps
        /**
         * @brief Handle the moves of the player
         * 
         * @param app
         */
        void handleMoves(sf::RenderWindow &app){
            sf::Event event;
            while(app.pollEvent(event)){
                //Close the game with the x on the window or escape
                if (event.type == sf::Event::Closed)
                    app.close();
                
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    app.close();

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    
                    moveRight();
                }

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                    moveLeft();
                }

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    moveUp();
                }
                    
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    moveDown();
            }
        }
};


#endif