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

			loadMedia();
		}
	}
}

Renderer::~Renderer()
{
	//Deallocate surface
	SDL_FreeSurface(helloWorld_);
	helloWorld_ = nullptr;

	//Destroy window
	SDL_DestroyWindow(window_);
	window_ = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}

void Renderer::loadMedia()
{
	//Load splash image
	helloWorld_ = SDL_LoadBMP("../hello_world.bmp");

	// "C:\...\Lazy-Foo-SDL\build"
	//std::filesystem::path currentPath = std::filesystem::current_path();
	//std::cout << "Current working directory: " << currentPath << std::endl;

	if (helloWorld_ == nullptr)
	{
		std::cout << "Unable to load image hello_world.bmp due to SDL Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		//Apply the image
		SDL_BlitSurface(helloWorld_, nullptr, screenSurface_, nullptr);

		//Update the surface
		SDL_UpdateWindowSurface(window_);
	}
}

void Renderer::KeepWindowUp()
{
	//Hack to get window to stay up
	SDL_Event e; 
	bool quit = false;

	while (quit == false) 
	{ 
		while (SDL_PollEvent(&e)) 
		{ 
			if (e.type == SDL_QUIT) quit = true; 
		} 
	}
}
