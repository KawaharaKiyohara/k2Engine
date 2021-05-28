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

	//���x�����\�z����B
	m_level2DRender.Init("Assets/level2D/sample.casl", [&](Level2DObjectData& objData) {
		if (objData.EqualObjectName("k2SLEditor_red") == true) {

			return false;
		}
		else if (objData.EqualObjectName("k2SLEditor_blue") == true) {

			m_spriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			return true;
		}
		return false;
		});

	return true;
}

void Game::Update()
{
	//���f���̍X�V�B
	m_modelRender.Update();

	//���x��2D�̉摜�̍X�V�B
	m_level2DRender.Update();
}

void Game::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);

	//���x��2D�̉摜�̕`�揈���B
	m_level2DRender.Draw(rc);
}