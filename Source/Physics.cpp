/******************************************************************
\file   Physics.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  physics
******************************************************************/
#include "Physics.h"
#include "DebugTool.h"
#include "Object.h"
#include "Sprite.h"
#include "Application.h"
#include <iostream>
#include <algorithm>
namespace GLE
{
	Physics* PHYSICS = nullptr;

	Physics::Physics()
	{
		DEBUG_ASSERT(PHYSICS != nullptr, "physics system is already existing !!!\n ");
		PHYSICS = this;
	}

	void Physics::Initialize()
	{

	}

	void Physics::Update(float dt)
	{
		Static_fixed();
		BroadPhase();
		ExplicitEuler(dt);
		MoveUpdate(dt);
		Gravity_Operation(dt);
	}


	void Physics::MoveUpdate(float dt)
	{
		for (std::vector<RigidBody*>::iterator i = m_vecprb.begin();
			i != m_vecprb.end(); ++i)
		{
			(*i)->pm_velocity += ((*i)->pm_ac_velocity * dt);
			(*i)->m_ptransform->AddPosition((*i)->pm_velocity * dt);
		}
	}
	void Physics::ExplicitEuler(float dt)
	{
		//F = ma
		Transform* pTr = nullptr;
		//current frame position, next frame position
		Vector2 curfp;

		for (std::vector<RigidBody*>::iterator i = m_vecprb.begin();
			i != m_vecprb.end(); ++i)
		{
			if ((*i) != NULL)
			{
				//Explicit Euler method
				//f(t + dt) = f(t) + f'(t)dt
				pTr = (*i)->m_ptransform;

				curfp = pTr->GetPosition();
				//Next frame's position = Current frame's position + (Vector * dt)
				//v' = v + at = v + F/m * t

				(*i)->pm_velocity += ((*i)->m_force * (*i)->pm_invmass /*+ (*i)->pm_gravity*/) *dt;
				//p' = p + vt
				pTr->SetPosition(curfp + (*i)->pm_velocity * dt);

				(*i)->m_force.SetZero();
			}
		}
	}


	void Physics::Gravity_Operation(float dt)
	{

		for (std::vector<RigidBody*>::iterator i = m_vecprb.begin();
			i != m_vecprb.end(); ++i)
		{

			//if ((*i)->is_gravity == true)
			//	(*i)->pm_ac_velocity = (*i)->pm_gravity;
			if ((*i)->is_ground == false)
			{
				if ((*i)->is_gravity == true)
					(*i)->pm_ac_velocity = (*i)->pm_gravity;
			}
			else
			{
				(*i)->pm_ac_velocity = Vector2(0.0f, 0.0f);
				(*i)->m_force = Vector2(0.0f, 0.0f);
				(*i)->pm_velocity = Vector2(0.0f, 0.0f);
			}
		}
	}

	void Physics::PositionalCorrection(RigidBody *pA, RigidBody *pB)
	{
		const float percent = 0.2; // usually 20% to 80%
		const float slop = 0.1f;
		Vector2 correction = Max(pA->penetration - slop, 0.0f) / (pA->pm_invmass + pB->pm_invmass) * percent * pA->pm_normal;
		pA->m_ptransform->AddPosition(-pA->pm_invmass * correction);
		pB->m_ptransform->AddPosition(pB->pm_invmass * correction);
	}

	void Physics::Static_fixed()
	{
		for (std::vector<RigidBody*>::iterator i = m_vecprb.begin();
			i != m_vecprb.end(); ++i)
		{
			if ((*i)->pm_dynamic == STATIC)
			{
				(*i)->pm_velocity = Vector2(0.0f, 0.0f);
				(*i)->m_force = Vector2(0.0f, 0.0f);
				(*i)->pm_gravity = Vector2(0.0f, 0.0f); 
				(*i)->pm_invmass = 0;
				(*i)->is_gravity = false;
			}
		}
	}
	//void Physics::BroadPhase()
	//{
	//	//k; number of objects
	//	//Big O Notation O(n^2 / 2)
	//	for (std::vector<RigidBody*>::iterator i = m_vecprb.begin();
	//		i != m_vecprb.end();
	//		++i)
	//	{
	//		for (std::vector<RigidBody*>::iterator j = i + 1;
	//			j != m_vecprb.end();
	//			++j)
	//		{
	//			//Check collision between two AABB objects
	//			//put the pair into the container.
	//			if (AABBAABCollisionCheck((*i), (*j)))
	//			{
	//				//Put the pair into the container.
	//				m_vecpair.push_back(Pair(*i, *j));
	//			}
	//		}
	//	}
	//}
	void Physics::BroadPhase()
	{
		//std::vector<RigidBody*>::iterator Player_r;
		RigidBody *Player_r = NULL;
		std::vector<RigidBody*>::iterator i;
		//k; number of objects
		//Big O Notation O(n^2 / 2)
		//Player_r = std::find(m_vecprb.begin(), m_vecprb.end(), ((*i)->GetType == PLAYER_1 || (*i)->GetType == PLAYER_2));
		for (i = m_vecprb.begin(); i != m_vecprb.end(); ++i)
		{
			if (((*i)->GetType() == PLAYER_1) || ((*i)->GetType() == PLAYER_2))
				Player_r = (*i);
		}
		if (Player_r != NULL)
		{
			Player_r->check_ground = false;		
			for (std::vector<RigidBody*>::iterator i = m_vecprb.begin();
				i != m_vecprb.end();
				++i)
			{
				if (*i != Player_r)
				{
					if (AABBvsAABB((*i), (Player_r)))
					{
						//printf("collied!\n");
						if ((*i)->GetType() == WALL)
						{
							PositionalCorrection((*i), (Player_r));
							ResolveCollision((*i), (Player_r));
							//TODO: player vs wall colide
						}
						if ((*i)->GetType() == ITEM)
						{
							//TODO: player vs item colide
						}
					}

				}
			}
			if (Player_r->check_ground == false)
			{
				//Player_r->is_ground = false;
				//Player_r->down_ground = false;
				//Player_r->right_ground = false;
				//Player_r->left_ground = false;
				Player_r->is_ground = AIR;
			}
		}
		
	}

	void Physics::ResolveCollision(RigidBody *pA, RigidBody *pB)
	{
		// Calculate relative velocity
		Vector2 rv = pB->pm_velocity - pA->pm_velocity;
			// Calculate relative velocity in terms of the normal direction
		float velAlongNormal = DotProduct(rv, pA->pm_normal);
			//float velAlongNormal = DotProduct(rv, normal)

			// Do not resolve if velocities are separating
			if (velAlongNormal > 0)
				return;

		// Calculate restitution
			float e = Min(pA->pm_restitution, pB->pm_restitution);

			// Calculate impulse scalar
			float j = -(1 + e) * velAlongNormal;
			j /= pA->pm_invmass + pB->pm_invmass;
			// Apply impulse
			Vector2 impulse = j *  pA->pm_normal;
			pA->pm_velocity -= pA->pm_invmass * impulse;
			pB->pm_velocity += pB->pm_invmass * impulse;
	}
	//			for (std::vector<RigidBody*>::iterator j = i + 1;
	//				j != m_vecprb.end();
	//				++j)
	//		{
	//			//Check collision between two AABB objects
	//			//put the pair into the container.
	//			if (AABBAABCollisionCheck((*i), (*j)))
	//			{
	//				//Put the pair into the container.
	//				m_vecpair.push_back(Pair(*i, *j));
	//			}
	//		}
	//	}
	//}
	bool Physics::AABBAABCollisionCheck(RigidBody *pA, RigidBody *pB)
	{
		//pB is player
		Sprite* pAsprite = dynamic_cast<Sprite*>(pA->GetOwner()->GetComponent(CT_SPRITE));
		Sprite* pBsprite = dynamic_cast<Sprite*>(pB->GetOwner()->GetComponent(CT_SPRITE));
		Vector2 asize = Vector2(pAsprite->Size.x, pAsprite->Size.y),
			apos = Vector2(pA->m_ptransform->GetPosition().x * (APP->screenWidth / 2.f),
				pA->m_ptransform->GetPosition().y * (APP->screenHeight / 2.f));
		Vector2 bsize = Vector2(pBsprite->Size.x, pBsprite->Size.y),
			bpos = Vector2(pB->m_ptransform->GetPosition().x * (APP->screenWidth / 2.f),
				pB->m_ptransform->GetPosition().y * (APP->screenHeight / 2.f));
		Vector2 atl, abr, btl, bbr;

		//Top left
		atl = Vector2(apos.x - asize.x / 2.f, apos.y + asize.y / 2.f);
		//Bottom right
		abr = Vector2(apos.x + asize.x / 2.f, apos.y - asize.y / 2.f);
		//Top left
		btl = Vector2(bpos.x - bsize.x / 2.f, bpos.y + bsize.y / 2.f);
		//Bottom right
		bbr = Vector2(bpos.x + bsize.x / 2.f, bpos.y - bsize.y / 2.f);

		if (atl.x > bbr.x)
		{
			//std::cout << "nop" << std::endl;
			return false;
		}
		if (abr.x < btl.x)
		{
			//std::cout << "nop" << std::endl;
			return false;
		}
		if (abr.y > btl.y)
		{
			//std::cout << "nop" << std::endl;
			return false;
		}
		if (atl.y < bbr.y)
		{
			//std::cout << "nop" << std::endl;
			return false;
		}

		return true;

	}

	
	bool Physics::AABBvsAABB(RigidBody * pA, RigidBody * pB)
	{
		Sprite* pAsprite = dynamic_cast<Sprite*>(pA->GetOwner()->GetComponent(CT_SPRITE));
		Sprite* pBsprite = dynamic_cast<Sprite*>(pB->GetOwner()->GetComponent(CT_SPRITE));
		Vector2 asize = Vector2(pAsprite->Size.x, pAsprite->Size.y),
			apos = Vector2(pA->m_ptransform->GetPosition().x * (APP->screenWidth / 2.f),
				pA->m_ptransform->GetPosition().y * (APP->screenHeight / 2.f));
		Vector2 bsize = Vector2(pBsprite->Size.x, pBsprite->Size.y),
			bpos = Vector2(pB->m_ptransform->GetPosition().x * (APP->screenWidth / 2.f),
				pB->m_ptransform->GetPosition().y * (APP->screenHeight / 2.f));
		Vector2 atl, abr, btl, bbr;
		//Top left
		atl = Vector2(apos.x - asize.x / 2.f, apos.y + asize.y / 2.f);
		//Bottom right
		abr = Vector2(apos.x + asize.x / 2.f, apos.y - asize.y / 2.f);
		//Top left
		btl = Vector2(bpos.x - bsize.x / 2.f, bpos.y + bsize.y / 2.f);
		//Bottom right
		bbr = Vector2(bpos.x + bsize.x / 2.f, bpos.y - bsize.y / 2.f);

		//Vector2 asize = Vector2(pA->m_ptransform->GetScalel());
		//Vector2  apos = Vector2(pA->m_ptransform->GetPosition());
		//Vector2 bsize = Vector2(pB->m_ptransform->GetScalel());
		//Vector2  bpos = Vector2(pB->m_ptransform->GetPosition());
		//Vector2 atl, abr, btl, bbr;

		//atl = Vector2(apos.x - (asize.x), apos.y + (asize.y));
		//abr = Vector2(apos.x + (asize.x), apos.y - (asize.y));
		//btl = Vector2(bpos.x - (bsize.x), bpos.y + (bsize.y));
		//bbr = Vector2(bpos.x + (bsize.x), bpos.y - (bsize.y));

		// Vector from A to B
		Vector2 normal = pB->m_ptransform->GetPosition() - pA->m_ptransform->GetPosition();
		// Calculate half extents along x axis for each object
		float a_extent = (abr.x - atl.x) / 2;
		float b_extent = (bbr.x - btl.x) / 2;

		float x_overlap = a_extent + b_extent - std::abs(normal.x);

		if (x_overlap > 0)
		{
			float a_extent = (atl.y - abr.y) / 2;
			float b_extent = (btl.y - bbr.y) / 2;

			float y_overlap = a_extent + b_extent - Abs(normal.y);

			if (y_overlap > 0)
			{
				// Find out which axis is axis of least penetration
				if (x_overlap < y_overlap)
				{
					// Point towards B knowing that n points from A to B
					if (normal.x < 0)
					{
						pA->pm_normal = Vector2(-1, 0);
						pB->check_ground = true;
						pB->is_ground = RIGHT;
					}
					else
					{
						pB->check_ground = true;
						pB->is_ground = LEFT;
						pA->pm_normal = Vector2(1, 0);
					}
					pA->penetration = x_overlap;
					return true;
				}
				else
				{
					// Point toward B knowing that n points from A to B
					if (normal.y < 0)
						pA->pm_normal = Vector2(0, -1);
					else
					{
						//ground
						pA->pm_normal = Vector2(0, 1);
						pB->check_ground = true;
						pB->is_ground = DOWN;
					}
					pA->penetration = y_overlap;
					
					//M->m_lhs->Jump = true; 
					//M->m_rhs->Jump = true;
					return true;
				}
			}
		}
		return false;
	}
	
}