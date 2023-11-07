#pragma once

#include <SDL.h>
#include "Renderer.hpp"
#include "Game.hpp"

// forward declaration (compiler needs to know it will be somewhere pre-linking)
class Game;

enum class KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

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