/******************************************************************
\file   ObjectManager.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  object manager
******************************************************************/
#include "ObjectManager.h"

namespace GLE {
	ObjectManager::ObjectManager(int maxObjects, int maxButtons)
	{
		_pObject = new Object[maxObjects];

		_objectCount = 0;
		_maxObjects = maxObjects;
	}


	ObjectManager::~ObjectManager(void)
	{
		delete[] _pObject;
	}


	Object* ObjectManager::GetObjects(void)
	{
		return _pObject;
	}


	int ObjectManager::GetObjectCount(void) const
	{
		return _objectCount;
	}


	void ObjectManager::DeleteObject(int objectID)
	{
		_pObject[objectID] = _pObject[_objectCount - 1];

		_objectCount--;
	}


	void ObjectManager::AddObject(
		const Vector3& pos,
		const Vector3& Vel,
		float rotation,
		float rotationVel,
		float scale,
		int texture,
		unsigned color)
	{
		if (_objectCount < _maxObjects)
		{
			_objectCount++;
		}
	}

	void ObjectManager::RemoveAllObject(void)
	{
		while (_objectCount != 0)
			DeleteObject(_objectCount - 1);
	}

}