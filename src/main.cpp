#include <iostream>
#include <engine.h>

int main() {
    engine maze(40, 30); 

    while (maze.isRunning())
    {
        // Event Loop
        maze.processEvent();

        // Update
        maze.update();

        // Render
        maze.renderScreen();
    }
}