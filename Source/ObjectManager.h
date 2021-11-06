/******************************************************************
\file   ObjectManager.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  object manager
******************************************************************/
#pragma once
#include "Object.h"
#include "Vector3.h"

namespace GLE {
	class ObjectManager
	{
	public:
		ObjectManager(int maxObjects, int maxButtons);
		~ObjectManager(void);

		Object* GetObjects(void);
		int GetObjectCount(void) const;

		void DeleteObject(int objectID);
		void AddObject(
			const Vector3& pos,
			const Vector3& Vel,
			float rotation,
			float rotationVel,
			float scale,
			int texture,
			unsigned color);

		void LoadObject(void);
		void RemoveAllObject(void);
		void Update(void);
		void Draw(void);
		void Unload(void);




	private:
		Object* _pObject; //pointer to objects.
		int _objectCount; //number of the object currently added.
		int _maxObjects; //maximum number of objects can be added.
	};
}
