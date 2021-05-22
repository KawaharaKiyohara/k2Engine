/*!
 *@brief	���x���B
 */

#include "k2EnginePreCompile.h"
#include "Level.h"
#include "MapChip.h"


Level::~Level()
{
		
}
void Level::CreateMapChip(const LevelObjectData& objData)
{
	//�t�b�N����Ȃ������̂ŁA�}�b�v�`�b�v���쐬����B
	auto mapChip = std::make_shared<MapChip>(objData);
	m_mapChipPtrs.push_back(mapChip);
}
void Level::Init(
	const char* filePath,
	std::function<bool(LevelObjectData& objData)> hookFunc
)
{
	//�X�P���g�������[�h����B
	Skeleton skeleton;
	skeleton.Init(filePath);

	//�\�z�\�z�B
	//0�Ԗڂ̓��[�g�I�u�W�F�N�g�Ȃ̂Ŕ�΂��B
	for (auto i = 1; i < skeleton.GetNumBones(); i++) {
		//�����擾�B
		auto bone = skeleton.GetBone(i);
		if (bone->GetParentBoneNo() == 0) {	//�e�����[�g�̏ꍇ�����}�b�v�`�b�v�𐶐�����B
			LevelObjectData objData;
			Vector3 scale;
			bone->CalcWorldTRS(objData.position, objData.rotation, objData.scale);
			//3dsMax�Ƃ͎����Ⴄ�̂ŁA�␳������B
			auto t = objData.position.y;
			objData.position.y = objData.position.z;
			objData.position.z = -t;

			t = objData.rotation.y;
			objData.rotation.y = objData.rotation.z;
			objData.rotation.z = -t;

			const wchar_t* wname = bone->GetName();
			//�p�X�̍쐬
			wchar_t filePath[256];
			swprintf_s(filePath, L"Assets/modelData/%s.tkm", wname);
			//�}���`�o�C�g�ɕϊ� wchar�� char
			//�x�[�X�̕�����B
			size_t origsize = wcslen(filePath) + 1;
			//�ϊ�����������
			size_t convertedChars = 0;
			//�}���`�o�C�g�i�[�p
			char strCon[] = "";
			//�T�C�Y
			size_t strConSize = (strlen(strCon) + 1) * 2;
			//�ϊ���̃T�C�Y�B
			const size_t newsize = origsize * 2;
			//�A����̃T�C�Y
			objData.name = new char[newsize + strConSize];
			//�}���`�o�C�g�ɕϊ�����B���肫��Ȃ����̂͐؂肷��
			wcstombs_s(&convertedChars, objData.name, newsize, filePath, _TRUNCATE);
			//������̘A��
			_mbscat_s((unsigned char*)objData.name, newsize + strConSize, (unsigned char*)strCon);


			std::swap(objData.scale.y, objData.scale.z);

			auto isHook = false;
			if (hookFunc != nullptr) {
				//hook�֐����w�肳��Ă���̂�hook�֐����Ăяo���B
				isHook = hookFunc(objData);
			}
			if (isHook == false) {
				//�}�b�v�`�b�v���쐬����B
				CreateMapChip(objData);
			}
		}
	}
}

void Level::Draw(RenderContext& rc)
{
	for (auto mapChipPtr : m_mapChipPtrs)
	{

	}
}