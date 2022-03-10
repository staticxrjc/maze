#include <engine.h>

void engine::initVariables() {
    //
};

void engine::initWindow(int x, int y){
    //
}

engine::engine(int x, int y) {
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(x,y), "Hello SFML!");
}

engine::~engine() {
    //
}

bool engine::isRunning(){
    return this->window->isOpen();
}

void engine::update() {
    //
}

void engine::processEvent() {
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void engine::renderScreen() {
    // clear window
    this->window->clear(sf::Color::Black);

    sf::CircleShape shape(50.f);

    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));

    this->window->draw(shape);
    
    // Display frame
    this->window->display();
}