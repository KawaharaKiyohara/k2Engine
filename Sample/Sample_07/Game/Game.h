#pragma once

//�N���X�錾�B
class Player;
class Background;

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
	Player* m_player = nullptr;
	Background* m_background = nullptr;
};

