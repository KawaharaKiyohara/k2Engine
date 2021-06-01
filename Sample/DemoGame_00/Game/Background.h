#pragma once

class Background : public IGameObject
{
public:
	//////////////////////////////////////
	// �����o�֐��B
	//////////////////////////////////////
	Background();
	~Background();
	bool Start();
	void Render(RenderContext& rc);

	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	ModelRender			m_modelRender;							//���f�������_���[�B
	PhysicsStaticObject m_phyStaticObject;						//�ÓI�����I�u�W�F�N�g�B
	Vector3				m_position;								//���W�B
	Quaternion			m_rotation = Quaternion::Identity;		//��]�B
	Vector3				m_scale = Vector3::One;					//�傫���B
};