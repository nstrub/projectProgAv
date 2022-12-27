#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "bloc.hpp"

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
        bool canGo;
        Bloc blocOn;


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
        Player(int coordX, int coordY, int postabX, int postabY, Bloc blocGived){
            haut = 50;
            larg = 50;
            canGo = true;
            posX = coordX;
            posY = coordY;
            posTabX = postabX;
            posTabY = postabY;
            sprite.setPosition(coordX,coordY);
            texture.loadFromFile("ressources/stance.png");
            setBloc(blocGived);
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


        /**
         * @brief Set the Go object
         * 
         * @param newGo 
         */
        void setGo(bool newGo){
            canGo = newGo;
        }

        void setBloc(Bloc newBloc){
            blocOn = newBloc;
        }


        /**
         * @brief Move the player on the x axis
         * 
         */
        void moveLeft(){
//            infoPlayerMove();
            int ancienX = posX;
            int ancienY = posY;
            if(canGo){
                posX -= MOVEMENT;
                posTabX--;
                sprite.setPosition(posX, posY);
                texture.loadFromFile("ressources/avGauche.png");
            }
            else{
                posX = ancienX;
                posY = ancienY;
                sprite.setPosition(posX, posY);
                changeGo(true);
            }
        }

        void moveRight(){
//            infoPlayerMove();
            int ancienX = posX;
            int ancienY = posY;
            if(canGo){
                posX += MOVEMENT;
                posTabX++;
                sprite.setPosition(posX, posY);
                texture.loadFromFile("ressources/avDroite.png");

            }
            else{
                posX = ancienX;
                posY = ancienY;
                sprite.setPosition(posX, posY);
                changeGo(true);
            }
        }

        /**
         * @brief Move the player on the x axis
         * 
         */
        void moveDown(){
//            infoPlayerMove();
            int ancienX = posX;
            int ancienY = posY;
            if(canGo){
                posY = posY + MOVEMENT;
                posTabY++;
                sprite.setPosition(posX, posY);
                texture.loadFromFile("ressources/avBas.png");
            }
            else{
                posX = ancienX;
                posY = ancienY;
                changeGo(true);
            }
        }

        void moveUp(){
//            infoPlayerMove();
            int ancienX = posX;
            int ancienY = posY;
            if(canGo){
                posY = posY - MOVEMENT;
                posTabY--;
                sprite.setPosition(posX, posY);
                texture.loadFromFile("ressources/avHaut.png");
            }
            else{
                posX = ancienX;
                posY = ancienY;
                changeGo(true);
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
         * @brief autorize the player to move or not
         * 
         */
        void changeGo(bool go){
            canGo = go;
        }

        /**
         * @brief Rool the player back to his previous position (if he exit the blocs for exemple)
         * 
         */
        void replacePlayer(){
            sprite.setPosition(blocOn.getSprite().getPosition().x,
                               blocOn.getSprite().getPosition().y);
        }

        // void infoPlayerMove(){
        //     if(blocOn.getisFree()){
        //         canGo = true;
        //     }
        //     else{
        //         canGo = false;
        //         printf("player met cango faux\n");
        //     }
        // }

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

                if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    moveRight();
                }

                if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                    moveLeft();
                }

                 if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    moveUp();
                }
                    
                 if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    moveDown();
                }
            }
            //printf("CanGo : %d %d %d\n",canGo, posX, posY);
        }
};


#endif