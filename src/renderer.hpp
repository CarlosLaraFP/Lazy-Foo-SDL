#pragma once

#include <SDL.h>

class Renderer
{
public:
	Renderer(const int screenWidth, const int screenHeight);
	~Renderer();
	// Rule of Five: Is a renderer never copied or moved? 

private:
	const int screenWidth_, screenHeight_;
	SDL_Window* window_ = nullptr;
	SDL_Surface* screenSurface_ = nullptr;
};
