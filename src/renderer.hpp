#pragma once

#include <SDL.h>

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
	void KeepWindowUp();

private:
	const int screenWidth_, screenHeight_;
	SDL_Window* window_ = nullptr;
	SDL_Surface* screenSurface_ = nullptr;
	SDL_Surface* helloWorld_ = nullptr;
	void loadMedia();
};
