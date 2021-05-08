#pragma once
#include "Effect.h"

/// <summary>
/// �G�t�F�N�g�𔭐��A�Đ�����N���X�B
/// </summary>
class EffectEmitter : public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	EffectEmitter();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~EffectEmitter();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// �G�t�F�N�g��ǂݍ��ށB
	/// </summary>
	/// <param name="number">EffectEngine::GetInstance()->ResistEffect�Ŏw�肵���ԍ��B</param>
	void Init(const int number);
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position">���W�B/param>
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
	/// �X�P�[��(�g�嗦��ݒ�)�B
	/// </summary>
	/// <param name="scale">�X�P�[��(�g�嗦)�B</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �X�P�[��(�g�嗦)���擾�B
	/// </summary>
	/// <returns>�X�P�[��(�g�嗦)�B</returns>
	const Vector3& GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// ��]���擾�B
	/// </summary>
	/// <returns>��]�B</returns>
	const Quaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// �ړ����x��ݒ�B
	/// </summary>
	/// <param name="moveSpeed">�ړ����x�B</param>
	void SetMoveSpeed(const Vector3& moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	/// <summary>
	/// �ړ����x���擾�B
	/// </summary>
	/// <returns>�ړ����x�B</returns>
	const Vector3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/// <summary>
	/// �Đ������ǂ������擾�B
	/// </summary>
	/// <returns>�Đ����Ȃ�true�B</returns>
	const bool GetIsPlay() const
	{
		return m_effect.IsPlay();
	}
private:
	Effect m_effect;					//�G�t�F�N�g�B
	Vector3 m_position;					//���W�B
	Vector3 m_moveSpeed;				//�ړ����x�B
	Quaternion m_rotation;				//��]�B
	Vector3 m_scale = g_vec3One;		//�X�P�[��(�g�嗦)�B
};

