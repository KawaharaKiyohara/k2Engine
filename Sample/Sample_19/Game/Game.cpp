#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "Background.h"
#include "GameCamera.h"
#include "Box.h"

Game::Game()
{
	//�폜�B
	DeleteGO(m_player);
	DeleteGO(m_background);
	DeleteGO(m_gameCamera);
	DeleteGO(m_box);
}

Game::~Game()
{

}

bool Game::Start()
{
	g_camera3D->SetPosition({ 0.0f, 100.0f, -600.0f });

	m_player = NewGO<Player>(0, "player");
	m_background = NewGO<Background>(0, "background");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_box = NewGO<Box>(0, "box");

	//�����蔻��L�����B
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_fontRender.SetText(L"�ՓˁI�I");
	m_fontRender.SetScale(2.0f);
	m_fontRender.SetPosition(Vector3(100.0f, 100.0f, 0.0f));
	return true;
}

void Game::Update()
{
	m_isHit = false;
	//�L�����N�^�R���g���[���[�ƃS�[�X�g�I�u�W�F�N�g�̂����蔻����s���B
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_box->m_physicsGhostObject.IsSelf(contactObject) == true) {
			//m_physicsGhostObject�ƂԂ������B
			//�t���O��true�ɂ���B
			m_isHit = true;
		}
	});
}

void Game::Render(RenderContext& rc)
{
	//�L�����N�^�[�R���g���[���[�ƃS�[�X�g�I�u�W�F�N�g���Փ˂��Ă��Ȃ�������B
	if (m_isHit == false)
	{
		//�������Ȃ��B
		return;
	}

	//�����\���B
	m_fontRender.Draw(rc);
}