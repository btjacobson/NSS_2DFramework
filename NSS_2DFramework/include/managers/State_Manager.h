#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <vector>
#include <mutex>

#include "states/Base_state.h"

class State_Manager
{
public:
	static State_Manager* GetInstance();

	State_Manager(State_Manager& other) = delete;

	void operator=(const State_Manager& other) = delete;

	void ChangeState(Base_State* state);
	void PushState(Base_State* state);
	void PopState();

	void HandleInput();
	void Update();

protected:
	static State_Manager* instance;
	static std::mutex mutex;

	State_Manager();
	~State_Manager();

private:
	std::vector<Base_State*> states;
};

#endif
