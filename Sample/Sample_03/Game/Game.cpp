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
	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[enAnimationClip_idle].Load("Assets/animData/idle.tka");
	m_animClips[enAnimationClip_run].Load("Assets/animData/run.tka");
	m_animClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	//���[�v�t���O��ݒ肷��B<-����A�j���[�V�����̓��[�v�t���O��ݒ肵�Ă��Ȃ��̂�
	//�����V���b�g�Đ��Œ�~����B
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);


	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animClips,enAnimationClip_Num,enModelUpAxisY);

	return true;
}

void Game::Update()
{
	//A�{�^���������ꂽ��ҋ@���[�V�������Đ�����B
	if (g_pad[0]->IsTrigger(enButtonA)) {
		//Play�֐��̑������͕⊮���ԁB
		//�ҋ@���[�V�����̐؂�ւ��͕⊮���Ԃ�ݒ肵�Ă��Ȃ��̂ŁA�A�j���[�V�������p�L���ƕς��B
		m_modelRender.PlayAnimation(enAnimationClip_idle);
	}
	//B�{�^���������ꂽ�瑖��A�j���[�V�������Đ�����B
	else if (g_pad[0]->IsTrigger(enButtonB)) {
		m_modelRender.PlayAnimation(enAnimationClip_run, 0.2f);
	}
	//Y�{�^���������ꂽ������A�j���[�V�������Đ�����B
	else if (g_pad[0]->IsTrigger(enButtonY)) {
		m_modelRender.PlayAnimation(enAnimationClip_walk, 0.2f);
	}

	//���f���̍X�V�B
	m_modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
}