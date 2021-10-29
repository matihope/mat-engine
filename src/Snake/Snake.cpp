#include "modules/Game.h"
#include "Snake.h"
#include <cstring>

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

void Snake::ready() {
    sf::Image img1, img2;
    sf::Texture bodyTexture;
    img1.create(this->size, this->size, sf::Color(81, 149, 207));
    img2.create(this->size, this->size, sf::Color(41, 97, 145));
    this->texture.loadFromImage(img1);
    this->setTexture(texture);

    bodyTexture.loadFromImage(img2);
    this->new_piece.setTexture(bodyTexture);
    this->body.push_back(this->new_piece);
    this->body.push_back(this->new_piece);
}

void Snake::update(float dt){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->direction = "RIGHT";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->direction = "LEFT";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->direction = "UP";
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->direction = "DOWN";

    this->counter += dt;
    if (this->counter >= this->maxCounter) {

        if(this->body.size() > 0){
            auto it = this->body.begin(); // points to the first element
            it->setPosition(this->position);
            std::rotate(it, it + 1, this->body.end()); // move the piece in the memory to the end
        }

        this->counter -= this->maxCounter;
        if (this->direction == "RIGHT")
            this->move(sf::Vector2f(this->size, 0.f));
        if (this->direction == "LEFT")
            this->move(sf::Vector2f(-this->size, 0.f));
        if (this->direction == "UP")
            this->move(sf::Vector2f(0.f, -this->size));
        if (this->direction == "DOWN")
            this->move(sf::Vector2f(0.f, this->size));

        this->setPosition(sf::Vector2f(mod(this->position.x, this->game->getWindowSize().x), mod(this->position.y, this->game->getWindowSize().x)));
    }
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (Drawable const& piece : this->body){
        target.draw(piece, states);
    }
    Updatable::draw(target, states);
}