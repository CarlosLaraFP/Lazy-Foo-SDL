#include "UserInput.hpp"

void UserInput::PollEvents(Game& game)
{
	while (SDL_PollEvent(&currentEvent_))
	{
		if (currentEvent_.type == SDL_QUIT) { game.Quit(); }

		SDL_Scancode code = currentEvent_.key.keysym.scancode;

		switch (code)
		{
		case SDL_SCANCODE_LEFT:
			game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
			break;
		case SDL_SCANCODE_RIGHT:
			game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
			break;
		case SDL_SCANCODE_UP:
			game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_UP);
			break;
		case SDL_SCANCODE_DOWN:
			game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
			break;
		default:
			game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
			break;
		}
	}
}
