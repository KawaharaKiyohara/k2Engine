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
	m_spriteRender.Init("Assets/sprite/suzuka.dds", 970, 380);
	m_spriteRender.SetScale(Vector3(0.9474f, 0.7432f, 0.0f));
	return true;
}

void Game::Update()
{
	//�摜�̍X�V�B
	m_spriteRender.Update();
}

void Game::Render(RenderContext& rc)
{
	//�摜�̕`��B
	m_spriteRender.Draw(rc);
}