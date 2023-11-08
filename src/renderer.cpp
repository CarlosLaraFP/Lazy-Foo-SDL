#include "Renderer.hpp"
#include "Error.hpp"

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

	SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
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

	/*
		When you load a bitmap, it's typically loaded in a 24bit format since most bitmaps are 24bit. 
		Most, if not all, modern displays are not 24bit by default. If we blit an image that's 24bit 
		onto a 32bit image, SDL will convert it every single time the image is blitted. Therefore, 
		we convert it to the same format as the screen so no conversion needs to be done on blit.
	*/
	SDL_Surface* optimizedSurface = SDL_ConvertSurface(surface, screenSurface_->format, 0);

	if (optimizedSurface == nullptr)
	{
		ThrowSDLError("Unable to optimize image: " + imagePath);
	}

	/*
		SDL_ConvertSurface returns a copy of the original in a new format. The original loaded image is still in memory after the call. 
		This means we have to free the original loaded surface or we'll have two copies of the same image in memory.
	*/
	SDL_FreeSurface(surface);

	return optimizedSurface;
}

void Renderer::SetCurrentSurface(KeyPressSurfaces value)
{
	currentSurface_ = keyPressSurfaces_[static_cast<size_t>(value)];
}

void Renderer::SwapChain()
{
	/*
		SDL 2 has a new dedicated function to blit images to a different size: SDL_BlitScaled. 
		Like blitting images before, SDL_BlitScaled takes in a source surface to blit onto the destination surface. 
		It also takes in a destination SDL_Rect which defines the position and size of the image you are blitting.
		If we want to take an image that's smaller than the screen and make it the size of the screen, 
		we make the destination width/height to be the width/height of the screen.
	*/

	//Apply the image stretched by drawing to the back buffer first
	SDL_Rect stretchRect {};
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = screenWidth_;
	stretchRect.h = screenHeight_;
	SDL_BlitScaled(currentSurface_, nullptr, screenSurface_, &stretchRect);

	//Swap the back and front buffer so the user can see a fully finished frame
	SDL_UpdateWindowSurface(window_);
}
