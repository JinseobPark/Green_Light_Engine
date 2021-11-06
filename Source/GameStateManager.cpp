/******************************************************************
\file   GameStageManager.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  
******************************************************************/
#include "GameState.h"
#include "Factory.h"
#include "GameStateManager.h"
#include "Object.h"
#include "Physics.h"

namespace GLE
{

	void GameStateManager::Init()
	{
		printf("GSM Init\n");
		//AddLogic(new ObjectFactory());
		//AddLogic(new Physics());

		//for (auto logics : LogicList)
		//	logics->Initialize();
	}

	void GameStateManager::Cleanup()
	{
		// cleanup the all states
		while (!states.empty()) {
			states.back()->Cleanup();
			states.pop_back();
		}

		// shutdown SDL
		SDL_Quit();
	}

	void GameStateManager::ChangeState(GameState* state)
	{
		// cleanup the current state
		if (!states.empty()) {
			states.back()->Cleanup();
			states.pop_back();
		}

		// store and init the new state
		states.push_back(state);
		states.back()->Init();
	}

	void GameStateManager::PushState(GameState* state)
	{
		// pause current state
		if (!states.empty()) {
			states.back()->Pause();
		}

		// store and init the new state
		states.push_back(state);
		states.back()->Init();
	}

	void GameStateManager::PopState()
	{
		// cleanup the current state
		if (!states.empty()) {
			states.back()->Cleanup();
			states.pop_back();
		}

		// resume previous state
		if (!states.empty()) {
			states.back()->Resume();
		}
	}

	void GameStateManager::HandleEvents()
	{
		// let the state handle events
		states.back()->HandleEvents(this);
	}

	void GameStateManager::Update(float dt)
	{
		// let the state update the game
		states.back()->Update(this);
	}

	void GameStateManager::Draw()
	{
		// let the state draw the screen
		states.back()->Draw(this);
	}

	void GameStateManager::Unload()
	{
		printf("unload\n");

	}

	void GameStateManager::AddLogic(ObjectLogic* logic)
	{
		LogicList.push_back(logic);
	}
}