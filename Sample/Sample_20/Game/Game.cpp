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
	if (m_rotateMode == 0) {
		//�p�x�����Z����B
		m_rotation.AddRotationDegY(1.0f);
		//���������N�H�[�^�j�I�������f�������_���[�ɓ`����B
		m_modelRender.SetRotation(m_rotation);
	}
	else if (m_rotateMode == 1) {
		//�X�e�B�b�N�ŉ�]�����郂�[�h�B
		//��]�����Z����B
		m_rotation.AddRotationDegY(g_pad[0]->GetLStickXF());
		m_rotation.AddRotationDegX(g_pad[0]->GetLStickYF());
		//���������N�H�[�^�j�I�������f�������_���[�ɓ`����B
		m_modelRender.SetRotation(m_rotation);
	}
	if (g_pad[0]->IsTrigger(enButtonA) == true) {
		//A�{�^������������A��]���[�h��ύX����B
		if (m_rotateMode == 0) {
			m_rotateMode = 1;
		}
		else if (m_rotateMode == 1) {
			m_rotateMode = 0;
		}
	}
	//���f���̍X�V�B
	m_modelRender.Update();
}


void Game::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
}