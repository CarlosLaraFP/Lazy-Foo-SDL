#include <stdexcept>
#include <SDL.h>

void ThrowSDLError(const std::string& message)
{
	throw std::runtime_error(message + " SDL Error: " + SDL_GetError());
}