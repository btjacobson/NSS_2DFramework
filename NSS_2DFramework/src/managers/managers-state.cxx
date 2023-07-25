module;
#include <vector>
#include <mutex>
export module framework:managers.state;

import :states.base;

export class State_Manager
{
public:
	static State_Manager* GetInstance();

	State_Manager(State_Manager& other) = delete;

	void operator=(const State_Manager& other) = delete;

	void ChangeState(Base_State* state);
	void PushState(Base_State* state);
	void PopState();

	void HandleInput();
	void Update(float deltaTime);
	void Draw();

protected:
	static State_Manager* instance;
	static std::mutex mutex;

	State_Manager();
	~State_Manager();

private:
	std::vector<Base_State*> states;
};

State_Manager* State_Manager::instance = nullptr;
std::mutex State_Manager::mutex;

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
	std::lock_guard<std::mutex> lock(mutex);

	if (instance == nullptr)
	{
		instance = new State_Manager();
	}

	return instance;
}

void State_Manager::ChangeState(Base_State* state)
{
	std::lock_guard<std::mutex> lock(mutex);

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
	std::lock_guard<std::mutex> lock(mutex);

	if (!states.empty())
	{
		states.back()->Pause();
	}

	states.push_back(state);
	states.back()->Init();
}

void State_Manager::PopState()
{
	std::lock_guard<std::mutex> lock(mutex);

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

void State_Manager::Update(float deltaTime)
{
	states.back()->Update(deltaTime);
}

void State_Manager::Draw()
{
	states.back()->Draw();
}
