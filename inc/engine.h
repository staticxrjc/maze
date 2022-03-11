#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <random>

struct mazeNode {
    mazeNode(int,int);
    bool visited = false;
    int xPos, yPos;
    std::vector<std::shared_ptr<mazeNode>> neighbors;
};

struct cursor {
    int xPos, yPos;
};

class engine {
private:
    // SFML Variables
    std::shared_ptr<sf::RenderWindow> window;
    sf::Event event;

    // Maze Variables
    cursor selection;
    std::vector<std::shared_ptr<mazeNode>> mazeList;
    std::vector<std::pair<int,int>> history;
    int mazeWidth;
    int mazeHeight;
    int visitedCells;
    float cellSize;
    float borderSize;

    // Initialization
    void initVariables(int, int);
    
    // Maze Functions
    void drawMaze();
    void evaluateMaze();
public:

    engine(int = 40,int = 30);
    ~engine();
    bool isRunning();
    void update();
    void processEvent();
    void renderScreen();
};
#endif