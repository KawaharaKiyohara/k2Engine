#include "stdafx.h"
#include "BackGround.h"

Background::Background()
{

}

Background::~Background()
{

}

bool Background::Start()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");
	//�傫���ύX�B
	m_modelRender.SetScale({ 0.7f, 0.7f, 0.7f });
	//�傫���̕ύX�𔽉f�����邽�߂ɁA���f�����X�V�B
	m_modelRender.Update();

	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//�����蔻��`���L���B
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void Background::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}