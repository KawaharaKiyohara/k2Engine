#pragma once

//�N���X�錾�B
class Player;
class Background;
class GameCamera;

class Game : public IGameObject
{
public:
	//////////////////////////////////////
	// �����o�֐��B
	//////////////////////////////////////
	Game();
	~Game();
	bool Start();

	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	Player* m_player = nullptr;				//�v���C���[�B
	Background* m_background = nullptr;		//�w�i�B
	GameCamera* m_gameCamera = nullptr;		//�Q�[���J�����B
};

