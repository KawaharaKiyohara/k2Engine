#pragma once

//�N���X�錾�B
class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	Player* m_player = nullptr;		//�v���C���[�B
};

