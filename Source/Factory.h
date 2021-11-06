/****************************************************************************
\file   Factory.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  This file is header of Factory.cpp
*****************************************************************************/
#pragma once

#include "Systems.h"
#include "Object.h"
#include <map>

namespace GLE
{
	class ObjectFactory : public Systems
	{
	public:
		ObjectFactory();
		~ObjectFactory();

		void Initialize() override;

		void Update(float dt) override;

		//Add an object to the destroy list for delay destruction
		void Destory(Object*);

		//For the shutdown of the Factory
		void DestroyAllObject();

		//helper function to ID objects
		//ID the object and store it in the object list(map)
		void IDGameObject(Object* gameObject);

		//Return an object with specific ID
		Object* GetObjectwID(ObjectID id);

		Object* CreateEmptyObject();
		//Showing how to create an object through hardcode
		//Todo : When applying data driven methods, use this as blueprint
		Object* CreatePlayer(const Vector2& position, const Vector2& vel, const Vector2& scale);
		Object* CreateWall(const Vector2& position, const Vector2& vel, const Vector2& scale);
		Object* CreateItem(const Vector2& position, const Vector2& vel, const Vector2& scale);

	private:
		//Used to incrementally generate unique IDs
		ObjectID LastObjectID;

		//Map of Objects to their IDs used for safe referencing
		std::map<ObjectID, Object*> ObjectIDMap;

		//List of Objects to be deleted
		//To prevent problems of early of multi call of Object's destruction
		std::vector<Object*> ObjectsToBeDeleted;
	};

	extern ObjectFactory* FACTORY;
}