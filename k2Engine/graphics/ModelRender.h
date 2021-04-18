#pragma once

#include "MyRenderer.h"

class RenderingEngine;
/// <summary>
/// �X�L�����f�������_�[�B
/// </summary>
class ModelRender
{
public:
	ModelRender() {}
	/// <summary>
	/// �������B
	/// �f�B�t�@�[�h�����_�����O�B
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
	/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
	/// <param name="">���f���̏�����B</param>
	/// <param name="">true�Ȃ�e��������B</param>
	void Init(const char* filePath,
		AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0,
		EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
		bool isShadowReciever = true);
	/// <summary>
/// �������B
/// �t�H���[�h�����_�����O�B
/// </summary>
/// <param name="filePath">�t�@�C���p�X�B</param>
/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
/// <param name="">���f���̏�����B</param>
/// <param name="">true�Ȃ�e��������B</param>
	void InitForwardRendering(const char* filePath,
		AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0,
		EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
		bool isShadowReciever = true);
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈���B
	/// </summary>
	void Draw();

	/// <summary>
	/// �A�j���[�V�����Đ��B
	/// </summary>
	/// <param name="animNo">�A�j���[�V�����N���b�v�̔ԍ��B</param>
	/// <param name="interpolateTime">�⊮����(�P�ʁF�b�B)</param>
	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	/// <summary>
	/// �A�j���[�V�����̍Đ����H
	/// </summary>
	bool IsPlayingAnimation() const
	{
		return m_animation.IsPlaying();
	}

	/// <summary>
	/// ���f�����擾�B
	/// </summary>
	/// <returns>���f��</returns>
	Model& GetModel()
	{
		return m_zprepassModel;
	}

	/// <summary>
	/// ���W�A��]�A�g���S�čX�V�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	/// <param name="rotation">��]�B</param>
	/// <param name="scale">�g��B</param>
	void SetTRS(const Vector3& pos, const Quaternion& rotation, const Vector3& scale)
	{
		SetPosition(pos);
		SetRotation(rotation);
		SetScale(scale);
	}

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
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
	/// �傫���B
	/// </summary>
	/// <param name="scale">�傫���B</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
/// �V���h�E�L���X�^�[�̃t���O��ݒ肷��
/// </summary>
	void SetShadowCasterFlag(bool flag)
	{
		m_isShadowCaster = flag;
	}
private:
	/// <summary>
	/// ���f���̏������B
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	/// <param name="enModelUpAxis">���f���̏�����B</param>
	void InitModel(const char* filePath, EnModelUpAxis enModelUpAxis);
	/// <summary>
	/// �X�P���g���̏������B
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X�B</param>
	void InitSkeleton(const char* filePath);
	/// <summary>
	/// �A�j���[�V�����̏������B
	/// </summary>
	/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
	/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
	/// <param name="enModelUpAxis">���f���̏�����B</param>
	void InitAnimation(AnimationClip* animationClips,
		int numAnimationClips, 
		EnModelUpAxis enModelUpAxis);
private:
	/// <summary>
	 /// ���ʂ̏���������
	 /// </summary>
	 /// <param name="renderingEngine">�����_�����O�G���W��</param>
	 /// <param name="tkmFilePath">tkm�t�@�C���p�X</param>
	void InitCommon(RenderingEngine& renderingEngine, const char* tkmFilePath);
private:
	AnimationClip*				m_animationClips = nullptr;			//�A�j���[�V�����N���b�v�B
	int							m_numAnimationClips = 0;			//�A�j���[�V�����N���b�v�̐��B
	Vector3 					m_position = Vector3::Zero;			//���W�B
	Quaternion	 				m_rotation = Quaternion::Identity;	//��]�B
	Vector3						m_scale = Vector3::One;				//�g�嗦�B
	EnModelUpAxis				m_enFbxUpAxis = enModelUpAxisZ;		//FBX�̏�����B
	Animation					m_animation;						//�A�j���[�V�����B
	Model m_zprepassModel;					//ZPrepass�ŕ`�悳��郂�f��
	Model m_forwardRenderModel;				//�t�H���[�h�����_�����O�̕`��p�X�ŕ`�悳��郂�f��
	Model m_renderToGBufferModel;			//RenderToGBuffer�ŕ`�悳��郂�f��
	Model m_shadowModels[NUM_DEFERRED_LIGHTING_DIRECTIONAL_LIGHT][NUM_SHADOW_MAP];	//�V���h�E�}�b�v�ɕ`�悷�郂�f��
	bool						m_isUpdateAnimation = true;			//�A�j���[�V�������X�V����H
	Skeleton					m_skeleton;							//���B
	bool						m_isShadowCaster = true;			//�V���h�E�L���X�^�[�t���O
};

