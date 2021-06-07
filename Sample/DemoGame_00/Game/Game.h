#pragma once
#include "level3DRender/LevelRender.h"

//�N���X�錾�B
class Player;
class Background;
class GameCamera;
class SkyCube;
class Fade;
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

	/// <summary>
	/// �l���������̐���+1����B
	/// </summary>
	void AddGetStarCount()
	{
		m_starCount++;
	}
private:
	void UpdateFont();
	Player*		m_player = nullptr;			//�v���C���[�B
	Background* m_background = nullptr;		//�w�i�B
	GameCamera* m_gameCamera = nullptr;		//�Q�[���J�����B
	std::vector<Enemy*>		m_enemys;		//�G�l�~�[�̃��X�g�B
	LevelRender	m_levelRender;				//���x���B
	SkyCube*	m_skyCube = nullptr;		//�X�J�C�L���[�u�B
	bool		m_isWaitFadeout = false;
	Fade*		m_fade = nullptr;			//�t�F�[�h�B
	int			m_starCount = 0;			//�l���������̐��B
	FontRender	m_starCountFont;			//�l���������̐���\������t�H���g�B
	float		m_timer = 90.0f;			//�^�C�}�[�B
	FontRender	m_timerFont;				//�^�C�}�[��\������t�H���g�B
};

