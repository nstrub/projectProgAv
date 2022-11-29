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
        char *tab;
        int sizeTab;
        Bloc *blocs;
        int nbBlocs;

    public:
        /**
         * @brief Construct new game Object
         * 
         */
        Game(int size){
            map = Map("ressources/niveau1.map");
            sizeTab = nbBlocs = map.size();
            tab = map.getMap();    //Récup les données de map
            filetoBlocs();

            //Placer player au coordonnée de son départ (0,0 par défaut)
            Bloc blocDebut = blocs[map.getNbColonne() * map.getDY() + map.getDX()];
            player = Player(map.getDX(),map.getDY(),0,0, blocDebut);
        }

        Bloc getBloc(int n){
            return blocs[n];
        }

        /**
         * @brief Transform the file from map to blocs
         * 
         */
        void filetoBlocs(){
            blocs = new Bloc[nbBlocs];
            int h = 0;
            int w = 0;
            int n = 0;
            for(int i = 0; i < map.getNbLigne(); i++){     //Nb colonne + Colonne
                for(int j = 0; j < map.getNbColonne(); j++){
                    switch(tab[n]) {
                        case '0':
                            blocs[n] = Bloc(50*(w), 50*(h), false);
                            break;
                        case '#':
                            blocs[n] = Bloc(50*(w), 50*(h), true );
                            break;
                    }
                    n++;
                    if (tab[n] == '#' || tab[n] == '0') w++;
                    else n++;
                }
                w = 0;
                h++;
            }
        }

        /**
         * @brief Draw Blocs
         * 
         * @param app
         */
        void drawBlocs(sf::RenderWindow &app){
            for(int i = 0; i < nbBlocs; i++){
                blocs[i].draw(app);
            }
        }


        /**
         * @brief Handle player moves in the game
         * 
         * @param app
         */
        void handleMoves(sf::RenderWindow &app){
            setBlocforPlayer();
            player.handleMoves(app);     
        }

        /**
         * @brief Return true if there's a collision between 2 sprites
         * 
         * @param sprite1
         * @param sprite2
         */
        bool collision(sf::Sprite sprite1, sf::Sprite sprite2) {
            return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
        }

        void setBlocforPlayer(){
            for(int i = 0; i < nbBlocs; i++){
                if(collision(blocs[i].getSprite(), player.getSprite())){
                    // printf("collision\n");
                    player.setBloc(blocs[i]);
                    return;
                }
            }
            printf("pas sur un bloc\n");
            player.replacePlayer();
            player.changeGo(false);
        }
        
        /**
         * @brief Show texture on screen
         * 
         * @param app
         */
        void draw(sf::RenderWindow &app){
            app.clear();
            drawBlocs(app);
            player.draw(app);
            app.display();
        }
};

#endif