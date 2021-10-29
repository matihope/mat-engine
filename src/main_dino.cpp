#include "../modules/Game.h"
// #include "Snake.h"
#include "DinoGame/Player.h" 


int main() {
    // Init game engine
    Game game(900, 500);
    game.setVsync();
    game.setPrintCurrentFPS();
    game.setBgColor(sf::Color(32, 32, 32));

    // Snake snake("isia.png");
    // game.addUpdatable(snake);

    Player player;
    game.addUpdatable(player);

    // Game loop
    while(game.running()) {
        // Update
        game.update();

        // Render
        game.render();
    }
}
