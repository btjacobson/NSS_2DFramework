module;

export module framework:states.base;

export class Base_State
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleInput() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

protected:
	Base_State() {}
};