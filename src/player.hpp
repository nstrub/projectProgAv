#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * @brief Class that manage what is related to the player
 * 
 */
class Player{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        int posY, posX;

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
        Player(int coordX, int coordY){
            sprite.setPosition(coordX,coordY);
            texture.loadFromFile("ressources/perso.png");
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
         * @brief Move the player on the x axis
         * 
         */
        void moveX(int mX){
            printf("PosX avant : %d",this->getX());
            sprite.setPosition(mX + posX,posY);
            printf("PosX après : %d",this->getX());
        }
        /**
         * @brief Move the player on the x axis
         * 
         */
        void moveY(int mY){
            sprite.setPosition(posX,mY + posY);
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
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    app.close();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    moveX(1);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    moveX(-10);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                    moveY(10);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    moveY(-10);
            }
        }
};


#endif