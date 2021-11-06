/****************************************************
\file   Systems.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  This file is system of engine.
****************************************************/


#pragma once

namespace GLE
{
	class Systems
	{
	public:
		//Initialize the system
		virtual void Initialize() {};

		//All systems are updated every frame
		virtual void Update(float dt) = 0;

		//All systems need a virtual destructor to their destructors called
		virtual ~Systems() {};
	};

	class ObjectLogic
	{
	public:
		//Initialize the system
		virtual void Initialize() {};

		//All systems are updated every frame
		virtual void Update(float dt) = 0;

		//All systems need a virtual destructor to their destructors called
		virtual ~ObjectLogic() {};
	};

}// namespace GLE end