/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <memory>
#include "renderer.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	// Allow users to decide their screen dimensions
	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(SCREEN_WIDTH, SCREEN_HEIGHT);

	renderer->GameLoop();

	return 0;
}
