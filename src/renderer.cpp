#include "renderer.hpp"
#include <iostream>

Renderer::Renderer(const int screenWidth, const int screenHeight) : screenWidth_{screenWidth}, screenHeight_{screenHeight}
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		//Create window
		window_ = SDL_CreateWindow(
			"SDL Tutorial", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			screenWidth_, screenHeight_, 
			SDL_WINDOW_SHOWN
		);

		if (window_ == nullptr)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			//Get window surface
			screenSurface_ = SDL_GetWindowSurface(window_);

			//Fill the surface white
			SDL_FillRect(screenSurface_, nullptr, SDL_MapRGB(screenSurface_->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window_);
		}
	}
}

Renderer::~Renderer()
{
	//Destroy window
	SDL_DestroyWindow(window_);

	//Quit SDL subsystems
	SDL_Quit();
}
