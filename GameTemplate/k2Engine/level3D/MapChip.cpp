/*!
 *@brief	マップチップ
 */
#include "k2EnginePreCompile.h"
#include "MapChip.h"
#include "Level.h"


MapChip::MapChip(const LevelObjectData& objData)
{
	//モデルを読み込む。
	m_modelRender.Init(objData.name);
	//色々セット。
	m_modelRender.SetPosition(objData.position);
	m_modelRender.SetScale(objData.scale);
	m_modelRender.SetRotation(objData.rotation);
	//モデルを更新。
	m_modelRender.Update();

	//静的物理オブジェクトを作成。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

void MapChip::Draw(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

