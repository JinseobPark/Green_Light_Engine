/****************************************************************************
\file   GameLogic.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  
*****************************************************************************/
#include "GameLogic.h"
#include "Controller.h"

using namespace GLE;

namespace GLE
{
	GameLogic* GAMELOGIC = nullptr;
}

GameLogic::GameLogic()
{
	DEBUG_ASSERT(GAMELOGIC != nullptr, "There can bo only 1! GameLogic System");
	GAMELOGIC = this;
}

GameLogic::~GameLogic()
{

}

void GameLogic::Initialize()
{

}

void GameLogic::Update(float dt)
{
	//std::list<Controller>::iterator itr = ControllerList.begin();
	for (auto element : ControllerList)
		element->Update(dt);
}
