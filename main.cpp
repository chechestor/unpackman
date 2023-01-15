/**
 * Main file for game. Consists Game class and main loop for gameflow.
 * All gaming actions performs in Game class.
 * Update() methods used to calculate new states of game objects in each frame.
 * Render() methods used to draw game state on screen.
 * 
*/
#include <iostream>
#include "Game.hpp"

int main()
{
    Game * game = new Game();
    while (game->running())
    {
        game->update();  // calc new state of game objects
        game->render();  // draw new frame state in window
    }
    return 0;
}