#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "player.hpp"
#include "map.hpp"
#include "choixNiveaux.hpp"

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
        bool hasMove;
        int choixLvl;
        int isContrsuct = 0;

    public:
        /**
         * @brief Construct an empty Game Object
         * 
         */
        Game(){

        }

        /**
         * @brief Construct a new Game Object
         * 
         * @param size 
         * @param numNiveau 
         */
        Game(int size, int numNiveau){
            choixLvl = numNiveau;
            switch (choixLvl)
            {
            case 1:
                map = Map("ressources/niveau1.map");
                isContrsuct = 1;
                break;
            case 2:
                map = Map("ressources/niveau2.map");
                isContrsuct = 1;
                break;
            case 3:
                map = Map("ressources/niveau3.map");
                isContrsuct = 1;
                break;                
            }
            sizeTab = nbBlocs = map.size();
            tab = map.getMap();    //Récup les données de map
            filetoBlocs();

            //Placer player au coordonnée de son départ (0,0 par défaut)
            //printf("x:%i y:%i", map.getDX(), map.getDY());
            Bloc blocDebut = blocs[map.getNbColonne() * (map.getDX()/50) + (map.getDY()/50)];
            player = Player(map.getDX(),map.getDY(),map.getDX()/50,map.getDY()/50, blocDebut);
            hasMove = true;
        }

        /**
         * @brief Get the Is Contruct number (1 if Game(int size, int numNiveau) is called )
         * 
         * @return int 
         */
        int getIsContruct(){return isContrsuct;}

        /**
         * @brief Return a certain bloc from blocs[]
         * 
         * @param n 
         * @return Bloc 
         */
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
            // printf("%i %i", map.getDX(), map.getDY());
            for(int i = 0; i < map.getNbLigne(); i++){   //Nb colonne + Colonne
                for(int j = 0; j < map.getNbColonne(); j++){
                    blocs[n] = Bloc(50*(w), 50*(h), tab[n]);
                    w++;
                    n++;
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


        /**
         * @brief Send the bloc that is in colision with the player and reacts in fonction of it
         * 
         */
        void setBlocforPlayer(){
            for(int i = 0; i < nbBlocs; i++){
                // if (i == player.getposTabY()*map.getNbColonne()+player.getposTabX()) printf("sur la case : %i", i);
                // else printf("%i ", player.getposTabY()*map.getNbColonne()+player.getposTabX());
                if(collision(blocs[i].getSprite(), player.getSprite()) && !blocs[i].getIsWall() && !blocs[i].getIsClosed()){
                    // printf("collision\n");
                    if(blocs[i].getIsWall()){
                        player.changeGo(false);
                    }
                    player.setBloc(blocs[i]);
                    if (blocs[i].getIsButton() && hasMove) {
                        for(int j = 0; j < nbBlocs; j++){
                            if (blocs[j].getChar() == '=') {
                                if (blocs[j].getIsClosed()) {
                                    blocs[j].changeTexture('0');
                                    blocs[j].changeClosed();
                                    //printf("porte trouvée");
                                }
                                // else {
                                //     blocs[j].changeTexture('#');
                                //     blocs[j].changeClosed();
                                // }
                            }
                        }
                        //printf("hasMove = false\n");
                        hasMove = false;
                    }

                    if (blocs[player.getposTabY()*map.getNbColonne()+player.getposTabX()].getChar() != '@') {
                        hasMove = true;
                        //printf("hasMove = true\n");
                    }

                    if (blocs[i].getIsExit()) {
                        //printf("Bravo !\n");
                        exit(0);
                    }
                    return;
                }
            }
            //printf("pas sur un bloc\n");
            player.changeGo(false);
            player.replacePlayer();
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