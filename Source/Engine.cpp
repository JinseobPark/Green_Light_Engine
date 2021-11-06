/****************************************************
\file   Engine.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  This file is base engine of GLEngine.
****************************************************/
#include "Engine.h"
#include <iostream>
#include "DebugTool.h"
#include "input.h"
#include "Application.h"
#include "Timer.h"
#include "input.h"
#include "GameLogic.h"
#include "Factory.h"
#include "Object.h"
#include "Transform.h"
#include "Physics.h"
#include "GameStateManager.h"
#include "../GoodTest/GoodTest/StateList.h"
#include "../GoodTest/GoodTest/PlayerController.h"
#include "Graphics.h"


using namespace GLE;
namespace GLE
{
	Engine* ENGINE = nullptr;
	GameStateManager GameStage;
}
Engine::Engine() : GameIsRunning(true), dt(0),
pm_fixeddt(1 / 60.f), pm_accumulator(0.f), pm_accumlock(0.25f)
{
	DEBUG_ASSERT(ENGINE != nullptr, "More than 1 instance of the Engine cannot be created!!! YOU FOOL!");
	ENGINE = this;
}
 

Engine::~Engine()
{
	
}

void Engine::Initalize()
{
	
	Input::Initialize();
	//Todo : Add systems to the engine here.
	AddSystem(new Application()); //0
								  //AddSystem(Application::instance());
								  //add systems
	AddSystem(new ObjectFactory()); //1 move gamestatemanager
	AddSystem(new GameLogic()); //2
	AddSystem(new Graphics()); //3
	AddSystem(new Physics()); //4 move gamestatemanager
							  //AddSystem(Graphics::instance());
							  //Todo : //Initialize systems after being added

	
	for (auto sys : SystemsList)           //for (unsigned i = 0; i < SystemsList.size(); ++i)
		sys->Initialize();		     	   	//SystemsList[i]->Update(dt); 

	// Load intro
	GameStage.Init();
	GameStage.ChangeState(GLIntroState::Instance());

}

void Engine::Quit()
{
	GameIsRunning = false;
}

//This is where all systems update
void Engine::GameLoop()
{
	//Initialize Timer
	Timer::Initialize();

	while (GameIsRunning)
	{

		if (Input::IsTriggered(SDL_SCANCODE_J))
			printf("keyboard J");
		//Calculate the amount of time took for one iteration in previous frame.
		//Update the dt
		dt = Timer::GetDelta();
		
		pm_accumulator += dt;

		if (pm_accumulator > pm_accumlock)
			pm_accumulator = pm_accumlock;


		// Update all systems
		//Update Application, ObjectFactory, GameLogic

		//3 is the index for the Physics.
		//Implement GetSystem function, whether it's templatized or..
		for (unsigned i = 0; i < 5; ++i)
			SystemsList[i]->Update(dt);

		while (pm_accumulator > pm_fixeddt)
		{
			PHYSICS->Update(dt);
			pm_accumulator -= pm_fixeddt;
		}
		GRAPHICS->Update(dt);
		GameStage.HandleEvents();
		GameStage.Update(dt);
		GameStage.Draw();


	}
	//Delete all game objects
	FACTORY->DestroyAllObject();
}

void GLE::Engine::AddSystem(Systems * system)
{
	//Add a system to the Engine to be updated every frame
	SystemsList.push_back(system);
}

void GLE::Engine::DestroyAllSystems()
{
	//Delete all systems (in reverse) that they were added in
	//to minimize dependency problems between systems
	for (unsigned i = 0; i < SystemsList.size(); ++i)
		delete SystemsList[SystemsList.size() - 1 - i];
}