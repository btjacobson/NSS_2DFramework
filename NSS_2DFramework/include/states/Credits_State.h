#ifndef CREDITS_STATE_H
#define CREDITS_STATE_H

#include "Base_State.h"

class Credits_State : public Base_State
{
public:
	Credits_State();

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleInput();
	void Update();
};

#endif
