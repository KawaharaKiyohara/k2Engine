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
	ModelRender m_modelRender;		//���f�������_�\�B
	Quaternion m_rotation;			//�N�H�[�^�j�I���B
	int m_rotateMode = 0;			//0�͎�����]�A1�̓X�e�B�b�N�ŉ�]�B
};

