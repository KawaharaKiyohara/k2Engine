#pragma once

//�N���X�錾�B
class SoundSource;

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
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	SoundSource* m_soundSource = nullptr;		//BGM�B
};
