#pragma once
class Game : public IGameObject
{
public:
	//////////////////////////////////////
	// �����o�֐��B
	//////////////////////////////////////
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//////////////////////////////////////
	// �����o�ϐ��B
	//////////////////////////////////////
	SpriteRender m_spriteRender;
};
