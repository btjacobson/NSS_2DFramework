#ifndef MAINMENU_STATE_H
#define MAINMENU_STATE_H

#include "Base_State.h"

class MainMenu_State : public Base_State
{
public:
	MainMenu_State();

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleInput();
	void Update(float deltaTime);
};

#endif