/******************************************************************
\file   Graphics.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  graphics
******************************************************************/
#pragma once

#include <list>
#include "Systems.h"
#include <vector> // sprite list
#include "Sprite.h"

namespace GLE {
	//Forward declaration of Sprite Component
	class Sprite;

	class Graphics : public Systems
	{
	public:
		Graphics();
		//Initialize the system
		void Initialize() override;

		//All systems are updated every frame
		void Update(float dt) override;

		//All systems need a virtual destructor to their destructors called
		~Graphics();

		//List of sprite components
		std::vector<Sprite*> SpriteList;
	private:
		unsigned int program;
		unsigned int VAO;

		unsigned int uniformLocations[2]; //posOffset, size Offset
	};


	extern Graphics* GRAPHICS;
}

