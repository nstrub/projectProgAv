#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "define.hpp"
#include "game.hpp"

int main() {
    sf::RenderWindow app(sf::VideoMode(WINDOW_X, WINDOW_Y), "Tesoro");
    app.setFramerateLimit(60);

    Game game = Game();

    while (app.isOpen()) {
        game.handleMoves(app);
        game.draw(app);
    }

    return 0;
}