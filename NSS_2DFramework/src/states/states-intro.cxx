module;
#include <iostream>
export module framework:states.intro;

import :states.base;

export class Intro_State : public Base_State
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

Intro_State::Intro_State()
{

}

void Intro_State::Init()
{
	std::cout << "Intro State" << std::endl;
}

void Intro_State::Cleanup()
{

}

void Intro_State::Pause()
{

}

void Intro_State::Resume()
{

}

void Intro_State::HandleInput()
{

}

void Intro_State::Update(float deltaTime)
{

}

void Intro_State::Draw()
{

}
