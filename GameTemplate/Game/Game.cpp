#include "stdafx.h"
#include "Game.h"
#include "Player.h"

bool Game::Start()
{

	//���x�����\�z����B
	m_levelRender.Init("Assets/level/sample.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"unityChan") == true) {

			return true;
		}
		else if (objData.EqualObjectName(L"player") == true) {
			//Unity�����B
			//�v���C���[�̃C���X�^���X�𐶐�����B
			m_player = NewGO<Player>(0, "player");
			m_player->position = objData.position;
			//�t�b�N�����ꍇ��true��Ԃ��B
			return true;
		}
		return false;
		});
	return true;
}

void Game::Render(RenderContext& rc)
{
	m_levelRender.Draw(rc);
}