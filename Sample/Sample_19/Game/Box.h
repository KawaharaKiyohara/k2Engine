#pragma once

//�S�[�X�g�I�u�W�F�N�g���g�p����ɂ́A�t�@�C�����C���N���[�h����K�v������B
#include "physics/PhysicsGhostObject.h"

class Box : public IGameObject
{
public:
	bool Start();
	
	//�S�[�X�g�I�u�W�F�N�g�B
	PhysicsGhostObject m_physicsGhostObject;
};

