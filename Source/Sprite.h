/******************************************************************
\file   Sprite.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  sprite graphic
******************************************************************/
#pragma once

#include "Component.h"
#include "Graphics.h"
#include "vector2.h"
#include "Transform.h"

namespace GLE
{
	class Sprite : public Component
	{
	public:
		Sprite();
		~Sprite();

		virtual void Initialize() override;

		Vector2 Size;
		float Color[4];

		unsigned int TextureID;
		Transform* pTransform;
		//Todo :
		//Animation
		//...
		//private:
		//	std::list<Sprite*>::iterator mysprite;
	};
}// namespace GLE end