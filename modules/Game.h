#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "GameObject.h"
#include "Drawable.h"
#include "Updatable.h"

enum VIEWPORT_MODE {
    FILL,
    KEEP_AS_IS,
    MAINTAIN_RATIO,
};

/*
    Class that acts as the game enine.
    Wrapper class.
*/

class Game {
    public:
        Game(int window_width = 800, int window_height = 600, std::string title = "Game 1");
        ~Game();

        // Accessors
        const bool running() const;
        const sf::Color getBgColor() const;
        const sf::Vector2u getWindowSize() const;
        const sf::Vector2f getViewportSize() const;
        const sf::Vector2f getMouseViewPos() const;
        const bool getVsync() const;
        const uint getFPS() const;
        const float getPhysicsUpdateCallFreq() const;

        // Variables
        int current_screen;
        int initialized_screens;

        // Functions
        void pollEvents();
        void updateMousePositions();
        void update();
        void render();

        void setBgColor(sf::Color = sf::Color(80, 80, 80));
        void setVsync(bool on = true);
        void setViewportSize(sf::Vector2f size);
        void setViewportMode(VIEWPORT_MODE mode);
        void setFPS(uint fpsCount);
        void setPrintCurrentFPS(bool on = true);
        void setPhysicsUpdateCallFreq(float newFreq = 60.f);
        void addGameObject(GameObject& obj, int screen = 0);
        void addDrawable(Drawable& drawable, int screen = 0);
        void addUpdatable(Updatable& updatable, int screen = 0);
        void validateScreen(int screen);

    private:
        // Variables
        // Window
        sf::RenderWindow* window;
        sf::View view;
        sf::Vector2f viewport_size;
        VIEWPORT_MODE viewport_mode;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::Color bgColor;
        bool vsync;
        uint FPS;
        bool printCurrentFPS;

        // Mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        // Game objects
        // vectors of vectors to create screens
        std::vector<std::vector<GameObject *>> gameObjects;
        std::vector<std::vector<Drawable *>> drawables;
        std::vector<std::vector<Updatable *>> updatables;

        // Update related
        sf::Clock clock;
        float dt;
        float physicsUpdateCallFreq;
        float physicsUpdateCounter = 0;
        
        // Private functions
        void initVariables();
        void initWindow(int window_width, int window_height, std::string title);
        const void printFPS(float &dt) const;

};

#endif // GAME_H