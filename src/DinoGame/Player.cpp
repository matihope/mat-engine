#include "../../modules/Game.h"
#include "Player.h"

int sign(int x){
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void Player::ready() {
    animation_index = 0;
    if (!setTextureFromFile("src/DinoGame/DinoSprites/sheets/player.png")) {
        printf("Error loading player image\n");
    }

    textureSize = texture.getSize();
    textureSize.x /= 24;
    sprite.setTextureRect(sf::IntRect(textureSize.x, 0, textureSize.x, textureSize.y));
    sprite.setScale(3.f, 3.f);
}


void Player::updatePhysics(float dt) {
    sprite.setTextureRect(sf::IntRect(textureSize.x * animation_index, 0, textureSize.x, textureSize.y));
    curr_frame_time += dt;
    if (curr_frame_time >= max_frame_time) {
        curr_frame_time -= max_frame_time;
        animation_index ++;
        animation_index %= 4;
    }

    if (sf::Joystick::isConnected(0))
        velocity.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100.f;
    else
        velocity.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    velocity.x *= speed;
    velocity.y += grv;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (position.y + (texture.getSize().y * 3.f) >= game->getWindowSize().y)){
        velocity.y = jump_val;
    }

    if (position.y + velocity.y + (texture.getSize().y * 3.f) > game->getWindowSize().y) {
        velocity.y -= position.y + velocity.y + (texture.getSize().y * 3.f) - game->getWindowSize().y;
    }

    
    move(velocity);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Updatable::draw(target, states);
}
