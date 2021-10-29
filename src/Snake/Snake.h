#include "modules/Updatable.h"

class Snake : public Updatable {
    public:
        using Updatable::Updatable;

        // In every updatable
        void update(float dt);
        void ready();

        Drawable new_piece;
        std::vector<Drawable> body;
        
        // Class variables
        float size = 50.f;
        std::string direction = "STOP";
        float counter = 0.f;
        float maxCounter = 1.f / 6.f;
};