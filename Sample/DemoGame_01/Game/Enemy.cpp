#include "stdafx.h"
#include "Enemy.h"

#include "collision/CollisionObject.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/enemy/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/enemy/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/attack.tka");
	m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Damage].Load("Assets/animData/enemy/damage_receive.tka");
	m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/enemy/down.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/enemy/enemy.tkm", m_animationClips, enAnimationClip_Num);
	//m_modelRender.PlayAnimation(enAnimationClip_Run);
	//m_modelRender.Init("Assets/modelData/enemy.tkm");
	m_modelRender.SetPosition(m_position);


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
	//��]�����B
	Rotation();
	//�U�������B
	Attack();
	//�A�j���[�V�����̍Đ��B
	PlayAnimation();
	//�X�e�[�g�̊Ǘ��B
	ManageState();
	//�����蔻��B
	Collision();

	m_modelRender.Update();
}

void Enemy::Move()
{
	if (m_EnemyState == 3)
	{
		return;
	}


	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

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
	//m_moveSpeed += cameraForward * lStick_y * 250.0f;	//�������ւ̈ړ����x�����Z�B
	//m_moveSpeed += cameraRight * lStick_x * 250.0f;		//�E�����ւ̈ړ����x�����Z�B
	/*if (g_pad[0]->IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_charaCon.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
	}
	*/

	//m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B

	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

void Enemy::Rotation()
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

void Enemy::Attack()
{
	if (m_EnemyState == 3)
	{
		if (m_modelRender.IsPlayingAnimation() == false)
		{
			m_isAttack = false;
		}
		return;
	}


	if (g_pad[0]->IsTrigger(enButtonY))
	{
		m_isAttack = true;

	}
}

void Enemy::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B
	/*if (m_charaCon.IsOnGround() == false)
	{
		m_EnemyState =
		return;
	}
	*/

	if (m_isAttack == true)
	{
		m_EnemyState = 3;
		return;
	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (m_moveSpeed.LengthSq() >= 200 * 200.0f)
		{
			//�X�e�[�g�𑖂�ɂ���B
			m_EnemyState = 2;
		}
		else
		{
			//�����ɂ���B
			m_EnemyState = 1;
		}

	}
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��ҋ@�ɂ���B
		m_EnemyState = 0;
	}
}

void Enemy::PlayAnimation()
{
	switch (m_EnemyState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.5f);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Walk, 0.1f);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Attack, 0.1f);
		break;
	default:
		break;
	}
}

void Enemy::Collision()
{
	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("fire");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_charaCon) == true)
			{
				DeleteGO(this);
			}
		}
	}

	{
		auto collisions = g_collisionObjectManager->FindCollisionObjects("player_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_charaCon) == true)
			{
				DeleteGO(this);
			}
		}
	}
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}