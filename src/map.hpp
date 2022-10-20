#ifndef MAP_HPP
#define MAP_HPP

#include <string.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "bloc.hpp"

/**
 * @brief Class that create and store a map
 * 
 */
class Map{
    private:
        int nbLigne;
        int nbColonne;
        char* nom;
        char** map;
        Bloc** tab;

    public:
        Map(){
            nbLigne = 5;
            nbColonne = 5;
            map = (char**) malloc(nbLigne * nbColonne * sizeof(char));
            //Ici je voulais commencer la structure pour les réactions bloc/joueur mais segmentation fault...
            // tab = (Bloc**) malloc(nbLigne * nbColonne * sizeof(Bloc));
            // int x = 100;
            // int y = 100;
            // for(int i = 0; i < nbLigne; i++){
            //     for(int j = 0; j < nbColonne; j++){
            //         tab[i][j] = Bloc(x,y);
            //         x += 50;
            //     }
            //     x = 100;
            //     y += 50;
            // }
        }
        /**
         * @brief Construct new map Object
         * 
         */
        Map(char* nom){
            nom = nom;
            setNbLigne();
            setNbColonne();
            map = (char**) malloc(nbLigne * nbColonne * sizeof(char));
            lireFichier();
        }

        void setNbLigne(){
            std::ifstream fichier(nom);
            nbLigne = 0;
            if (fichier) {
                printf("Found");
                fichier.seekg(0, std::ios::end);
                nbLigne = fichier.tellg();
            }
            if (nbLigne > 15 || nbLigne == 0) {
                printf("Taille de la map (lignes) trop grande ou inexistante : %d > 15 ou %d = 0\n", nbLigne, nbLigne);
                exit(0);
            }
        }

        void setNbColonne(){
            std::ifstream fichier(nom);
            nbColonne = 0;
            if (fichier) {
                char* ligne;
                fichier.getline(ligne,16,'\n');
                printf("%s",ligne);
                nbColonne = strlen(ligne);
            }
            if (nbColonne > 15 || nbColonne == 0) {
                printf("Taille de la map (colonnes) trop grande ou inexistante : > 15 ou = 0\n");
                exit(0);
            }
        }

        int* getD(){
            int* coos = (int*) malloc(sizeof (int) * 2);
            coos[0] = 0;
            coos[1] = 0;

            for (int i = 0; i < nbLigne; i++) {
                for (int j = 0; j < nbColonne; j++)
                    if (map[i][j] == 'D'){
                        coos[0] = i;
                        coos[1] = j;
                        return coos;
                    }
            }

            return coos;
        }

        /**
         * @brief Allow to generate the map from a text file
         * 
         */
        void lireFichier(){
            char c;
            std::ifstream fichier(nom);
            if (fichier) {
                fichier.seekg(0, std::ios::beg);
                for (int i = 0; i < nbLigne; i++) {
                    for (int j = 0; j < nbColonne; j++) {
                        char c = fichier.peek();
                        switch(c) {
                            case ' ':
                                map[i][j] = '0';
                                break;
                            default:
                                map[i][j] = c;
                        }
                    }
                }
            }
        }

        /**
         * @brief Show texture of the labyrinth on screen
         * 
         * @param app 
         */
        void draw(sf::RenderWindow &app) {
            int x = 100;
            int y = 100;
            for(int i = 0; i < nbColonne; i++){
                for(int j = 0; j < nbLigne; j++){
                    //Ajouter un if si le bloc est spécial ou non
                    sf::RectangleShape carre(sf::Vector2f(50,50));
                    carre.setPosition(x,y);
                    carre.setFillColor(sf::Color::Yellow);
                    carre.setOutlineColor(sf::Color::Black);
                    carre.setOutlineThickness(2);
                    app.draw(carre);
                    x += 50;
                }
                x = 100;
                y += 50;            
            }
        }
};

#endif