#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Base_State.h"
#include "core/Camera2D.h"

class Game_State : public Base_State
{
public:
	Game_State();

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleInput();
	void Update();

private:
	Camera2D camera;
};

#endif