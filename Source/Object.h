/******************************************************************
\file   Object.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Contains definition for the Object class which each and
every entities in the game engine will be built upon.
******************************************************************/
#pragma once

#include <vector>
#include "Component.h"
#include "ComponentType.h"
#include "Transform.h"
#include "Controller.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "GameLogic.h"

namespace GLE
{
	typedef unsigned int ObjectID;
	class Object
	{
	public:
		friend class ObjectFactory;

		Object();
		~Object();

		void Initialize();
		//Properly destroy the object by delay destruction
		void Destroy();

		bool AddComponent(Component* pComponent);
		Component* GetComponent(ComponentType cType);

	private:
		//All different types of pointers to different components
		//but set to nullptr if component doesn't exist
		Transform* transform;
		Sprite* sprite;
		RigidBody* rigidbody;
		Controller* controller;
		//Uniqud ID for each object used to safely reference objects
		ObjectID objID;
	};
}