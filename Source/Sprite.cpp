/******************************************************************
\file   Sprite.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  sprite graphics
******************************************************************/
#include "Sprite.h"
#include "DebugTool.h"
#include <algorithm>
#include "Object.h" //getowner

namespace GLE
{
	Sprite::Sprite() : Component(ComponentType::CT_SPRITE)
	{
		GRAPHICS->SpriteList.push_back(this);
	}

	Sprite::~Sprite()
	{
		//Add this sprite comp to graphics sprite list
		GRAPHICS->SpriteList.erase(std::find(GRAPHICS->SpriteList.begin(), GRAPHICS->SpriteList.end(), this));
	}
	void Sprite::Initialize()
	{
		pTransform = (Transform*)GetOwner()->GetComponent(CT_TR);
		if (pTransform == nullptr)
		{
			DEBUG_PRINT("Sprite init error\n");
		}
	}
}// namespace GLE end