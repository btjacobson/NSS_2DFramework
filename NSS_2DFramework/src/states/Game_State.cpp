#include "states/Game_State.h"

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

void Game_State::Update()
{

}
