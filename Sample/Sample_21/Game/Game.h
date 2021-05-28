#pragma once

//Level2D���g�p����ɂ̓t�@�C�����C���N���[�h����K�v������B
#include "level2DRender/Level2DRender.h"

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
	ModelRender		m_modelRender;
	Level2DRender	m_level2DRender;
	SpriteRender	m_spriteRender;
};

