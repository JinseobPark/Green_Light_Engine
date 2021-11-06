/****************************************************************************
\file   GameLogic.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  This file is header of GameLogic.cpp
*****************************************************************************/
#pragma once

#include <list>

#include "Systems.h"
#include "DebugTool.h"

namespace GLE
{
	//Forward declaration of Controller Component
	class Controller;

	class GameLogic : public Systems
	{
	public:
		GameLogic();
		~GameLogic();

		void Initialize() override;
		void Update(float dt) override;

		//List of controller components
		std::list<Controller*> ControllerList;

	private:
	};
	extern GameLogic* GAMELOGIC;

}