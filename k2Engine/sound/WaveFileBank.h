/*!
 *@brief	�g�`�f�[�^�o���N�B
 */
#pragma once

#include <map>
#include <array>

const int MAXWAVEFILENUMBER = 1000;

	class WaveFile;
	typedef std::shared_ptr<WaveFile>	WaveFilePtr;
	typedef std::map<unsigned int , WaveFilePtr>	WaveFilePtrMap;
	/*!
	 *@brief	�g�`�f�[�^�o���N�B
	 *@details
	 * ��x���[�h���ꂽ�g�`�f�[�^���o���N�ɓo�^���邱�Ƃ��o���܂��B
	 * �o�^���ꂽ�g�`�f�[�^�͍ēǂݍ��݂��s���K�v���Ȃ��A�o���N����ė��p���邱�Ƃ��o���܂��B
	 */
	class WaveFileBank{
	public:
		WaveFileBank();
		~WaveFileBank();
		/*!
		 *@brief	�g�`�f�[�^��o�^�B
		 *@param[in]	groupID		�O���[�v�h�c�B�w��ł���h�c�̍ő�l��MAX_GROUP-1�B
		 *@param[in]	waveFile	�g�`�f�[�^�B
		 */
		//Svoid RegistWaveFile(int groupID, WaveFilePtr waveFile);
		/*!
		*@brief	�����Ŏw�肵���t�@�C���p�X�̔g�`�f�[�^���o���N�ɓo�^����Ă��邩��������B
		*@param[in]	groupID		�O���[�v�h�c�B�w��ł���h�c�̍ő�l��MAX_GROUP-1�B
		*@param[in]	filePath	�t�@�C���p�X�B
		*@return �g�`�f�[�^�B�o�^����Ă��Ȃ��ꍇ��NULL���Ԃ�B
		*/
		//WaveFilePtr FindWaveFile(int groupID, const char* filePath);
		/*!
		*@brief	�����Ŏw�肵���t�@�C���p�X�̔g�`�f�[�^���o���N�ɓo�^����Ă��邩��������B
		*@details 
		*  �������̂ق����������������B
		*@param[in]	groupID		�O���[�v�h�c�B�w��ł���h�c�̍ő�l��MAX_GROUP-1�B
		*@param[in]	nameyKey	���O�L�[�B�B
		*@return �g�`�f�[�^�B�o�^����Ă��Ȃ��ꍇ��NULL���Ԃ�B
		*/
		//WaveFilePtr FindWaveFile(int groupID, const int nameKey);
		/*!
		*@brief	�g�`�f�[�^���o���N����o�^�����B
		*@param[in]	groupID		�O���[�v�h�c�B�w��ł���h�c�̍ő�l��MAX_GROUP-1�B
		*@param[in]	waveFile	�g�`�f�[�^�B
		*/
		//void UnregistWaveFile(int groupID, WaveFilePtr waveFile);
		/*!
		*@brief	�O���[�v�P�ʂŉ���B
		*/
		//void Release(int groupID);
		/*!
		*@brief	�S�ĉ���B
		*/
		/*void ReleaseAll()
		{
			for (int i = 0; i < MAX_GROUP; i++) {
				Release(i);
			}
		}*/
		//TODO ��Ŏ�������B
		void Release()
		{

		}
		//Wave�t�@�C������������B
		WaveFilePtr FindWaveFile(int number)
		{
			return m_waveFilePtrArray[number];
		}
		//Wave�t�@�C����o�^����B
		void Resist(int number, const char* filePath);
	private:
		static const int MAX_GROUP = 256;
		//WaveFilePtrMap	m_waveFileMap[MAX_GROUP];		//!<wave�t�@�C���̃��X�g�B
		std::array<WaveFilePtr, MAXWAVEFILENUMBER> m_waveFilePtrArray;
	};