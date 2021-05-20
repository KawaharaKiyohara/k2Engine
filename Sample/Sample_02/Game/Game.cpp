#include "stdafx.h"
#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/unityChan.tkm");

	return true;
}

void Game::Update()
{
	float degree = 0.0f;
	//�㉺���E�̃L�[���͂ɂ���]�����B
	if (g_pad[0]->IsPress(enButtonRight)) {
		//Y�������2�x�񂷁B
		degree = 2.0f;
	}
	else if (g_pad[0]->IsPress(enButtonLeft)) {
		//Y�������-2�x�񂷁B
		degree = -2.0f;
	}
	else if (g_pad[0]->IsPress(enButtonUp)) {
		degree = 2.0f;
	}
	else if (g_pad[0]->IsPress(enButtonDown)) {
		degree = -2.0f;
	}
	//�p�x�����Z����B
	m_rotation.AddRotationDegY(degree);

	//�A�i���O�X�e�B�b�N�ɂ���]�����B
	Vector3 stick;
	stick.x = -g_pad[0]->GetLStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stick.y = g_pad[0]->GetLStickYF();		//�A�i���O�X�e�B�b�N��y�̓��͗ʂ��擾�B
	stick.z = 0.0f;
	//��]�����Z����B
	m_rotation.AddRotationDegY(stick.x * 2.0f);

	//��]�����Z����B
	m_rotation.AddRotationDegY(stick.y * 2.0f);

	//�N�H�[�^�j�I����ݒ肷��B
	m_modelRender.SetRotation(m_rotation);

	//���f���̍X�V�B
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
}