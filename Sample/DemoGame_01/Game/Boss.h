#pragma once

class Player;

class Boss : public IGameObject
{
public:
	enum EnBossState {
		enBossState_Idle,
		enBossState_Chase,
		enBossState_Attack,
		enBossState_MagicAttack,
		enBossState_ReceiveDamage,
		enBossState_Down,
	};
public:
	Boss();
	~Boss();
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
	void SetHP(const int hp)
	{
		m_hp = hp;
	}
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	//�������Ԃ��ǂ������擾�B
	const bool GetIsEnableMove() const
	{
		return m_BossState != enBossState_Attack &&
			m_BossState != enBossState_ReceiveDamage &&
			m_BossState != enBossState_Down;
	}
private:
	void Chase();
	void Rotation();
	void Attack();
	void ReceiveDamage();
	void Down();
	void Collision();
	const bool SearchPlayer() const;
	void MakeAttackCollision();
	void MakeFireBall();
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
		enAnimationClip_MagicAttack,
		enAnimationClip_Damage,
		enAnimationClip_Down,
		enAnimationClip_Num,
	};
	/// <summary>
	/// ���ʂ̃X�e�[�g�J�ڏ����B
	/// </summary>
	void ProcessCommonStateTransition();
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
	/// �ǐՃX�e�[�g�̔w�J�ڏ����B
	/// </summary>
	void ProcessChaseStateTransition();
	/// <summary>
	/// �U���X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessAttackStateTransition();
	/// <summary>
	/// ���@�U���X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessMagicAttackStateTransition();
	/// <summary>
	/// ��_���[�W�X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessReceiveDamageStateTransition();
	/// <summary>
	/// �_�E���X�e�[�g�̑J�ڏ����B
	/// </summary>
	void ProcessDownStateTransition();
	/// <summary>
	/// �U���ł��鋗�����ǂ������ׂ�B
	/// </summary>
	/// <returns>�U���ł���Ȃ�true�B</returns>
	const bool IsCanAttack() const;

	AnimationClip			m_animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	ModelRender				m_modelRender;
	Vector3					m_position;
	Vector3					m_spawnPosition;
	Vector3					m_moveSpeed;				//�ړ����x�B
	Vector3					m_forward = Vector3::AxisZ;
	Quaternion				m_rotation;					//�N�H�[�^�j�I���B
	Vector3					m_scale = Vector3::One;
	CharacterController		m_charaCon;

	EnBossState				m_BossState = enBossState_Idle;
	bool					m_isUnderAttack = false;
	int						m_swordBoneId = -1;
	int						m_hp = 10;
	Player*					m_player = nullptr;
	float					m_chaseTimer = 0.0f;
	float					m_idleTimer = 0.0f;
};



