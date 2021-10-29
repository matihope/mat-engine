#include "Game.h"
#include "GameObject.h"

// static init
int GameObject::objCounter = 0;

// Contructors / destructors
GameObject::GameObject() {
    this->initVariables();
    std::cout << "Created a new object: " << this->tag << '\n';
}

GameObject::GameObject(Game& game) {
    this->addGameParent(game);
    this->initVariables();
}

GameObject::~GameObject() {

}

void GameObject::addGameParent(Game& game){
    this->game = &game;
}

void GameObject::initVariables() {
    /*
    *   @return void
    * 
    *   sets the default variables of gameobject
    */

    this->setTag("GameObject");
    this->setPosition(sf::Vector2f(0.f, 0.f));
}

void GameObject::setTag(std::string tag, bool add_number) {
    this->tag = tag + (add_number ? std::to_string(GameObject::objCounter++) : "");
}

void GameObject::setPosition(sf::Vector2f position) {
    /*
    *   @return void
    * 
    *   Sets the position of game object.
    */
    this->position = position;
}

void GameObject::ready() {
    /*
        Called just before the first update
    */
}