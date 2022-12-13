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
        int xD, yD, xF, yF;
        string nom;
        char* map;

    public:
        Map(){
            nbLigne = 5;
            nbColonne = 5;
            map = (char*) malloc(nbLigne * nbColonne * sizeof(char));
        }

        /**
         * @brief Construct new map Object
         * 
         */
        Map(char* nomMap){
            nom = nomMap;
            setNbLigneEtColonne();
            map = (char*) malloc(nbLigne * nbColonne * sizeof(char));
            lireFichier();
        }

        void setNbLigneEtColonne(){
            ifstream fichier(nom);
            nbLigne = 1;
            nbColonne = 0;
            if (fichier) {
                printf("Fichier trouvé.\n");
                fichier.seekg(0, std::ios::end);
                int nbCarac = fichier.tellg();
                char c;

                // Nombre de lignes
                for (int i = 0; i < nbCarac; i++){
                    fichier.seekg(i,std::ios::beg);
                    fichier.get(c);
                    if (c == 10) nbLigne++;
                }

                // Nombre de colonnes
                for (int i = 0; i < nbCarac; i++){
                    fichier.seekg(i,std::ios::beg);
                    fichier.get(c);
                    if (c == 10 || c == '\n') break;
                    else nbColonne++;
                }

                fichier.close();
            }
            else
            {
                printf("File not found\n");
                fichier.close();
                exit(0);
            }

            if (nbLigne > 15 || nbLigne == 0) {
                printf("Taille de la map (lignes) trop grande ou inexistante\n");
                exit(0);
            }

            if (nbColonne > 15 || nbColonne == 0) {
                printf("Taille de la map (colonnes) trop grande ou inexistante\n");
                exit(0);
            }

            printf("Format de fichier correct.\n");
        }

        int getDX(){
            return xD * 50;
        }

        int getDY(){
            return yD * 50;
        }

        int size() {
            return nbLigne * nbColonne;
        }

        char* getMap() {
            return map;
        }

        int getNbLigne() {
            return nbLigne;
        }

        int getNbColonne() {
            return nbColonne;
        }

        /**
         * @brief Allow to generate the map from a text file
         * 
         */
        void lireFichier(){
            char c;
            int index = 0;
            ifstream fichier(nom);

            if (fichier) {
                // allocate memory:
                char * buffer = new char [nbLigne * nbColonne + nbLigne - 1];

                // read data as a block:
                fichier.read (buffer,nbLigne * nbColonne + nbLigne - 1);

                // Indice pour la construction du nouveau tableau
                int caseActuelle = 0;

                for (int i = 0; i < nbLigne * nbColonne + nbLigne - 1; i++) {
                    printf("%c",buffer[i]);
                    // Caractères par défaut
                    map[caseActuelle] = buffer[i];

                    switch(buffer[i]) {
                        // Caractères incorrects ou spéciaux
                        case ' ':
                            map[caseActuelle] = '0';
                            break;
                        case 'D':
                            yD = caseActuelle / nbColonne;
                            xD = caseActuelle % nbColonne;
                            break;
                        case 'd':
                            map[caseActuelle] = 'D';
                            yD = caseActuelle / nbColonne;
                            xD = caseActuelle % nbColonne;
                            break;
                        case 'F':
                            yF = caseActuelle / nbColonne;
                            xF = caseActuelle % nbColonne;
                            break;
                        case 'f':
                            map[caseActuelle] = 'F';
                            yF = caseActuelle / nbColonne;
                            xF = caseActuelle % nbColonne;
                            break;
                    }

                    // Si le caratère que l'on a regardé est autre chose qu'un \n, on passe au caractère suivant.
                    // Cela permet de ne pas mettre de \n dans le tableau et surtout de ne pas perdre l'indice sur lequel
                    // on doit ajouter dans le tableau construit.
                    if (buffer[i] != '\n') caseActuelle++;
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
