#pragma once

#include "UserInput.hpp"
#include "Renderer.hpp"

// forward declarations
class UserInput;
class Renderer;

class Game
{
public:
	Game(UserInput& input, Renderer& renderer) : input_{ input }, renderer_{ renderer } {};
	void StartGameLoop();
	void Quit();
	Renderer& GetRenderer();

private:
	UserInput& input_;
	Renderer& renderer_;
	bool quit_ = false;
};
