#pragma once

#include <string>
#include <SDL.h>
#include "UserInput.hpp"

enum class KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

class Renderer
{
public:
	Renderer(const int screenWidth, const int screenHeight);
	~Renderer(); //Frees media and shuts down SDL
	// Rule of Five: Is a renderer never copied or moved?
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	void SetCurrentSurface(KeyPressSurfaces value);
	void SwapChain();

private:
	const int screenWidth_, screenHeight_;
	SDL_Window* window_ = nullptr; //The window we'll be rendering to
	SDL_Surface* screenSurface_ = nullptr; //The surface contained by the window
	SDL_Surface* currentSurface_ = nullptr; //The image we will load and show on the screen based on user input
	SDL_Surface* keyPressSurfaces_[static_cast<size_t>(KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL)];
	SDL_Surface* LoadSurface(const std::string imageFile);
	void LoadMedia();
};
