/*!
 *@brief	�}�b�v�`�b�v
 */

#pragma once




struct LevelObjectData;

/*!
*@brief	�}�b�v�`�b�v�B
*/
class MapChip
{
public:
	MapChip(const LevelObjectData& objData);
	~MapChip()
	{
	}
	/*!
	*@brief	���f�������_���[���擾�B
	*/
	ModelRender& GetSkinModelRender()
	{
		return m_modelRender;
	}
private:
	ModelRender			m_modelRender;					//���f�������_�[�B
	PhysicsStaticObject m_physicsStaticObject;			//�ÓI�����I�u�W�F�N�g�B
};
