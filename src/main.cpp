#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.hpp"
#include "game.hpp"
#include "menu.hpp"

int main() {
    sf::RenderWindow app(sf::VideoMode(WINDOW_X, WINDOW_Y), "Tesoro");
    app.setFramerateLimit(60);

    Game game = Game(5);
    Menu menu = Menu();

    while (app.isOpen()) {
        while(menu.getMenuUpdate() == 1){
            menu.handleMoves(app);
            menu.draw(app);
        }
        game.handleMoves(app);
        game.draw(app);
    }

    return 0;
}