module;

export module framework:states.mainmenu;

import :states.base;

export class MainMenu_State : public Base_State
{
public:
	MainMenu_State();

	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleInput();
	void Update(float deltaTime);
	void Draw();
};

MainMenu_State::MainMenu_State()
{

}

void MainMenu_State::Init()
{

}

void MainMenu_State::Cleanup()
{

}

void MainMenu_State::Pause()
{

}

void MainMenu_State::Resume()
{

}

void MainMenu_State::HandleInput()
{

}

void MainMenu_State::Update(float deltaTime)
{

}

void MainMenu_State::Draw()
{

}
