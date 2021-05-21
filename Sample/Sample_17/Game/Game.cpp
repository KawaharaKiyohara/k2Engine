#include "stdafx.h"
#include "Game.h"

//EffectEmitter���g�p���鎞�̓t�@�C�����C���N���[�h����K�v������B
#include "effect/EffectEmitter.h"

Game::Game()
{

}

Game::~Game()
{
	
}

bool Game::Start()
{
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/laser.efk");
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/laser2.efk");

	return true;
}

void Game::Update()
{
	//A�{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(0);
		effectEmitter->SetScale({ 5.0f,5.0f,5.0f });
		effectEmitter->Play();
	}

	//B�{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(1);
		effectEmitter->SetScale({ 5.0f,5.0f,5.0f });
		effectEmitter->Play();
	}

}