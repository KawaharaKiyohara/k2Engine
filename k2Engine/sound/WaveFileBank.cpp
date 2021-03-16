/*!
 *@brief	�g�`�f�[�^�o���N�B
 */

#include "k2EngineLowPreCompile.h"
#include "WaveFile.h"
#include "WaveFileBank.h"


	WaveFileBank::WaveFileBank()
	{
	}
	WaveFileBank::~WaveFileBank()
	{
		ReleaseAll();
	}
	void WaveFileBank::Release(int groupID)
	{
		for (auto waveFile : m_waveFileMap[groupID]) {
			waveFile.second->Release();
		}
		m_waveFileMap[groupID].clear();
	}
	void WaveFileBank::UnregistWaveFile(int groupID, WaveFilePtr waveFile)
	{
		MY_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
		m_waveFileMap->erase(waveFile->GetFilePathHash());
	}
	void WaveFileBank::RegistWaveFile(int groupID, WaveFilePtr waveFile)
	{
		MY_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
		m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
	}
	WaveFilePtr WaveFileBank::FindWaveFile(int groupID, const char* filePath)
	{
		MY_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
		auto value = m_waveFileMap[groupID].find(CUtil::MakeHash(filePath));
		if (value != m_waveFileMap[groupID].end()) {
			return value->second;
		}
		return WaveFilePtr();
	}
	WaveFilePtr WaveFileBank::FindWaveFile(int groupID, const int nameKey)
	{
		MY_ASSERT(groupID < MAX_GROUP, "groupID is invalid");
		auto value = m_waveFileMap[groupID].find(nameKey.GetHashCode());
		if (value != m_waveFileMap[groupID].end()) {
			return value->second;
		}
		return WaveFilePtr();
	}


void WaveFileBank::Resist(int number, const char* filePath)
{
	//����������ĂȂ�������B
	if (!m_waveFilePtrArray[number])
	{
		m_waveFilePtrArray[number].reset(new WaveFilePtr);
		auto waveFile = m_waveFilePtrArray[number];
		waveFile->Open(filePath);
		bool result = waveFile->Open(filePath);
		//�t�@�C���I�[�v���Ɏ��s������B
		if (result == false) {
			//���\�[�X��j������B
			m_waveFilePtrArray[number].reset();
			return;
		}
		waveFile->AllocReadBuffer(waveFile->GetSize());	//wave�t�@�C���̃T�C�Y���̓ǂݍ��݃o�b�t�@���m�ۂ���B
		unsigned int dummy;
		waveFile->Read(waveFile->GetReadBuffer(), waveFile->GetSize(), &dummy);
		waveFile->ResetFile();
	}
}
