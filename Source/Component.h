/******************************************************************
\file   Component.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  This class contains definition for the component class,
which gives identity to every Object in the game
******************************************************************/
#pragma once
#include "ComponentType.h"

namespace GLE
{
	//Forward declaration of Object class
	class Object;

	class Component
	{
	public:
		friend class Object;

		//Object will initialize all Components
		virtual void Initialize() {};

		Object* GetOwner() { return pOwner; }
		void SetOwner(Object* owner) { pOwner = owner; }
		ComponentType GetType() { return pType; }

		virtual ~Component() {};

		Component(ComponentType type) : pType(type) {}

	private:
		Object* pOwner;
		ComponentType pType;
	};
}