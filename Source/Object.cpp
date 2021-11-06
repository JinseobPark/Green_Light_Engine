/******************************************************************
\file   Object.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Contains definition for the Object class which each and
every entities in the game engine will be built upon.
******************************************************************/
#include "Object.h"
#include "DebugTool.h"

using namespace GLE;

Object::Object()
{
	transform = nullptr;
	controller = nullptr;
	sprite = nullptr;
	rigidbody = nullptr;

}

Object::~Object()
{
	//delete all components
	if (transform)
		delete transform;
	if (controller)
		delete controller;
	if (sprite)
		delete sprite;
	if (rigidbody)
		delete rigidbody;
}

void Object::Initialize()
{
	//Initialize all components
	//pCompList
	if (transform)
		transform->Initialize();
	if (controller)
		controller->Initialize();
	if (sprite)
		sprite->Initialize();
	if (rigidbody)
		rigidbody->Initialize();
}

bool Object::AddComponent(Component* pComponent)
{
	//Add component and return true if success
	if (pComponent->GetType() > CT_INVALID && pComponent->GetType() < CT_NUM_COMPONENTS)
		pComponent->SetOwner(this);
	switch (pComponent->GetType())
	{
	case CT_TR:
		transform = dynamic_cast<Transform*>(pComponent);
		return true;
	case CT_CONTROLLER:
		controller = dynamic_cast<Controller*>(pComponent);
		return true;
	case CT_SPRITE:
		sprite = dynamic_cast<Sprite*>(pComponent);
		return true;
	case CT_RIGIDBODY:
		rigidbody = dynamic_cast<RigidBody*>(pComponent);
		return true;
	default:
		break;
	}

	return false; //if failed
}

Component* Object::GetComponent(ComponentType cType)
{
	switch (cType)
	{
	case CT_TR:			return transform;
	case CT_CONTROLLER: return controller;
	case CT_SPRITE:     return sprite;
	case CT_RIGIDBODY:	return rigidbody;
	default:
		break;
	}
	return nullptr;
}

//Signal the object factory for delay destruction
void Object::Destroy()
{

}