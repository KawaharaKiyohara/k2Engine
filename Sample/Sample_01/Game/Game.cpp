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
	//�A�i���O�X�e�B�b�N�ɂ��ړ������B
	//GetLStickXF�́A�Q�[���p�b�h�̉������̓|����-1.0�`1.0��Ԃ��Ă��܂��B
	//GetLStickYF�́A�Q�[���p�b�h�̏c�����̓|����-1.0�`1.0��Ԃ��Ă��܂��B
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.z += g_pad[0]->GetLStickYF();

	//���W��ݒ�B
	m_modelRender.SetPosition(m_position);

	//���f���̍X�V�B
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
}