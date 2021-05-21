/*!
 *@brief	�}�b�v�`�b�v
 */
#include "k2EnginePreCompile.h"
#include "MapChip.h"
#include "Level.h"


	MapChip::MapChip(const LevelObjectData& objData, MapChipRender* mapChipRender)
	{
		char objName[256];
		wcstombs(objName, objData.name, 256);
		
		//�t�@�C���p�X���쐬�B
		wchar_t filePath[256];
		swprintf_s(filePath, L"modelData/%s.cmo", objData.name);
		m_mapChipRender = mapChipRender;
		m_physicsStaticObject.CreateMesh( 
			objData.position, 
			objData.rotation,
			objData.scale,
			mapChipRender->GetSkinModelRender()
		);
	}
MapChip::MapChip(const LevelObjectData& objData)
{
	m_modelRender.Init(objData.name);
}

