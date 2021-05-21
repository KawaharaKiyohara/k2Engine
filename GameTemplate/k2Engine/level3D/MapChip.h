/*!
 *@brief	マップチップ
 */

#pragma once




struct LevelObjectData;

/*!
*@brief	マップチップ。
*/
class MapChip
{
public:
	MapChip(const LevelObjectData& objData);
	~MapChip()
	{
	}
	/*!
	*@brief	モデルレンダラーを取得。
	*/
	ModelRender& GetSkinModelRender()
	{
		return m_modelRender;
	}
private:
	ModelRender			m_modelRender;					//モデルレンダー。
	PhysicsStaticObject m_physicsStaticObject;			//静的物理オブジェクト。
};
