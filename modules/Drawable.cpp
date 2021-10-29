#include "Drawable.h"

// Constructors / destructors
Drawable::Drawable() : GameObject::GameObject(), sf::Drawable::Drawable() {
}

Drawable::Drawable(std::string filename) : Drawable::Drawable() {
    this->setTextureFromFile(filename);
}

Drawable::Drawable(sf::Vector2f position) {
    this->setPosition(position);
}

Drawable::~Drawable() {
    delete this->texture;
}

void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}

bool Drawable::setTextureFromFile(std::string filename) {
    bool success = this->texture->loadFromFile(filename);
    this->setTexture(*this->texture);

    return success;
}

void Drawable::setTexture(sf::Texture &texture) {
    this->texture = &texture;
    this->sprite.setTexture(*this->texture, true);
}

void Drawable::setPosition(sf::Vector2f position) {
    GameObject::setPosition(position);
    this->sprite.setPosition(position);
}

void Drawable::move(sf::Vector2f offset) {
    this->setPosition(this->position + offset);
}

void Drawable::initVariables() {
    GameObject::initVariables();
    this->sprite.setTexture(*this->texture);
}
