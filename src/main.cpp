/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <memory>
#include <chrono>
#include <thread>
#include "UserInput.hpp"
#include "Renderer.hpp"
#include "Game.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	// Allow users to decide their screen dimensions
	Renderer renderer { SCREEN_WIDTH, SCREEN_HEIGHT };

	// Class to manage all input related functionality
	UserInput input;

	// Game manager class
	Game game { input, renderer };

	game.StartGameLoop();

	return 0;
}
