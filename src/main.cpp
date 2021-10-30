#include "JumpingGame/JGame.h"
#include "JumpingGame/Player.h"

// Init game engine
JGame game(1000, 1000);
Player p;

void init(){
    game.setVsync();
    game.setBgColor(sf::Color(33, 33, 33));
    game.setViewportMode(VIEWPORT_MODE::MAINTAIN_RATIO);
    game.setViewportSize(sf::Vector2f(800, 600));
}

void addObjects(){
    game.addUpdatable(p);
}

int main() {
    init();
    addObjects();

    while(game.running()) {
        game.update();
        game.render();
    }
}
