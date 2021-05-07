#include "stdafx.h"
#include "system/system.h"

#include<InitGUID.h>
#include<dxgidebug.h>


#include "Player.h"
#include "sound/SoundEngine.h"
#include "graphics/RenderingEngine.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "effect/effect.h"

void ReportLiveObjects()
{
	IDXGIDebug* pDxgiDebug;

	typedef HRESULT(__stdcall* fPtr)(const IID&, void**);
	HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
	fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");

	DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDxgiDebug);

	// �o�́B
	pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_DETAIL);
}

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

	//�e��G���W���Ȃǂ̏������B
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();
	g_soundEngine = new SoundEngine();
	//�����_�����O�G���W����������
	g_renderingEngine = new RenderingEngine();
	g_renderingEngine->Init();
	//�G�t�F�N�g�G���W���̏������B
	EffectEngine::CreateInstance();

	auto* player = NewGO<Player>(0, "player");
	//player->m_position = { 100.0f,00.0f,600.0f };
	//player->m_scale = { 4.0f,4.0f,4.0f };
	auto backGround = NewGO<BackGround>(0, "backGround");
	auto gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//NewGO<Player>(0,"player");
	//NewGO<Player>(0,"player");
	//NewGO<Player>(0,"player");
	//NewGO<Player>(0,"player");


	//step-2 ���[�U�[�G�t�F�N�g�̏������B
	Effect laserEffect;
	laserEffect.Init(u"Assets/effect/laser.efk");
	laserEffect.SetPosition({ 0.0f,100.0f,0.0f });

	//�X�v���C�g�͌���\���ł��Ȃ��B
	//�C���\��B
	//SpriteRender spriteRender;
	//spriteRender.Init("Assets/sprite/gameclear.dds", 500.0f, 500.0f);
	//Quaternion rotation;

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
		
		GameObjectManager::GetInstance()->ExecuteUpdate();



		if (g_pad[0]->IsTrigger(enButtonA)) {
			//�Đ��J�n�B
			laserEffect.Play();
		}
		auto pos = laserEffect.GetPosition();
		pos.x += g_pad[0]->GetLStickXF();
		pos.z += g_pad[0]->GetLStickYF();

		auto rot = laserEffect.GetRotation();
		rot.AddRotationY(g_pad[0]->GetRStickXF() * 0.1f);

		laserEffect.SetPosition(pos);
		laserEffect.SetRotation(rot);
		laserEffect.SetScale({ 10.0f,10.0f,10.0f });
		laserEffect.Update();
		//�G�t�F�N�g�G���W���̍X�V�B
		EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		
		




		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		//�G�t�F�N�g�̃h���[�B
		//�����_�����O�G���W���Ńh���[���Ă��܂��B
		//EffectEngine::GetInstance()->Draw();
		//�����_�����O�G���W�������s
		g_renderingEngine->Execute(renderContext);
	
		PhysicsWorld::GetInstance()->DebubDrawWorld(renderContext);
	
	
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_soundEngine->Update();
		g_engine->EndFrame();
	
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();

	PhysicsWorld::DeleteInstance();
	delete g_soundEngine;
	EffectEngine::DeleteInstance();
	delete g_renderingEngine;

#ifdef _DEBUG
	ReportLiveObjects();
#endif // _DEBUG
	return 0;
}

