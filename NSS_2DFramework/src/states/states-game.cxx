module;
#include <glm.hpp>
export module framework:states.game;

import :states.base;
import :core.camera2d;

export class Game_State : public Base_State
{
public:
	Game_State();

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleInput();
	void Update(float deltaTime);
	void Draw();

private:
	Camera2D camera;
};

Game_State::Game_State() : camera(800, 600)
{
	camera.SetZoom(50.0f);
	camera.SetPosition(glm::vec2(-25.0f, -25.0f));
}

void Game_State::Init()
{

}

void Game_State::Cleanup()
{

}

void Game_State::Pause()
{

}

void Game_State::Resume()
{

}

void Game_State::HandleInput()
{

}

void Game_State::Update(float deltaTime)
{

}

void Game_State::Draw()
{

}
