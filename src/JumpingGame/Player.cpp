#include "../../modules/Game.h"
#include "Player.h"

void Player::ready() {
    sf::Image img1;
    sf::Texture* t = new sf::Texture;
    img1.create(this->size, this->size, sf::Color(20, 167, 12));
    t->loadFromImage(img1); // to avoid texture being removed from memory
    this->setTexture(*t);
}

void Player::updatePhysics(float dt) {
    velocity.y += 0.4;
    velocity.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    velocity.x *= 3;


    if(position.y + size + velocity.y > game->getViewportSize().y) {
        position.y = game->getViewportSize().y - size;
        velocity.y = 0;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        velocity.y = -5;
    }

    move(velocity);
}

// void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//     Updatable::draw(target, states);
// }
