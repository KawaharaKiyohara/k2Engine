#pragma once
class Box : public IGameObject
{
public:
	Box();
	~Box();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender				m_modelRender;				//���f�������_���[�B
	Vector3					m_position;					//���W�B
	PhysicsStaticObject		m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g�B
};

