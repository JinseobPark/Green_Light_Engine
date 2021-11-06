/******************************************************************
\file   Rigidbody.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  rigidbody physics
******************************************************************/
#pragma once

#include "Component.h"
#include "vector2.h"

enum DynamicState {
	DYNAMIC, STATIC
};

enum ObjectType
{
	PLAYER_1 = 0,
	PLAYER_2,
	WALL,
	ITEM,
	NONE
};

enum GroundType
{
	AIR = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

namespace GLE
{
	class Transform;
	class Sprite;
	class RigidBody : public Component
	{
	public:
		RigidBody(Vector2 vel, DynamicState d_type, ObjectType otype);
		~RigidBody();

		void Set_mass(float invass) { pm_invmass = invass; }
		Vector2 m_force;
		Transform* m_ptransform;
		Sprite* m_sprite;

		void Initialize();
		ObjectType GetType(void) {
			return pm_otype;
		}
		GroundType Get_is_ground(void)
		{
			return is_ground;
		}
		Vector2& RigidBody::GetVelocity(void);
		//shit
		void PrintCheck(void);
	private:
		friend class Physics;
		RigidBody() : Component(ComponentType::CT_RIGIDBODY) {};
		//private member variable inverse mass
		float pm_invmass;
		float pm_restitution;
		Vector2 pm_velocity;
		Vector2 pm_ac_velocity;
		DynamicState pm_dynamic;
		ObjectType pm_otype;
		Vector2 pm_gravity;
		Vector2 pm_normal;
		float penetration;
		//bool is_ground;
		GroundType is_ground;
		bool is_gravity;
		bool check_ground;


	};
}