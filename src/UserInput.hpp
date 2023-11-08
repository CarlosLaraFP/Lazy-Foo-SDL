#pragma once

#include <SDL.h>
#include "Renderer.hpp"
#include "Game.hpp"

// forward declaration (compiler needs to know it will be somewhere pre-linking)
class Game;

class UserInput
{
public:
	UserInput() {};
	~UserInput() {};
	void PollEvents(Game& game);

private:
	// An SDL event is something like a key press, mouse motion, joy button press, etc.
	SDL_Event currentEvent_;
};
