#ifndef MENU_HPP
#define MENU_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "define.hpp"

/**
 * @brief Class that manage the menu before the game started
 * 
 */
class Menu{
    private:
        sf::Texture textPlayBig;
        sf::Texture textPlaySmall;
        sf::Texture textRuleSmall;
        sf::Texture textRuleScreen;
        sf::Texture textQuitSmall;
        sf::Texture textQuitBig;

        sf::Sprite spritePlayBig;
        sf::Sprite spritePlaySmall;
        sf::Sprite spriteRuleSmall;
        sf::Sprite spriteRuleScreen;
        sf::Sprite spriteQuitSmall;
        sf::Sprite spriteQuitBig;

        int ruleOpen = 0;

        int menuUpdate;
        int choix;

    public:
        Menu(){
            textPlaySmall.loadFromFile("ressources/playTiny.png");
            textPlayBig.loadFromFile("ressources/playGrand.png");
            textRuleSmall.loadFromFile("ressources/ruleTiny.png");
            textQuitBig.loadFromFile("ressources/quitGrand.png");
            textQuitSmall.loadFromFile("ressources/quitTiny.png");
            textRuleScreen.loadFromFile("ressources/ruleScreen.png");

            spritePlayBig.setPosition(120, 100);
            spriteQuitBig.setPosition(130, 220);
            spriteRuleScreen.setPosition(0, 0);

            spritePlaySmall.setPosition(230, 100);
            spriteQuitSmall.setPosition(200, 280);
            spriteRuleSmall.setPosition(200, 430);

            choix = 0;
            menuUpdate = 1;
        }
        
        /**
         * @brief Return the value that check if the player as chosen the play button
         * 
         * @return int 
         */
        int getMenuUpdate(){
            return menuUpdate;
        }

        /**
         * @brief draw the menu to the screen
         * 
         * @param app 
         */
        void draw(sf::RenderWindow &app){
            app.clear();
            spritePlayBig.setTexture(textPlayBig);
            spriteQuitBig.setTexture(textQuitBig);
            spritePlaySmall.setTexture(textPlaySmall);
            spriteQuitSmall.setTexture(textQuitSmall);
            spriteRuleScreen.setTexture(textRuleScreen);
            spriteRuleSmall.setTexture(textRuleSmall);
            spriteRuleScreen.setTexture(textRuleScreen);

            if(choix == 0){
                app.draw(spritePlayBig);
                app.draw(spriteQuitSmall);
                app.draw(spriteRuleSmall);
            }
            else if(choix == 1){
                app.draw(spritePlaySmall);
                app.draw(spriteQuitBig);
                app.draw(spriteRuleSmall);
            }
            else if(choix == 2){
                if(ruleOpen % 2 == 0){
                    app.draw(spriteRuleScreen);
                }else{
                    app.draw(spritePlaySmall);
                    app.draw(spriteQuitSmall);
                    app.draw(spriteRuleSmall);
                }
            }
            app.display();
        }

        /**
         * @brief Handle the moves of the player such as his keyboard
         * 
         * @param app 
         */
        void handleMoves(sf::RenderWindow &app){
            sf::Event event;
            while(app.pollEvent(event)){
                if(event.type == sf::Event::Closed){
                    app.close();
                    exit(0);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    app.close();
                    exit(0);
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    if(choix == 0)
                        menuUpdate = 0;
                    else if(choix == 1){
                        app.close();
                        exit(0);
                    }
                    else if(choix == 2){
                        ruleOpen ++;
                    }
                
                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    if(choix == 0 || choix == 1)
                        choix++;
                    else
                        choix = 0;
                
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)|| sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    if(choix == 2 || choix == 1)
                        choix --;
                    else
                        choix = 2;
                }
            }
        }
    };
#endif