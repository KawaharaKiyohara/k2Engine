#include "stdafx.h"
#include "Game.h"

#include "nature/SkyCube.h"

#include "Player.h"
#include "Background.h"
#include "GameCamera.h"
#include "Star.h"

Game::Game()
{
	//�폜�B
	DeleteGO(m_player);
	DeleteGO(m_background);
	DeleteGO(m_gameCamera);
}

Game::~Game()
{

}

bool Game::Start()
{
	g_camera3D->SetPosition({ 0.0f, 100.0f, -600.0f });
	
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//m_skyCube = NewGO<SkyCube>(0, "skycube");

	//���x�����\�z����B
	m_levelRender.Init("Assets/level3D/stage.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"unityChan") == true) {
			//Unity�����B
			//�v���C���[�̃C���X�^���X�𐶐�����B
			m_player = NewGO<Player>(0, "player");
			m_player->m_position = objData.position;
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ȃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"background") == true) {
			m_background = NewGO<Background>(0, "background");
			m_background->m_position = objData.position;
			m_background->m_scale = objData.scale;
			m_background->m_rotation = objData.rotation;
			return true;
		}
		else if (objData.EqualObjectName(L"star") == true) {
			//auto star = NewGO<Star>(0, "star");
			//star->m_postiion = objData.position;
			return true;
		}
		return false;
	});

	return true;
}
