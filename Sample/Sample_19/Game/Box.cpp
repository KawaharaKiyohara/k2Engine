#include "stdafx.h"
#include "Box.h"

bool Box::Start()
{
	//�S�[�X�g�I�u�W�F�N�g���������B
	m_physicsGhostObject.CreateBox(Vector3(100.0f, 100.0f, 200.0f), Quaternion::Identity, Vector3::One * 200.0f);
	return true;
}
