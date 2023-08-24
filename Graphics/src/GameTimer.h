#pragma once
#include <iostream>

#include "GLFW/glfw3.h"


class GameTimer
{
public:
	GameTimer();


	// in seconds
	float DeltaTime() const; 


	// Call every frame.
	void Tick(); 

private:
	float m_DeltaTime;
	float m_LastFrame ;
	int32_t m_CurrTime;
	bool m_Stopped;
};