#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Game;

class GameObject {
    static int objCounter;

    public:
        // Constructors / Destructors
        GameObject();
        GameObject(Game& game);
        ~GameObject();

        // Variables
        std::string tag;
        sf::Vector2f position;

        //Functions 
        void addGameParent(Game& game);
        virtual void setPosition(sf::Vector2f position);
        virtual void setTag(std::string tag, bool add_number = true);
        virtual void ready();

    protected:
        // Private functions
        virtual void initVariables();

        // Private variables
        Game* game;

};

#endif // GAME_OBJECT_H