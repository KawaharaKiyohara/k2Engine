#pragma once
class Enemy : public IGameObject
{
public:
	////////////////////////////////////
	// �����o�֐�
	////////////////////////////////////
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <returns>���W�B</returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �傫����ݒ�B
	/// </summary>
	/// <param name="scale">�傫���B</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
private:
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();
	/// <summary>
	/// ��]�����B
	/// </summary>
	void Turn();
	/// <summary>
	/// �X�e�[�g���Ǘ��B
	/// </summary>
	void ManageState();
	/// <summary>
	/// �A�j���[�V�����̍Đ��B
	/// </summary>
	void PlayAnimation();
	ModelRender			m_modelRender;				//���f�������_�\�B
	Vector3				m_position;					//���W�B
	CharacterController m_charaCon;					//�L�����N�^�[�R���g���[���[�B
	Vector3				m_moveSpeed;				//�ړ����x�B
	Vector3				m_scale = Vector3::One;		//�X�P�[���B
	Quaternion			m_rotation;					//�N�H�[�^�j�I���B
	enum EnAnimationClip {							//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip		m_animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	int m_enemyState = 0;							//�G�l�~�[�̃X�e�[�g(���)��\���ϐ��B
};

