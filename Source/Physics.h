/******************************************************************
\file   Physics.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief
******************************************************************/
#pragma once
#include <list>

#include "Systems.h"
#include "DebugTool.h"
#include <vector>

namespace GLE
{
	class RigidBody;

	class Pair
	{
	public:
		Pair(RigidBody *lhs, RigidBody *rhs) : m_lhs(lhs), m_rhs(rhs) {}

		RigidBody* m_lhs;
		RigidBody* m_rhs;
	private:
		Pair();
	};

	class Physics : public Systems
	{
	public:
		Physics();
		~Physics() {};

		//Initialize the system
		void Initialize() override;

		//Integrator
		void Update(float dt) override;

		//Member variable; vector of pointer to Rigidbody
		std::vector<RigidBody*> m_vecprb;

	private:
		//Explicit Euler (Forward Euler) Intergrator
		void ExplicitEuler(float dt);

		void ResolveCollision(RigidBody *lhs, RigidBody *rhs);
		void BroadPhase();
		void MoveUpdate(float dt);
		void Gravity_Operation(float dt);
		void Static_fixed();
		//Check two AABB object's collision,
		//return true if collided, and false otherwise.
		void PositionalCorrection(RigidBody *pA, RigidBody *pB);
		bool AABBAABCollisionCheck(RigidBody *lhs, RigidBody *rhs);
		bool AABBvsAABB(RigidBody * pA, RigidBody * pB);
		std::vector<Pair> m_vecpair;
	};
	extern Physics* PHYSICS;


}