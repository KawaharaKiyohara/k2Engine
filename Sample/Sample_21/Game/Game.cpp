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
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm");

	//レベルを構築する。
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
	//モデルの更新。
	m_modelRender.Update();

	//レベル2Dの画像の更新。
	m_level2DRender.Update();
}

void Game::Render(RenderContext& rc)
{
	//モデルの描画。
	m_modelRender.Draw(rc);

	//レベル2Dの画像の描画処理。
	m_level2DRender.Draw(rc);
}