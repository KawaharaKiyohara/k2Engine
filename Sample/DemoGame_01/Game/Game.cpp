#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "GameCamera.h"
#include "Background.h"
#include "Enemy.h"
#include "Lever.h"
#include "Door.h"

#include "nature/SkyCube.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_gameCamera);
	DeleteGO(m_skyCube);
	DeleteGO(m_player);
	DeleteGO(m_background);
	DeleteGO(m_enemy);
	for (auto lever : m_leverVector)
	{
		DeleteGO(lever);
	}
	for (auto door : m_doorVector)
	{
		DeleteGO(door);
	}
	DeleteGO(m_bgm);
}

bool Game::Start()
{
	g_camera3D->SetPosition({ 0.0f, 100.0f, -600.0f });
	g_camera3D->SetFar(40000.0f);

	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	m_skyCube = NewGO<SkyCube>(0, "skycube");


	//���x�����\�z����B
	m_levelRender.Init("Assets/level3D/level.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"human") == true) {
			//�v���C���[�B
			//�v���C���[�̃C���X�^���X�𐶐�����B
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			m_player->SetRotation(objData.rotation);
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ȃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"enemy") == true) {
			//�G�l�~�[�B
			//�G�l�~�[�̃C���X�^���X�𐶐�����B
			m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objData.position);
			m_enemy->SetRotation(objData.rotation);
			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ȃ��B
			return true;
		}
		else if (objData.EqualObjectName(L"background") == true) {
			m_background = NewGO<Background>(0, "background");
			m_background->SetPosition(objData.position);
			m_background->SetScale(objData.scale);
			m_background->SetRotation(objData.rotation);
			return true;
		}
		else if (objData.ForwardMatchName(L"lever") == true) {
			auto lever = NewGO<Lever>(0, "lever");

			lever->SetPosition(objData.position);
			lever->SetScale(objData.scale);
			lever->SetRotation(objData.rotation);
			lever->SetLeverNumber(objData.number);
			m_leverVector.push_back(lever);
			return true;
		}
		else if (objData.ForwardMatchName(L"door") == true) {
			auto door = NewGO<Door>(0, "door");

			door->SetPosition(objData.position);
			door->SetScale(objData.scale);
			door->SetRotation(objData.rotation);
			door->SetDoorNumber(objData.number);
			m_doorVector.push_back(door);
			return true;
		}
		return true;
		});

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/game.wav");
	m_bgm = NewGO<SoundSource>(0);
	m_bgm->Init(2);
	m_bgm->Play(true);
	m_bgm->SetVolume(0.2f);
	return true;
}

void Game::NotifyGameOver()
{

}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
}