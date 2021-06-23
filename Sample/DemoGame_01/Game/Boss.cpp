#include "stdafx.h"
#include "Boss.h"


#include "Game.h"
#include "FireBall.h"
#include "Player.h"

#include "collision/CollisionObject.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

#include <time.h>
#include <stdlib.h>

Boss::Boss()
{

}

Boss::~Boss()
{

}

bool Boss::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/enemy/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/enemy/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/attack.tka");
	m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
	m_animationClips[enAnimationClip_MagicAttack].Load("Assets/animData/enemy/magicattack.tka");
	m_animationClips[enAnimationClip_MagicAttack].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Damage].Load("Assets/animData/enemy/receivedamage.tka");
	m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/enemy/down.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);
	m_modelRender.Init("Assets/modelData/boss/boss.tkm", m_animationClips, enAnimationClip_Num);
	m_modelRender.SetPosition(m_position);
	m_spawnPosition = m_position;
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0f,			//���a�B
		100.0f,			//�����B
		m_position		//���W�B
	);

	m_swordBoneId = m_modelRender.FindBoneID(L"Sword");

	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/efk/enemy_slash_01.efk");
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/efk/cast_fire.efk");
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/magic.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/slash.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/hit.wav");

	m_player = FindGO<Player>("player");
	//�������������B
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
	return true;
}

void Boss::Update()
{
	//�ǐՏ����B
	Chase();
	//��]�����B
	Rotation();
	//�����蔻��B
	Collision();
	//�U�������B
	Attack();
	//��_���[�W�B
	ReceiveDamage();
	//�_�E���B
	Down();
	//�A�j���[�V�����̍Đ��B
	PlayAnimation();
	//�X�e�[�g�̑J�ڏ����B
	ManageState();



	//���f���̍X�V�B
	m_modelRender.Update();
}

void Boss::Rotation()
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

	//�v���C���[�̑O�x�N�g�����v�Z����B
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Boss::Chase()
{
	//�ǐՃX�e�[�g�łȂ��Ȃ�A�ǐՏ����͂��Ȃ��B
	if (m_BossState != enBossState_Chase)
	{
		return;
	}

	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	//������Ƃ������f���̍��W��������B
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

void Boss::Collision()
{
	if (m_BossState == enBossState_ReceiveDamage ||
		m_BossState == enBossState_Down)
	{
		return;
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_attack");
		for (auto collision : collisions)
		{
			if (collision->IsHit(m_charaCon))
			{
				m_hp -= 1;
				if (m_hp <= 0)
				{
					m_BossState = enBossState_Down;
				}
				else {
					m_BossState = enBossState_ReceiveDamage;
				}
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(4);
				se->Play(false);
				se->SetVolume(0.4f);
				return;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_fireball");
		for (auto collision : collisions)
		{
			if (collision->IsHit(m_charaCon))
			{
				m_hp -= 1;
				if (m_hp <= 0)
				{
					m_BossState = enBossState_Down;
				}
				else {
					m_BossState = enBossState_ReceiveDamage;
				}
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(4);
				se->Play(false);
				se->SetVolume(0.6f);
				return;
			}
		}
	}

}

void Boss::Attack()
{
	if (m_BossState != enBossState_Attack)
	{
		return;
	}

	//�U�����蒆�ł���΁B
	if (m_isUnderAttack == true)
	{
		//�U���p�̃R���W�������쐬����B
		MakeAttackCollision();
	}
}

const bool Boss::SearchPlayer() const
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//�v���C���[�ɂ�����x�߂�������.�B
	if (diff.LengthSq() <= 700.0 * 700.0f)
	{
		//�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K������B
		diff.Normalize();
		//�G�l�~�[�̐��ʂ̃x�N�g���ƁA�G�l�~�[����v���C���[�Ɍ������x�N�g���́B
		//����(cos��)�����߂�B
		float cos = m_forward.Dot(diff);
		//����(cos��)����p�x(��)�����߂�B
		float angle = acosf(cos);
		//�p�x(��)��180����菬������΁B
		if (angle <= (Math::PI / 180.0f) * 180.0f)
		{
			//�v���C���[���������I
			return true;
		}
	}

	return false;
}

void Boss::ReceiveDamage()
{
	if (m_BossState != enBossState_ReceiveDamage)
	{
		return;
	}
}

void Boss::Down()
{
	if (m_BossState != enBossState_Down)
	{
		return;
	}
}

void Boss::MakeAttackCollision()
{
	auto collisionObject = NewGO<CollisionObject>(0);
	Matrix matrix = m_modelRender.GetBone(m_swordBoneId)->GetWorldMatrix();
	collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(100.0f, 10.0f, 10.0f));
	collisionObject->SetWorldMatrix(matrix);
	collisionObject->SetName("enemy_attack");
}

void Boss::MakeFireBall()
{
	FireBall* fireBall = NewGO<FireBall>(0);
	Vector3 fireBallPosition = m_position;
	fireBallPosition.y += 70.0f;
	fireBall->SetPosition(fireBallPosition);
	fireBall->SetRotation(m_rotation);
	fireBall->SetEnMagician(FireBall::enMagician_Enemy);
}

void Boss::ProcessCommonStateTransition()
{
	//�e�^�C�}�[���������B
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;

	//�܂��r���B
	{
		Vector3 diff = m_spawnPosition - m_position;

	}
	Vector3 diff = m_player->GetPosition() - m_position;

	//�v���C���[����������B
	if (SearchPlayer())
	{
		diff.Normalize();
		//�ړ����x��ݒ肷��B
		m_moveSpeed = diff * 320.0f;
		//�U���ł��鋗���Ȃ�B
		if (IsCanAttack())
		{
			//�����ɂ���āA�U�����邩�ҋ@�����邩�����肷��B	
			int ram = rand() % 100;
			if (ram > 30)
			{
				//�U���X�e�[�g�Ɉڍs����B
				m_BossState = enBossState_Attack;
				m_isUnderAttack = false;
				return;
			}
			else
			{
				//�ҋ@�X�e�[�g�Ɉڍs����B
				m_BossState = enBossState_Idle;
				return;
			}

		}
		//�U���ł��Ȃ������Ȃ�B
		else
		{
			//�����ɂ���āA�ǐՂ����邩���@�U�������邩���肷��B	
			int ram = rand() % 100;
			if (ram > 40)
			{
				//�ǐՃX�e�[�g�Ɉڍs����B
				m_BossState = enBossState_Chase;
				return;
			}
			else {
				//���݂����@�U���X�e�[�g�Ȃ�B
				//�A���Ŗ��@���������Ȃ��悤�ɂ���B
				if (m_BossState == enBossState_MagicAttack)
				{
					//�ǐՃX�e�[�g�Ɉڍs����B
					m_BossState = enBossState_Chase;
					return;
				}
				else
				{
					//���@�U���X�e�[�g�Ɉڍs����B
					m_BossState = enBossState_MagicAttack;
					EffectEmitter* effect = NewGO<EffectEmitter>(0);
					effect->Init(2);
					Vector3 effectPosition = m_position;
					effect->SetPosition(m_position);
					effect->SetScale(Vector3::One * 10.0f);
					effect->Play();
					return;
				}
			}
		}
	}
	//�v���C���[���������Ȃ���΁B
	else
	{
		//�ҋ@�X�e�[�g�Ɉڍs����B
		m_BossState = enBossState_Idle;
		return;

	}
}

void Boss::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//�ҋ@���Ԃ�������x�o�߂�����B
	if (m_idleTimer >= 0.5f)
	{
		//���̃X�e�[�g�ֈڍs����B
		ProcessCommonStateTransition();
	}

}

void Boss::ProcessWalkStateTransition()
{
	ProcessCommonStateTransition();
}

void Boss::ProcessRunStateTransition()
{
	ProcessCommonStateTransition();
}

void Boss::ProcessChaseStateTransition()
{
	//�U���ł��鋗���Ȃ�B
	if (IsCanAttack())
	{
		//�ǐՃX�e�[�g���瑼�̃X�e�[�g�ֈڍs����B
		ProcessCommonStateTransition();
		return;
	}
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//�ǐՎ��Ԃ�������x�o�߂�����B
	if (m_chaseTimer >= 0.5f)
	{
		ProcessCommonStateTransition();
	}
}

void Boss::ProcessAttackStateTransition()
{
	//�U���A�j���[�V�����̍Đ����I�������B
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//�X�e�[�g��J�ڂ���B
		ProcessCommonStateTransition();
	}
}

void Boss::ProcessMagicAttackStateTransition()
{
	//���@�U���A�j���[�V�����̍Đ����I�������B
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//�X�e�[�g��J�ڂ���B
		ProcessCommonStateTransition();
	}
}

void Boss::ProcessReceiveDamageStateTransition()
{
	//��_���[�W�A�j���[�V�����̍Đ����I�������B
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//�U�����ꂽ�狗���֌W�����ɁA��芸�����ǐՂ�����B
		m_BossState = enBossState_Chase;
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.Normalize();
		//�ړ����x��ݒ肷��B
		m_moveSpeed = diff * 150.0f;
	}
}

void Boss::ProcessDownStateTransition()
{
	//�_�E���A�j���[�V�����̍Đ����I�������B
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		Game* game = FindGO<Game>("game");
		game->AddDefeatedEnemyNumber();
		DeleteGO(this);
	}
}

void Boss::ManageState()
{
	switch (m_BossState)
	{
	case enBossState_Idle:
		ProcessIdleStateTransition();
		break;
		/*case enBossState_Walk:
			ProcessWalkStateTransition();
			break;
		case enBossState_Run:
			ProcessRunStateTransition();
			break;
		*/
	case enBossState_Chase:
		ProcessChaseStateTransition();
		break;
	case enBossState_Attack:
		ProcessAttackStateTransition();
		break;
	case enBossState_MagicAttack:
		ProcessMagicAttackStateTransition();
		break;
	case enBossState_ReceiveDamage:
		ProcessReceiveDamageStateTransition();
		break;
	case enBossState_Down:
		ProcessDownStateTransition();
		break;
	}
}

void Boss::PlayAnimation()
{
	m_modelRender.SetAnimationSpeed(1.5f);
	switch (m_BossState)
	{
	case enBossState_Idle:
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.5f);
		break;
		/*case enBossState_Walk:
			m_modelRender.SetAnimationSpeed(1.2f);
			m_modelRender.PlayAnimation(enAnimationClip_Walk, 0.1f);
			break;
		case enBossState_Run:
			m_modelRender.SetAnimationSpeed(1.2f);
			m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
			break;
		*/
	case enBossState_Chase:
		m_modelRender.SetAnimationSpeed(1.6f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
	case enBossState_Attack:
		m_modelRender.SetAnimationSpeed(0.9f);
		m_modelRender.PlayAnimation(enAnimationClip_Attack, 0.1f);
		break;
	case enBossState_MagicAttack:
		m_modelRender.SetAnimationSpeed(1.5f);
		m_modelRender.PlayAnimation(enAnimationClip_MagicAttack, 0.1f);
		break;
	case enBossState_ReceiveDamage:
		m_modelRender.SetAnimationSpeed(1.8f);
		m_modelRender.PlayAnimation(enAnimationClip_Damage, 0.1f);
		break;
	case enBossState_Down:
		m_modelRender.PlayAnimation(enAnimationClip_Down, 0.1f);
		break;
	default:
		break;
	}
}

void Boss::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"attack_start") == 0) {
		m_isUnderAttack = true;
		//�U���G�t�F�N�g�𔭐�������B
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(1);
		effectEmitter->SetScale(Vector3::One * 12.0f);
		Vector3 effectPosition = m_position;
		effectPosition.y += 70.0f;
		//effectPosition += m_forward * 10.0f;
		effectEmitter->SetPosition(effectPosition);
		Quaternion rotation;
		rotation = m_rotation;
		rotation.AddRotationDegY(360.0f);
		//rotation.AddRotationDegZ(180.0f);
		effectEmitter->SetRotation(rotation);
		effectEmitter->Play();
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(3);
		se->Play(false);
		se->SetVolume(0.8f);
	}
	else if (wcscmp(eventName, L"attack_end") == 0) {
		m_isUnderAttack = false;
	}
	else if (wcscmp(eventName, L"magic_attack") == 0) {
		MakeFireBall();
	}
}

const bool Boss::IsCanAttack() const
{
	Vector3 diff = m_player->GetPosition() - m_position;
	//���������Ȃ�߂�������B
	if (diff.LengthSq() <= 100.0f * 100.0f)
	{
		return true;
	}
	return false;
}

void Boss::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}