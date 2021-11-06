/******************************************************************
\file   Timer.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Static class to keep track of time
******************************************************************/
#pragma once

#include <chrono>

namespace GLE
{
	using namespace std::chrono;

	namespace
	{
		time_point<high_resolution_clock> prevTime;
		time_point<high_resolution_clock> currTime;
	}

	class Timer
	{
	public:
		static void Initialize(void)
		{
			prevTime = currTime = high_resolution_clock::now();
		};

		static float GetDelta(void)
		{
			currTime = high_resolution_clock::now();

			duration<float> delta(currTime - prevTime);

			prevTime = high_resolution_clock::now();

			return delta.count();
		};

	private:


	};
}// namespace GLE end

