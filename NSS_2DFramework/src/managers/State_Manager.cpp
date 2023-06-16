#include "managers/State_Manager.h"

State_Manager* State_Manager::instance = nullptr;

State_Manager::State_Manager()
{

}

State_Manager::~State_Manager()
{
	for (auto state : states)
	{
		state->Cleanup();
		delete state;
	}

	states.clear();
}

State_Manager* State_Manager::GetInstance()
{
	return nullptr;
}

void State_Manager::ChangeState(Base_State* state)
{
	if (!states.empty())
	{
		states.back()->Cleanup();
		delete states.back();
		states.pop_back();
	}

	states.push_back(state);
	states.back()->Init();
}

void State_Manager::PushState(Base_State* state)
{
	if (!states.empty())
	{
		states.back()->Pause();
	}

	states.push_back(state);
	states.back()->Init();
}

void State_Manager::PopState()
{
	if (!states.empty())
	{
		states.back()->Cleanup();
		delete states.back();
		states.pop_back();
	}

	if (!states.empty())
	{
		states.back()->Resume();
	}
}

void State_Manager::HandleInput()
{
	states.back()->HandleInput();
}

void State_Manager::Update()
{
	states.back()->Update();
}
