#include "../../modules/Game.h"
#include <vector>

class JGame : public Game {
    public:
        using Game::Game;

        std::vector<GameObject*> blocks;

        void update();

};  
