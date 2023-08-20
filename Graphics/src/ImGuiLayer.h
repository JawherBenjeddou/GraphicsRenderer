#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace GuiSetup
{

	void OnAttach(GLFWwindow* window) ;
	void OnDetach(); 
	void Begin();
	void RenderImGuiElements();
	
	void SetDarkThemeColors();

};