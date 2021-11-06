/****************************************************
\file   Engine.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  This file is header of Engine.cpp
****************************************************/
#pragma once

#include <vector>
#include "Systems.h"
#include <memory>

namespace GLE
{
	//The engine manage all systems in the game, updating them, routing msgs,
	//and destroy the systems when the game ends.
	class Engine
	{
	public:
		Engine();
		~Engine();

		//Update all systems
		void GameLoop();
		//Destroy all systems in the engine in reverse to avoid dependency issues
		void DestroyAllSystems();
		//Add systems to the engine
		void AddSystem(Systems* system);
		//Initialize Engine which means initialize all systems
		void Initalize();

		void Quit();

		//Todo : System Message functions

	private:
		//Hide Constructor
		//Engine(bool debugMode_ = false);
		//Track all systems the engine uses
		std::vector<Systems*> SystemsList;
		//Main Loop
		bool GameIsRunning;
		//delta for each frame
		float dt;
		//Fixed time step used for the physics intergration function.
		const float pm_fixeddt;
		//Accumulation of time cannot exceed pm_accumlock.
		const float pm_accumlock;
		//Accumulation
		float pm_accumulator;
	};

	//A global pointer ot the instance of the Engine
	extern Engine* ENGINE;
}//namespace SWE end
