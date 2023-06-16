#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include "Base_State.h"

class Intro_State : public Base_State
{
public:
	Intro_State();

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleInput();
	void Update(float deltaTime);
	void Draw();
};

#endif
