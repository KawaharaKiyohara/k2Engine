#pragma once
#include "physics/PhysicsGhostObject.h"

/// <summary>
/// ���̃R���W�����Ɠ����蔻����s���N���X�B
/// </summary>
class CollisionObject : public IGameObject
{
public:
	CollisionObject();
	~CollisionObject();
	bool Start();
	void Update();
	/// <summary>
/// �{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
/// </summary>
/// <param name="pos">���W�B</param>
/// <param name="rot">��]�B</param>
/// <param name="size">�T�C�Y�B</param>
	void CreateBox(Vector3 pos, Quaternion rot, Vector3 size)
	{
		m_physicsGhostObject.CreateBox(pos, rot, size);
	}
	/// <summary>
	/// �J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	/// <param name="rot">��]�B</param>
	/// <param name="radius">�J�v�Z���̔��a�B</param>
	/// <param name="height">�J�v�Z���̍����B</param>
	void CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height)
	{
		m_physicsGhostObject.CreateCapsule(pos, rot, radius, height);
	}
	/// <summary>
	/// ���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	/// <param name="rot">��]�B</param>
	/// <param name="radius">���`�̔��a�B</param>
	void CreateSphere(Vector3 pos, Quaternion rot, float radius)
	{
		m_physicsGhostObject.CreateSphere(pos, rot, radius);
	}
	/// <summary>
	/// ���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
	/// </summary>
	/// <param name="pos">���W�B</param>
	/// <param name="rot">��]�B</param>
	/// <param name="model">���f���B</param>
	/// <param name="worldMatrix">���[���h�s��B</param>
	void CreateMesh(Vector3 pos, Quaternion rot, const Model& model, const Matrix& worldMatrix)
	{
		m_physicsGhostObject.CreateMesh(pos, rot, model, worldMatrix);
	}
	/// <summary>
	/// �ݒ肵������(�b)���o�߂���Ǝ����ō폜����܂��B0.0f��ݒ肵����1�t���[���o�߂ō폜����܂��B
	/// </summary>
	/// <param name="timeLimit">�폜����������(�b)�B</param>
	void SetTimeLimit(const float timeLimit)
	{
		m_timeLimit = timeLimit;
	}
	/// <summary>
	/// ���O��ݒ�B
	/// </summary>
	/// <param name="name">���O�B</param>
	void SetName(const char* name)
	{
		m_name = name;
	}
	/// <summary>
	/// ���O���擾�B
	/// </summary>
	/// <returns></returns>
	const char* GetName() const
	{
		return m_name;
	}
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
		m_physicsGhostObject.SetPosition(m_position);
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �����ō폜���邩�ǂ�����ݒ肷��B
	/// </summary>
	/// <param name="isFlag">true�Ȃ玩���ō폜�����Bfalse�Ȃ玩���ō폜����Ȃ��̂ŁADeleteGO������K�v������B</param>
	void SetIsEnableAutoDelete(bool isFlag)
	{
		m_isEnableAutoDelete = isFlag;
	}
	/// <summary>
	/// �R���W�����I�u�W�F�N�g���m�̓����蔻��B
	/// </summary>
	/// <param name="collisionObject">�Փ˔��肵�����R���W�����I�u�W�F�N�g�B</param>
	/// <returns>�Փ˂�����true�B</returns>
	bool GetIsCollision(CollisionObject& collisionObject) 
	{
		bool isCollision = false;
		PhysicsWorld::GetInstance()->ContactTest(&collisionObject.GetbtCollisionObject(), [&](const btCollisionObject& contactObject) {
			if (m_physicsGhostObject.IsSelf(contactObject) == true) {
				isCollision = true;
			}
		});
		return isCollision;
	}
	/// <summary>
	/// �R���W�����I�u�W�F�N�g�ƃL�����R���̓����蔻��B
	/// </summary>
	/// <param name="collisionObject">�Փ˔��肵�����L�����R���B</param>
	/// <returns>�Փ˂�����true�B</returns>
	bool GetIsCollision(CharacterController& characterController)
	{
		bool isCollision = false;
		PhysicsWorld::GetInstance()->ContactTest(characterController, [&](const btCollisionObject& contactObject) {
			if (m_physicsGhostObject.IsSelf(contactObject) == true) {
				isCollision = true;
			}
		});
		return isCollision;
	}
	PhysicsGhostObject& GetGhostObject()
	{
		return m_physicsGhostObject;
	}
	btCollisionObject& GetbtCollisionObject()
	{
		return m_physicsGhostObject.GetbtCollisionObject();
	}
private:
	Vector3					m_position;
	PhysicsGhostObject		m_physicsGhostObject;
	const char*				m_name = nullptr;
	float					m_timer = 0.0f;
	float					m_timeLimit = 0.0f;
	bool					m_isEnableAutoDelete = true;
};

class CollisionObjectManager
{
public:
	CollisionObjectManager();
	~CollisionObjectManager();
	void AddCollisionObject(CollisionObject* collisionObject)
	{
		m_collisionObjectVector.push_back(collisionObject);
	}
	/// <summary>
	/// ���O�����S��v����R���W�����I�u�W�F�N�g����������B�������1�����B
	/// </summary>
	/// <param name="name">���O�B</param>
	/// <returns>�R���W�����I�u�W�F�N�g�B������Ȃ������ꍇ��nullptr�B</returns>
	CollisionObject* FindCollisionObject(const char* name)
	{
		for (auto collisionObject : m_collisionObjectVector)
		{
			//���O��v�I
			if (strcmp(collisionObject->GetName(), name) == 0)
			{
				return collisionObject;
			}
		}
		return nullptr;
	}

	/// <summary>
	/// ���O���O����v����R���W�����I�u�W�F�N�g����������B�������1�����B
	/// </summary>
	/// <param name="name">���O�B</param>
	/// <returns>�R���W�����I�u�W�F�N�g�B������Ȃ������ꍇ��nullptr�B</returns>
	CollisionObject* FindMatchForwardNameCollisionObject(const char* name)
	{
		for (auto collisionObject : m_collisionObjectVector)
		{
			auto len = strlen(name);
			auto namelen = strlen(collisionObject->GetName());
			if (len > namelen) {
				//���O�������B�s��v�B
				continue;
			}
			if (strncmp(name, collisionObject->GetName(), len) == 0)
			{
				return collisionObject;
			}
		}
		return nullptr;
	}

	/// <summary>
	/// ���O�����S��v����R���W�����I�u�W�F�N�g����������B������͕����B
	/// </summary>
	/// <param name="name">���O�B</param>
	/// <returns>�R���W�����I�u�W�F�N�g�̔z��B</returns>
	std::vector<CollisionObject*>& FindCollisionObjects(const char* name)
	{
		static std::vector<CollisionObject*> collisionObjectVector;
		collisionObjectVector.clear();
		for (auto collisionObject : m_collisionObjectVector)
		{
			//���O��v�I
			if (strcmp(collisionObject->GetName(), name) == 0)
			{
				collisionObjectVector.push_back(collisionObject);
			}
		}
		return collisionObjectVector;
	}
	/// <summary>
	/// ���O���O����v����R���W�����I�u�W�F�N�g����������B������͕����B
	/// </summary>
	/// <param name="name">���O�B</param>
	/// <returns>�R���W�����I�u�W�F�N�g�̔z��B</returns>
	std::vector<CollisionObject*>& FindMatchForwardNameCollisionObjects(const char* name)
	{
		static std::vector<CollisionObject*> collisionObjectVector;
		collisionObjectVector.clear();
		for (auto collisionObject : m_collisionObjectVector)
		{
			auto len = strlen(name);
			auto namelen = strlen(collisionObject->GetName());
			if (len > namelen) {
				//���O�������B�s��v�B
				continue;
			}
			if (strncmp(name, collisionObject->GetName(), len) == 0)
			{
				collisionObjectVector.push_back(collisionObject);
			}
		}
		return collisionObjectVector;
	}
	/// <summary>
	/// �z�񂩂�R���W�����I�u�W�F�N�g���폜�B
	/// </summary>
	/// <param name="deleteCollisionObject">�폜�������R���W�����I�u�W�F�N�g�B</param>
	void RemoveCollisionObject(CollisionObject* deleteCollisionObject)
	{
		for (auto it = m_collisionObjectVector.begin(); it != m_collisionObjectVector.end();) {
			// ������v�����v�f���폜����
			if (*it == deleteCollisionObject) {
				// �폜���ꂽ�v�f�̎����w���C�e���[�^���Ԃ����B
				it = m_collisionObjectVector.erase(it);
			}
			// �v�f�폜�����Ȃ��ꍇ�ɁA�C�e���[�^��i�߂�
			else {
				++it;
			}
		}
	}
private:
	std::vector<CollisionObject*>		m_collisionObjectVector;

};
extern CollisionObjectManager* g_collisionObjectManager;