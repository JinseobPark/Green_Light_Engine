/******************************************************************
\file   Transform.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Transform for object
******************************************************************/
#pragma once
#include "Application.h"
#include "Component.h"
#include "vector2.h"

namespace GLE
{
	class Transform : public Component
	{
	public:
		//Initialize
		Transform() : Component(ComponentType::CT_TR)
		{
			Position = Vector2(0.f, 0.f);
			Scale = Vector2(1.f, 1.f);
			Rotation = 0.f;
		}

		//Get Owner
		Vector2 GetPosition() { return Position; }
		void SetPosition(Vector2 pos) 
		{
			Position = pos;
		}
		void AddPosition(Vector2 pos) {
			Vector2 init = GetPosition();
			init += pos;
			SetPosition(init);
		}
		Vector2 GetScalel() { return Scale; }
		void SetScale(Vector2 scale) { Scale = scale; }
		void AddScale(Vector2 scale) {
			Vector2 init = GetScalel();
			init += scale;
			SetScale(init);
		}
		float GetRotation() { return Rotation; }
		void SetRotation(float rot) { Rotation = rot; }

		float GetArea(Vector2 scale) { return scale.x * scale.y; }
		Vector2 Transform::GetPositionWorldCoordinate(void)
		{
			return Vector2(Position.x * APP->screenWidth / 2, Position.y * APP->screenHeight / 2);
		}
	private:
		Vector2 Position;
		Vector2 Scale;
		float Rotation;
	};
}// namespace GLE end