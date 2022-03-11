#include <engine.h>
#include <iostream>

mazeNode::mazeNode(int x, int y) {
    xPos = x;
    yPos = y;
}

void engine::initVariables(int x, int y) {
    srand (time(NULL));
    this->visitedCells = 0;
    this->selection.xPos = 0;
    this->selection.yPos = 0;
    this->mazeWidth = x;
    this->mazeHeight = y;
    this->cellSize = 10;
    this->borderSize = 2;
    this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(borderSize+x*int(cellSize+borderSize),borderSize+y*int(cellSize+borderSize)), "Maze!");
    
    for(int y = 0; y < this->mazeHeight; y++) {
        for(int x = 0; x < this->mazeWidth; x++)
            mazeList.push_back(std::make_shared<mazeNode>(x,y));
        }

    mazeList[0]->visited = true;

};

void engine::drawMaze() {
    sf::RectangleShape rectangle(sf::Vector2f(cellSize, cellSize));
    for(int x = 0; x < this->mazeWidth; x++)
        for(int y = 0; y < this->mazeHeight; y++) {
            rectangle.setFillColor(sf::Color(133,133,133));
            rectangle.setPosition(sf::Vector2f(float(borderSize+x*(cellSize+borderSize)),float(borderSize+y*(cellSize+borderSize))));

            if(mazeList[x + (y * mazeWidth)]->visited == true)
                rectangle.setFillColor(sf::Color::White);

            if(x == this->selection.xPos && y == this->selection.yPos)
                if(this->visitedCells < (this->mazeWidth*this->mazeHeight) - 1) 
                    rectangle.setFillColor(sf::Color::Green);

            this->window->draw(rectangle);
            
            // Draw Neighbors
            if(mazeList[x + (y * mazeWidth)]->visited == true)
                for(auto neighbor : mazeList[x + (y * mazeWidth)]->neighbors) {
                    int lXpos = mazeList[x + (y * mazeWidth)]->xPos;
                    int lYpos = mazeList[x + (y * mazeWidth)]->yPos;
                    // check south
                    sf::RectangleShape path;
                    path.setFillColor(sf::Color::White);
                    if(lYpos < mazeHeight - 1)
                        if(neighbor->yPos == lYpos + 1) {
                            // Draw South
                            path.setSize(sf::Vector2f(cellSize,borderSize));
                            path.setPosition(sf::Vector2f(float(borderSize+x*(cellSize+borderSize)),float(cellSize+borderSize+y*(cellSize+borderSize))));
                            this->window->draw(path);
                        }
                    // check east
                    if(lXpos < mazeWidth - 1)
                        if(neighbor->xPos == lXpos + 1) {
                            // Draw East
                            path.setSize(sf::Vector2f(borderSize,cellSize));
                            path.setPosition(sf::Vector2f(float(cellSize+borderSize+x*(cellSize+borderSize)),float(borderSize+y*(cellSize+borderSize))));
                            this->window->draw(path);
                        }
                }
        }
}

void engine::evaluateMaze() {
    if(this->visitedCells < (this->mazeWidth*this->mazeHeight) - 1) {
        // Step 1: Pick Random Neighbor that is not visited
        // Find available neighbors
        std::vector<std::shared_ptr<mazeNode>> availNeighbors;
        int currentIndex = this->selection.xPos + (this->selection.yPos * mazeWidth);
        // Check North
        if(this->selection.yPos > 0) {
            if(!mazeList[currentIndex - mazeWidth]->visited) {
                availNeighbors.push_back(mazeList[currentIndex - mazeWidth]);
            }
        }
        // Check East
        if(this->selection.xPos < (this->mazeWidth - 1)) {
            if(!mazeList[currentIndex + 1]->visited) {
                availNeighbors.push_back(mazeList[currentIndex + 1]);
            }
        }
        // Check South
        if(this->selection.yPos < (this->mazeHeight - 1)) {
            if(!mazeList[currentIndex + mazeWidth]->visited) {
                availNeighbors.push_back(mazeList[currentIndex + mazeWidth]);
            }
        }
        // Check West
        if(this->selection.xPos > 0) {
            if(!mazeList[currentIndex - 1]->visited) {
                availNeighbors.push_back(mazeList[currentIndex - 1]);
            }
        }
        
        std::cout << availNeighbors.size() << std::endl;

        // Step 2: if no selection pop else push onto stack
        if(availNeighbors.size() == 0) {
            this->selection.xPos = history.back().first;
            this->selection.yPos = history.back().second;
            history.pop_back();
        }
        else {
            // Step 3: Make Neightbor visited, add to current selection node neighbors and next selection neightbors
            // and change selection to new x and y
            std::shared_ptr<mazeNode> selectedNeighbor = availNeighbors[rand() % availNeighbors.size()];
            history.push_back(std::make_pair(this->selection.xPos,this->selection.yPos));
            mazeList[currentIndex]->neighbors.push_back(selectedNeighbor);
            selectedNeighbor->neighbors.push_back(mazeList[currentIndex]);
            this->selection.xPos = selectedNeighbor->xPos;
            this->selection.yPos = selectedNeighbor->yPos;
            selectedNeighbor->visited = true;
            visitedCells++;
        }
    } 
}

engine::engine(int x, int y) {
    this->initVariables(x,y);
}

engine::~engine() {
    //
}

bool engine::isRunning(){
    return this->window->isOpen();
}

void engine::update() {
    //
    this->evaluateMaze();
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

    // Draw Maze
    this->drawMaze(); 

    // Display frame
    this->window->display();
}