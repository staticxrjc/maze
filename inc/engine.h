#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics.hpp>
#include <memory>

class engine {
private:
    // SFML Variables
    std::shared_ptr<sf::RenderWindow> window;
    sf::Event event;

    // Initialization
    void initVariables();
    void initWindow(int, int);
    
public:
    engine(int = 200,int = 200);
    ~engine();
    bool isRunning();
    void update();
    void processEvent();
    void renderScreen();
};
#endif