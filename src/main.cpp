#include <iostream>
#include <engine.h>

int main() {
    engine maze(500, 500); 

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