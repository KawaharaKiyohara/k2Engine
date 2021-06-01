#pragma once

//�N���X�錾�B
class Player;
class Background;
class GameCamera;
class Box;

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
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	Player*			m_player = nullptr;				//�v���C���[�B
	Background*		m_background = nullptr;			//�w�i�B
	GameCamera*		m_gameCamera = nullptr;			//�Q�[���J�����B
	Box*			m_box = nullptr;				//�{�b�N�X�B
	FontRender		m_fontRender;					//�t�H���g�B
	bool			m_isHit = false;				//�L�����R���ƃS�[�X�g���Փ˂����H
};

