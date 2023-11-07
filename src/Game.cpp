#include <thread>
#include <chrono>

#include "Game.hpp"

//Hack to get window to stay up
void Game::StartGameLoop()
{
	while (!quit_)
	{
		// Otherwise, CPU utilization goes from ~0% -> ~20%
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		// Handle events on queue: When you press a key, move the mouse, or touch a touch screen you put events onto the event queue.
		// SDL_PollEvent takes the most recent event from the queue and puts the data from the event into the SDL_Event we passed into the function.
		input_.PollEvents(*this);

		renderer_.SwapChain();
	}
}

void Game::Quit() { quit_ = true; }

Renderer& Game::GetRenderer() { return renderer_; }