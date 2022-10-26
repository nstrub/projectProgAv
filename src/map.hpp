#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace std;

#include "bloc.hpp"

/**
 * @brief Class that create and store a map
 * 
 */
class Map{
    private:
        int nbLigne;
        int nbColonne;
        string nom;
        char** map;
        Bloc** tab;

    public:
        Map(){
            nbLigne = 5;
            nbColonne = 5;
            map = (char**) malloc(nbLigne * nbColonne * sizeof(char));
        }

        /**
         * @brief Construct new map Object
         * 
         */
        Map(char* nomMap){
            nom = nomMap;
            setNbLigneEtColonne();
            printf("1");
            map = (char**) malloc(nbLigne * nbColonne * sizeof(char));
            printf("Après");
            lireFichier();
        }

        void setNbLigneEtColonne(){
            ifstream fichier(nom);
            nbLigne = 0;
            nbColonne = 0;
            if (fichier) {
                printf("Found\n");
                nbLigne = 1;
                fichier.seekg(0, std::ios::end);
                int nbCarac = fichier.tellg();
                char c;

                // Nombre de lignes
                for (int i = 0; i < nbCarac; i++){
                    fichier.seekg(i,std::ios::beg);
                    fichier.get(c);
                    if (c == 10) nbLigne++;
                }
                printf("%d\n", nbLigne);

                // Nombre de colonnes
                for (int i = 0; i < nbCarac; i++){
                    fichier.seekg(i,std::ios::beg);
                    fichier.get(c);
                    if (c == 10) break;
                    else nbColonne++;
                }
                printf("%d\n", nbColonne);

                fichier.close();
            }
            else
            {
                printf("File not found\n");
                fichier.close();
                exit(0);
            }

            printf("Après");

            if (nbLigne > 15 || nbLigne == 0) {
                printf("Taille de la map (lignes) trop grande ou inexistante");
                exit(0);
            }

            if (nbColonne > 15 || nbColonne == 0) {
                printf("Taille de la map (colonnes) trop grande ou inexistante");
                exit(0);
            }
        }

        int* getD(){
            int* coos = (int*) malloc(sizeof (int) * 2);
            coos[0] = 0;
            coos[1] = 0;

            for (int i = 0; i < nbLigne; i++)
                for (int j = 0; j < nbColonne; j++)
                    if (map[i][j] == 'D'){
                        coos[0] = i;
                        coos[1] = j;
                        return coos;
                    }

            return coos;
        }

        /**
         * @brief Allow to generate the map from a text file
         * 
         */
        void lireFichier(){
            char c;
            ifstream fichier(nom);
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
