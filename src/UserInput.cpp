#include "UserInput.hpp"

void UserInput::PollEvents(Game& game)
{
	while (SDL_PollEvent(&currentEvent_))
	{
		if (currentEvent_.type == SDL_QUIT) { game.Quit(); }

		// Remove this condition to capture ALL event types, including init event(s)
		else if (currentEvent_.type == SDL_KEYDOWN)
		{
			SDL_Keycode code = currentEvent_.key.keysym.sym;

			switch (code)
			{
			case SDLK_LEFT:
				game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
				break;
			case SDLK_RIGHT:
				game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
				break;
			case SDLK_UP:
				game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_UP);
				break;
			case SDLK_DOWN:
				game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
				break;
			default:
				game.GetRenderer().SetCurrentSurface(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
				break;
			}
		}
	}
}
