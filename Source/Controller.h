/****************************************************************************
\file   Controller.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  component controller
*****************************************************************************/
#pragma once

#include "Component.h"
#include "GameLogic.h"

namespace GLE
{
	class Controller : public Component
	{
	public:
		Controller() : Component(ComponentType::CT_CONTROLLER)
		{
			myController = GAMELOGIC->ControllerList.insert(GAMELOGIC->ControllerList.end(), this);
		}
		~Controller() { GAMELOGIC->ControllerList.erase(myController); };

		virtual void Initialize() {};

		virtual void Update(float) {};
	private:
		std::list<Controller*>::iterator myController;
	};
}