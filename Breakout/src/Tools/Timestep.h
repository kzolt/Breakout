#pragma once

namespace Breakout {

	struct Timestep
	{
		float Time;

		Timestep(float time = 0.0f)
			: Time(time) {}

		operator float() const { return Time; }
		
		float GetSeconds() const { return Time; }
		float GetMilliSeconds() const { return Time * 1000; }
	};

}