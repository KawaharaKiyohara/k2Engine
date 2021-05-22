/*!
 *@brief	�}�b�v�`�b�v
 */
#include "k2EnginePreCompile.h"
#include "MapChip.h"
#include "Level.h"


MapChip::MapChip(const LevelObjectData& objData)
{
	//���f����ǂݍ��ށB
	m_modelRender.Init(objData.name);
	//�F�X�Z�b�g�B
	m_modelRender.SetPosition(objData.position);
	m_modelRender.SetScale(objData.scale);
	m_modelRender.SetRotation(objData.rotation);
	//���f�����X�V�B
	m_modelRender.Update();

	//�ÓI�����I�u�W�F�N�g���쐬�B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

void MapChip::Draw(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

