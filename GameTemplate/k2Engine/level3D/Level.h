/*!
 *@brief	���x���B
 */

#pragma once


class MapChip;
/*!
* @brief	�I�u�W�F�N�g���B
*/
struct LevelObjectData {
	Vector3 position;		//<���W�B
	Quaternion rotation;	//!<��]�B
	Vector3 scale;			//!<�g�嗦�B
	char* name;	//!<���O�B
	/*!
	* @brief	�����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�B
	*@param[in]	objName		���ׂ閼�O�B
	*@return	���O�������ꍇ��true��Ԃ��܂��B
	*/
	bool EqualObjectName(const char* objName)
	{
		return strcmp(objName, name) == 0;
	}
	/*!
	* @brief	���O���O����v���邩���ׂ�B
	*/
	bool ForwardMatchName(const char* n)
	{
		auto len = strlen(n);
		auto namelen = strlen(name);
		if (len > namelen) {
			//���O�������B�s��v�B
			return false;
		}
		return strncmp(n, name, len) == 0;
	}
};
	/*!
	 *@brief	���x���B
	 */
class Level {
private:
	using MapChipPtr = std::shared_ptr<MapChip>;
public:
	~Level();
	/*!
	 * @brief	���x�����������B
	 *@param[in]	levelDataFilePath		tkl�t�@�C���̃t�@�C���p�X�B
	 *@param[in] hookFunc				�I�u�W�F�N�g���쐬���鎞�̏������t�b�N���邽�߂̊֐��I�u�W�F�N�g�B
	 *   �t�b�N���Ȃ��Ȃ�nullptr���w�肷��΂悢�A
	 * ���̊֐��I�u�W�F�N�g��false��Ԃ��ƁA�I�u�W�F�N�g�̏�񂩂�A
	 * �ÓI�I�u�W�F�N�g��MapChip�N���X�̃C���X�^���X����������܂��B
	 * �I�u�W�F�N�g�̖��O�ȂǂŁA�h�A��W�����v��A�A�C�e���Ȃǂ̓���ȃN���X�̃C���X�^���X�𐶐������Ƃ��ɁA
	 * �f�t�H���g�ō쐬�����MapChip�N���X�̃C���X�^���X���s�v�ȏꍇ��true��Ԃ��Ă��������B
	 * �Ⴆ�΁A�t�b�N�֐��̒��ŁA�n���ꂽ�I�u�W�F�N�g�f�[�^�̖��O�̃��f����`�悷��N���X�̃C���X�^���X��
	 * ���������Ƃ��ɁAfalse��Ԃ��Ă��܂��ƁA�������f������`�悳��邱�ƂɂȂ�܂��B
	 */
	void Init(const char* filePath, std::function<bool(LevelObjectData& objData)> hookFunc);
	/// <summary>
	/// ���f����`��B
	/// </summary>
	/// <param name="rc">�����_�[�R���e�L�X�g�B</param>
	void Draw(RenderContext& rc);
private:
	/// <summary>
	/// �}�b�v�`�b�v���쐬�B
	/// </summary>
	/// <param name="objData">LevelObjectData�B</param>
	void CreateMapChip(const LevelObjectData& objData);
private:
	std::vector<MapChipPtr> m_mapChipPtrs;			//�}�b�v�`�b�v�̉ϒ��z��B

};
