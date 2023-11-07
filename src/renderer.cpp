#include <chrono>
#include <thread>

#include "renderer.hpp"
#include "error.hpp"

// TODO: Create Input class

Renderer::Renderer(const int screenWidth, const int screenHeight) : screenWidth_{screenWidth}, screenHeight_{screenHeight}
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ThrowSDLError("SDL video could not initialize.");
	}

	window_ = SDL_CreateWindow(
		"SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth_, screenHeight_,
		SDL_WINDOW_SHOWN
	);

	if (window_ == nullptr)
	{
		ThrowSDLError("Window could not be created.");
	}
	
	screenSurface_ = SDL_GetWindowSurface(window_);

	LoadMedia();
}

Renderer::~Renderer()
{
	//Deallocate surfaces
	for (size_t i = 0; i < static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL); ++i)
	{
		SDL_FreeSurface(keyPressSurfaces_[i]);
		keyPressSurfaces_[i] = nullptr;
	}
	currentSurface_ = nullptr;

	//Destroy window
	SDL_DestroyWindow(window_);
	window_ = nullptr;
	screenSurface_ = nullptr; // destroying the window frees its surface

	//Quit SDL subsystems
	SDL_Quit();
}

void Renderer::LoadMedia()
{
	//Allocate surfaces
	keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT)] = LoadSurface("press.bmp");
	keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_UP)] = LoadSurface("up.bmp");
	keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN)] = LoadSurface("down.bmp");
	keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT)] = LoadSurface("left.bmp");
	keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT)] = LoadSurface("right.bmp");
}

SDL_Surface* Renderer::LoadSurface(const std::string imageFile)
{
	std::string imagePath = "../" + imageFile;

	SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());

	if (surface == nullptr)
	{
		ThrowSDLError("Unable to load image: " + imagePath);
	}

	return surface;
}

//Hack to get window to stay up
void Renderer::GameLoop()
{
	// An SDL event is something like a key press, mouse motion, joy button press, etc.
	SDL_Event e; 
	bool quit = false;

	// Game loop
	while (!quit) 
	{
		// Otherwise, CPU utilization goes from ~0% -> ~20%
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		// Handle events on queue: When you press a key, move the mouse, or touch a touch screen you put events onto the event queue.
		// SDL_PollEvent takes the most recent event from the queue and puts the data from the event into the SDL_Event we passed into the function.
		while (SDL_PollEvent(&e)) 
		{ 
			if (e.type == SDL_QUIT) 
			{ 
				quit = true; 
			}

			SDL_Scancode code = e.key.keysym.scancode;

			switch (code)
			{
			case SDL_SCANCODE_LEFT:
				currentSurface_ = keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT)];
				break;
			case SDL_SCANCODE_RIGHT:
				currentSurface_ = keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT)];
				break;
			case SDL_SCANCODE_UP:
				currentSurface_ = keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_UP)];
				break;
			case SDL_SCANCODE_DOWN:
				currentSurface_ = keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN)];
				break;
			default:
				currentSurface_ = keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT)];
				break;
			}
		} 

		//Apply the image by drawing to the back buffer first
		SDL_BlitSurface(currentSurface_, nullptr, screenSurface_, nullptr);

		//Swap the back and front buffer so the user can see a fully finished frame
		SDL_UpdateWindowSurface(window_);
	}
}
