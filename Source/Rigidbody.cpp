/******************************************************************
\file   Rigidbody.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  rigidbody for physics
******************************************************************/
#include "Rigidbody.h"
#include "Physics.h"
#include "Object.h"
//GetOwner method returns pointer to Object
#include "Transform.h"
#include <iostream>
namespace GLE
{
	RigidBody::RigidBody(Vector2 vel = { 0,0 }, DynamicState d_type = DYNAMIC,  ObjectType otype = ObjectType::NONE)
		: Component(CT_RIGIDBODY), pm_velocity(vel), pm_dynamic(d_type), pm_otype(otype)
	{
		pm_gravity = { 0.f, -100.f };
		pm_restitution = 0.01f;
		pm_invmass = 1.f;
		pm_ac_velocity = { 0.f, 0.f };
		pm_normal = { 0.f, 0.f };
		penetration = 0.f;
		is_gravity = true;
		is_ground = AIR;
		check_ground = false;

		//Put the pointer to component to the vector container,
		//so that Physics system can iterate through.
		PHYSICS->m_vecprb.push_back(this);
	}


	RigidBody::~RigidBody()
	{
		PHYSICS->m_vecprb.erase(std::find(PHYSICS->m_vecprb.begin(), PHYSICS->m_vecprb.end(), this));
	}


	void RigidBody::Initialize()
	{
		m_ptransform = dynamic_cast<Transform*>(GetOwner()->GetComponent(CT_TR));
	}


	void RigidBody::PrintCheck(void)
	{
		std::cout << "is ground is " << is_ground << "   is gravity is " << is_gravity << "\n";
	}
	Vector2& RigidBody::GetVelocity(void)
	{
		return pm_velocity;
	}
}