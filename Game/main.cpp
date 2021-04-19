#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "graphics/RenderingEngine.h"
#include "BackGround.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();
	g_soundEngine = new SoundEngine();
	//�����_�����O�G���W����������
	g_renderingEngine = new RenderingEngine();
	g_renderingEngine->Init();

	NewGO<Player>(0,"player");
	Player* player = NewGO<Player>(0, "player");
	player->m_position = { 100.0f,00.0f,600.0f };
	player->m_scale = { 4.0f,4.0f,4.0f };
	NewGO<BackGround>(0, "BackGround");
	//NewGO<Player>(0,"player");
	//NewGO<Player>(0,"player");
	//NewGO<Player>(0,"player");
	//NewGO<Player>(0,"player");

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		//sprite[1].Update(pos[1], Quaternion::Identity, Vector3::One);
		GameObjectManager::GetInstance()->ExecuteUpdate();
		

		//�����_�����O�G���W�������s
		g_renderingEngine->Execute(renderContext);
		PhysicsWorld::GetInstance()->DebubDrawWorld(renderContext);
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_soundEngine->Update();
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

