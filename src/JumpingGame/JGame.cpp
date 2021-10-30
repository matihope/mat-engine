#include "../../modules/Game.h"
#include "JGame.h"

void JGame::update() {
    Game::update();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        this->validateScreen(1);
        this->current_screen = 1;
    }
    //
}
