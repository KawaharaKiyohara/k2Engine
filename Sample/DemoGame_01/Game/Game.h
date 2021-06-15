#pragma once

#include "level3DRender/LevelRender.h"


class Player;
class GameCamera;
class SkyCube;
class Background;
class Enemy;

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
private:
	LevelRender			m_levelRender;
	Player*				m_player = nullptr;
	GameCamera*			m_gameCamera = nullptr;
	SkyCube*			m_skyCube = nullptr;
	Background*			m_background = nullptr;
	Enemy*				m_enemy = nullptr;
};

