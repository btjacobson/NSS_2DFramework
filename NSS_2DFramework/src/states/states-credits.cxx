module;
export module framework:states.credits;

import :states.base;

export class Credits_State : public Base_State
{
public:
	Credits_State();

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleInput();
	void Update(float deltaTime);
	void Draw();
};

Credits_State::Credits_State()
{

}

void Credits_State::Init()
{

}

void Credits_State::Cleanup()
{

}

void Credits_State::Pause()
{

}

void Credits_State::Resume()
{

}

void Credits_State::HandleInput()
{

}

void Credits_State::Update(float deltaTime)
{

}

void Credits_State::Draw()
{

}
