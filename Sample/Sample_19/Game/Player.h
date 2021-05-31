

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
	void Turn();
	void ManageState();
	void PlayAnimation();
	////////////////////////////////////
	// �����o�ϐ��Ƃ�
	////////////////////////////////////
	ModelRender			m_modelRender;
	Vector3				m_position;					//���W�B
	CharacterController m_charaCon;					//�L�����N�^�[�R���g���[���[�B
	Vector3				m_moveSpeed;				//�ړ����x�B
	Quaternion			m_rotation;					//�N�H�[�^�j�I���B
	enum EnAnimationClip {							//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip		m_animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	int m_playerState = 0;							//�v���C���[�̃X�e�[�g(���)��\���ϐ��B
};

