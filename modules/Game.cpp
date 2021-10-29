#include "Game.h"

sf::Vector2f scaleToFit(sf::Vector2f viewport_size, sf::Vector2u window_size) {
    /*
        @return FloatRect to apply, in order to keep ratio and fit in the window
    */
   sf::Vector2f scale;
   scale.x = viewport_size.x / window_size.x;
   scale.y = viewport_size.y / window_size.y;
   if(scale.x < scale.y){
       scale.x *= 1 / scale.y;
       scale.y = 1;
   }
   else{
        scale.y *= 1 / scale.x;
        scale.x = 1;
   }
    return scale;
}

// Constructor / Destructors
Game::Game(int window_width, int window_height, std::string title) {
    this->initVariables();
    this->initWindow(window_width, window_height, title);
}

Game::~Game() {
    delete this->window;
}

// Private Functions
void Game::initVariables() {
    this->window = nullptr;
    this->bgColor = sf::Color(80, 80, 80);
    this->printCurrentFPS = false;
    this->setPhysicsUpdateCallFreq();
    this->viewport_mode = VIEWPORT_MODE::KEEP_AS_IS;
}

void Game::initWindow(int window_width, int window_height, std::string title) {
    this->videoMode.width = window_width;
    this->videoMode.height = window_height;
    this->window = new sf::RenderWindow(this->videoMode, title, sf::Style::Titlebar | sf::Style::Close);
    this->setViewportSize(sf::Vector2f(window_width, window_height));
    this->window->setView(this->view);
}

void Game::setBgColor(sf::Color bg) {
    this->bgColor = bg;
}


// Accessors
const bool Game::running() const {
    /* 
        @return bool

        Return window open state.
    */
    return this->window->isOpen();
}

const sf::Vector2u Game::getWindowSize() const {
    /* 
        @return sf::Vector2u

        Return window's size.
    */
    return this->window->getSize();
}

const sf::Vector2f Game::getViewportSize() const {
    /* 
        @return sf::Vector2u

        Return window's size.
    */
    return this->viewport_size;
}

const sf::Vector2f Game::getMouseViewPos() const {
    /* 
        @return Vector2f

        Return current mouse position by view.
    */
    return this->mousePosView;
}

const bool Game::getVsync() const {
    /* 
        @return bool

        Return vsync boolean.
        true if on
    */
    return this->vsync;
}

const uint Game::getFPS() const {
    /* 
        @return int

        Return vsync boolean.
        true if on
    */
    return this->FPS;
}

const float Game::getPhysicsUpdateCallFreq() const {
    return 1.f / this->physicsUpdateCallFreq;
}

// Public Functions
void Game::pollEvents(){
    /* 
        @return void

        Handle all the events.
    */
    while(this->window->pollEvent(this->event)) {
        switch (this->event.type) {

            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;

        }
    }
}

void Game::updateMousePositions() {
    /* 
        @return void
        
        Updates the mouse positions:
            * Mouse position relative to the window (Vector2i)
    */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update() {
    /* 
        @return void

        - poll the events
        - update game objects

        Update the game state.
    */

    // Poll the events
    this->pollEvents();

    // Update delta time
    this->dt = this->clock.restart().asSeconds();

    // Update mouse positions
    this->updateMousePositions();

    this->printFPS(dt);

    // Update every updatable object
    for (auto updt : this->updatables) {
        updt->update(dt);
    }

    // Update every updatable object's physics
    if (this->physicsUpdateCounter >= this->physicsUpdateCallFreq) {
        this->physicsUpdateCounter -= this->physicsUpdateCallFreq;
        for (auto updt : this->updatables) {
            updt->updatePhysics(this->physicsUpdateCallFreq);
        }
    }
    this->physicsUpdateCounter += dt;
}

void Game::render() {
    /* 
        @return void

        - clear old frame
        - render objects
        - display frame in window

        Renders the game objects.
    */
    this->window->clear(this->bgColor);

    // Draw game objects
    for (Drawable* obj : this->drawables) {
        this->window->draw(*obj);
    }

    this->window->display();
}

void Game::addGameObject(GameObject& obj) {
    /*
        Adding an object to the game and adding self reference in the object
    */
    this->gameObjects.push_back(&obj);
    obj.addGameParent(*this);
    obj.ready();
}

void Game::addDrawable(Drawable& drawable) {
    /*
        Adding a drawable and passing drawble to addGameObject
    */
    this->addGameObject(drawable);
    this->drawables.push_back(&drawable);
}

void Game::addUpdatable(Updatable& updatable) {
    /*
        Adding a updatable and passing updatable to addDrawable
    */
    this->addDrawable(updatable);
    this->updatables.push_back(&updatable);
}

void Game::setViewportMode(VIEWPORT_MODE mode) {
    viewport_mode = mode;
    setViewportSize(this->viewport_size);
}

void Game::setViewportSize(sf::Vector2f size) {
    sf::Vector2f viewport_scale(1.f, 1.f);
    switch(this->viewport_mode) {
        case VIEWPORT_MODE::FILL:
            // default behaviour
            break;
        case VIEWPORT_MODE::KEEP_AS_IS:
            viewport_scale.x = size.x / this->videoMode.width;
            viewport_scale.y = size.y / this->videoMode.height;
            break;
        case VIEWPORT_MODE::MAINTAIN_RATIO:
            viewport_scale = scaleToFit(size, this->getWindowSize());
            break;
    }
    // printf("Window size: %d, %d\n", this->videoMode.width, this->videoMode.height);
    // printf("Viewport size: %f, %f\n", size.x, size.y);
    // printf("Viewport scale: %f, %f\n", viewport_scale.x, viewport_scale.y);
    this->viewport_size = size;
    this->view.reset(sf::FloatRect(sf::Vector2f(0, 0), size));
    this->view.setViewport(sf::FloatRect(sf::Vector2f(0, 0), viewport_scale));
    this->window->setView(this->view);
}

void Game::setVsync(bool on) {
    /*
        Set window's VerticalSync option
    */
    this->vsync = on;
    this->window->setVerticalSyncEnabled(on);
}

void Game::setFPS(uint fpsCount) {
    /*
        Set window's frame limit
    */
    this->FPS = fpsCount;
    this->window->setFramerateLimit(fpsCount);
}

void Game::setPrintCurrentFPS(bool on) {
    this->printCurrentFPS = on;
}

const void Game::printFPS(float &dt) const {
    if (this->printCurrentFPS)
        printf("%f\n", 1.f/dt);
}

void Game::setPhysicsUpdateCallFreq(float newFreq) {
    this->physicsUpdateCallFreq = 1.f / newFreq;
    std::cout << physicsUpdateCallFreq << std::endl;
}
