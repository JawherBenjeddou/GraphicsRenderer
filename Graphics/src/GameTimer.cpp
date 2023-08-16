#include "GameTimer.h"





GameTimer::GameTimer() :
	m_DeltaTime(0),
	m_LastFrame(0.0f),
	m_CurrTime(0),
	m_Stopped(false)
{

}

float GameTimer::DeltaTime() const
{
	return m_DeltaTime;
}

void GameTimer::Tick()
{
	float CurrentFrame = static_cast<float>(glfwGetTime());
	m_DeltaTime = CurrentFrame - m_LastFrame;
	m_LastFrame = CurrentFrame;
}
