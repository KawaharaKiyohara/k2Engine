#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/enemy/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//�G�l�~�[�̃��f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/enemy.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisZ);
	//���W��傫����ݒ�B
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0f,			//���a�B
		100.0f,			//�����B
		m_position		//���W�B
	);

	return true;
}

void Enemy::Update()
{
	//�ړ������B
	Move();
	//���񏈗��B
	Turn();
	//�X�e�[�g�Ǘ��B
	ManageState();
	//�A�j���[�V�����Đ��B
	PlayAnimation();

	//���f�����X�V�B
	m_modelRender.Update();
}

void Enemy::Move()
{
	//���̃t���[���̈ړ��ʂ����߂�B
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += cameraForward * lStick_y * 500.0f;	//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight * lStick_x * 500.0f;		//�E�����ւ̈ړ����x�����Z�B
	if (g_pad[0]->IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		//m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
	}
	//m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B

	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}

	//���W��ݒ�B
	m_modelRender.SetPosition(m_position);
}

void Enemy::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotationY(-angle);

	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);
}

void Enemy::ManageState()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��1(����)�ɂ���B
		m_enemyState = 1;
	}
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��0(�ҋ@)�ɂ���B
		m_enemyState = 0;
	}
}

void Enemy::PlayAnimation()
{
	//switch���B
	switch (m_enemyState) {
		//�v���C���[�X�e�[�g��0(�ҋ@)��������B
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//�v���C���[�X�e�[�g��1(����)��������B
	case 1:
		//����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}