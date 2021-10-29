#include "../../modules/Updatable.h"

class Player : public Updatable {
    public:
        using Updatable::Updatable;

        // In every updatable
        void updatePhysics(float dt);
        void ready();

        // Variables
        sf::Vector2u textureSize;
        int animation_index;
        float curr_frame_time = 0.f;
        float max_frame_time = 0.1f;
        sf::Vector2f velocity;
        float speed = 7.5f;
        float grv = 0.4f;
        float jump_val = -10.f;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates state) const;
};