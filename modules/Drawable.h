#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "GameObject.h"

class Drawable : public GameObject, public sf::Drawable { 
    public:
        // Constructors / Destructors
        Drawable();
        Drawable(std::string filename);
        Drawable(sf::Vector2f position);
        ~Drawable();

        // Variables
        sf::Sprite sprite;

        // Functions
        virtual bool setTextureFromFile(std::string filename);
        virtual void setTexture(sf::Texture& texture);
        virtual void setPosition(sf::Vector2f position);
        virtual void move(sf::Vector2f offset);

    protected:
        //Variables
        sf::Texture* texture;

        // Functions
        void draw(sf::RenderTarget &target, sf::RenderStates state) const;
        virtual void initVariables();
};

#endif // DRAWABLE_H