#include "../../modules/Updatable.h"

class Player : public Updatable {
    public:
        using Updatable::Updatable;
        
        void updatePhysics(float dt);
        void ready();

        sf::Vector2u textureSize;
        float size = 25.f;
        sf::Vector2f velocity;
};