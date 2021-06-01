#pragma once

/*!
	 * @brief	�S�[�X�g�I�u�W�F�N�g
	 *@detail
	 * �S�[�X�g�I�u�W�F�N�g�͍��̂����蔲���邠���蔻��̃I�u�W�F�N�g�ł��B
	 * �L�����N�^�[�̃`�F�b�N�|�C���g�ʉߔ���A�N���A����Ȃǂ�
	 * �L�����N�^�[�����蔲����K�v�̂��邠���蔻��Ɏg���܂��B
	 */
class PhysicsGhostObject{
public:
	~PhysicsGhostObject()
	{
		Release();
	}
	/*!
	* @brief	�S�[�X�g�I�u�W�F�N�g������B
	*@detail
	* �����I�ȃ^�C�~���O�ŃS�[�X�g�I�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
	*/
	void Release()
	{
		if (m_isRegistPhysicsWorld == true) {
			PhysicsWorld::GetInstance()->RemoveCollisionObject(m_ghostObject);
			m_isRegistPhysicsWorld = false;
		}
	}
	/*!
	* @brief	�{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	*@param[in]	pos			���W�B
	*@param[in]	rot			��]�B
	*@param[in]	size		�T�C�Y�B
	*/
	void CreateBox(Vector3 pos, Quaternion rot, Vector3 size);
	/*!
	* @brief	�J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	*@param[in]	pos			���W�B
	*@param[in]	rot			��]�B
	*@param[in]	radius		�J�v�Z���̔��a�B
	*@param[in]	height		�J�v�Z���̍����B
	*/
	void CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height);
	/*!
	* @brief	���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	*@param[in]	pos			���W�B
	*@param[in]	rot			��]�B
	*@param[in]	radius		���̂̔��a�B
	*/
	void CreateSphere(Vector3 pos, Quaternion rot, float radius);
	/*!
	* @brief	���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	*@param[in]	pos					���W�B
	*@param[in]	rot					��]�B
	*@param[in]	skinModelData		�X�L�����f���f�[�^�B
	*/
	void CreateMesh(Vector3 pos,Quaternion rot, const Model& model, const Matrix& worldMatrix);
	/*!
	* @brief	�����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g���ǂ�������B
	*/
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	/*!
	* @brief	���W��ݒ�B
	*/
	void SetPosition(const Vector3& pos)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		btPos = btVector3(pos.x, pos.y, pos.z);
		btTrans.setOrigin(btPos);
	}
	/*!
	* @brief	��]��ݒ�B
	*/
	void SetRotation(const Quaternion& rot)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btQuaternion btRot;
		btRot = btQuaternion(rot.x, rot.y, rot.z, rot.w);
		btTrans.setRotation(btRot);
	}
private:
	/*!
	* @brief	�S�[�X�g�쐬�����̋��ʏ����B
	*/
	void CreateCommon(Vector3 pos, Quaternion rot);
private:
	bool							m_isRegistPhysicsWorld = false;	//�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	btGhostObject					m_ghostObject;					//�S�[�X�g
	std::unique_ptr<ICollider>		m_collider;						//�R���C�_�[�B
};

