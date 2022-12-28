#ifndef CHOIXNIVEAU_HPP
#define CHOIXNIVEAU_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "define.hpp"

/**
 * @brief Class that manage the menu before the game started
 * 
 */
class ChoixNiveaux{
    private:
        sf::Texture textSel1;
        sf::Texture textSel2;
        sf::Texture textSel3;

        sf::Sprite spriteSel1;
        sf::Sprite spriteSel2;
        sf::Sprite spriteSel3;

        int choix;
        int menuUpdate;

    public:
        ChoixNiveaux(){
            textSel1.loadFromFile("ressources/select1.png");
            textSel2.loadFromFile("ressources/select2.png");
            textSel3.loadFromFile("ressources/select3.png");
            
            spriteSel1.setPosition(0, 0);
            spriteSel2.setPosition(0, 0);
            spriteSel3.setPosition(0, 0);


            choix = 1;
            menuUpdate = 1;
        }

        int getMenuUpdate(){
            return menuUpdate;
        }

        int getChoix(){
            return choix;
        }

        void draw(sf::RenderWindow &app){
            app.clear();
            spriteSel1.setTexture(textSel1);
            spriteSel2.setTexture(textSel2);
            spriteSel3.setTexture(textSel3);


            if(choix == 1){
                app.draw(spriteSel1);
            }
            else if(choix == 2){
                app.draw(spriteSel2);
            }
            else if(choix == 3){
                app.draw(spriteSel3);
            }
            app.display();
        }

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
                    menuUpdate = 0;

                } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    if(choix == 1){
                        choix = 3;
                    }else choix --;
                
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                    if(choix == 3){
                        choix = 1;
                    }else choix ++;
                }
            }
        }
    };
#endif