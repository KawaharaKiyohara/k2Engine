

class Player : public IGameObject
{
public:
	////////////////////////////////////
	// �����o�֐�
	////////////////////////////////////
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	ModelRender m_modelRender;
	Vector3 m_position;						//���W�B
	CharacterController m_charaCon;			//�L�����N�^�[�R���g���[���[�B
	Vector3 m_moveSpeed;					//�ړ����x�B
};

