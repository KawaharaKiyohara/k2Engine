#pragma once

class Player;

class Enemy : public IGameObject
{
public:
	enum EnEnemyState {
		enEnemyState_Idle,
		enEnemyState_Chase,
		enEnemyState_Attack,
		enEnemyState_ReceiveDamage,
		enEnemyState_Down,
	};
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	//�������Ԃ��ǂ������擾�B
	bool GetIsEnableMove() const
	{
		return m_enemyState != enEnemyState_Attack &&
			m_enemyState != enEnemyState_ReceiveDamage &&
			m_enemyState != enEnemyState_Down;
	}
private:
	void Move();
	void Chase();
	void Rotation();
	void Attack();
	void ReceiveDamage();
	void Down();
	void Collision();
	void MakeAttackCollision();
	/// <summary>
	/// �A�j���[�V�����̍Đ��B
	/// </summary>
	void PlayAnimation();
	/// <summary>
	/// �e�X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ManageState();
	//�A�j���[�V�����C�x���g
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	enum EnAnimationClip {							//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Attack,
		enAnimationClip_Damage,
		enAnimationClip_Down,
		enAnimationClip_Num,
	};
	/// <summary>
	/// ���ʂ̃X�e�[�g�J�ڏ����B
	/// </summary>
	void ProcessCommonStateTranstion();
	/// <summary>
	/// �ҋ@�X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessIdleStateTransition();
	/// <summary>
	/// �����X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessWalkStateTransition();
	/// <summary>
	/// ����X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessRunStateTransition();
	/// <summary>
	/// �`�F�C�X�X�e�[�g�̔w�J�ڏ����B
	/// </summary>
	void ProcessChaseStateTransition();
	/// <summary>
	/// �U���X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessAttackStateTransition();
	/// <summary>
	/// ��_���[�W�X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessReceiveDamageStateTransition();
	/// <summary>
	/// �_�E���X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessDownStateTransition();

	AnimationClip			m_animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	ModelRender				m_modelRender;
	Vector3					m_position;
	Vector3					m_moveSpeed;				//�ړ����x�B
	Vector3					m_forward = Vector3::AxisZ;
	Quaternion				m_rotation;					//�N�H�[�^�j�I���B
	CharacterController		m_charaCon;

	EnEnemyState			m_enemyState = enEnemyState_Idle;
	bool					m_isUnderAttack = false;
	int						m_swordBoneId = -1;
	int						m_hp = 10;
	Player*					m_player = nullptr;
};


