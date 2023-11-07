#pragma once

#include <string>
#include <SDL.h>
#include "UserInput.hpp"

// forward declaration
enum class KeyPressSurfaces;

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
	//const size_t keyPressSurfaceTotal_;
	SDL_Window* window_ = nullptr; //The window we'll be rendering to
	SDL_Surface* screenSurface_ = nullptr; //The surface contained by the window
	SDL_Surface* currentSurface_ = nullptr; //The image we will load and show on the screen based on user input
	SDL_Surface* keyPressSurfaces_[5];
	SDL_Surface* LoadSurface(const std::string imageFile);
	void LoadMedia();
};
