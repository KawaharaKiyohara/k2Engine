#include "k2EnginePreCompile.h"
#include "CollisionObject.h"

CollisionObjectManager* g_collisionObjectManager = nullptr;

CollisionObject::CollisionObject()
{

}

CollisionObject::~CollisionObject()
{
	g_collisionObjectManager->RemoveCollisionObject(this);
}

bool CollisionObject::Start()
{
	g_collisionObjectManager->AddCollisionObject(this);
	return true;
}

void CollisionObject::Update()
{
	if (m_isEnableAutoDelete == false)
	{
		return;
	}


	if (m_timer > m_timeLimit + 0000.1f)
	{
		DeleteGO(this);
	}
	m_timer += g_gameTime->GetFrameDeltaTime();
}


CollisionObjectManager::CollisionObjectManager()
{

}

CollisionObjectManager::~CollisionObjectManager()
{
	m_collisionObjectVector.clear();
}