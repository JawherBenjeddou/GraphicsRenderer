#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"


#include<iostream>
#include<vector>


#include "ImGuiLayer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "SceneCamera.h"
#include "GameTimer.h"
#include "Screen.h"
#include "Mesh.h"
#include "Model.h"

namespace Graphics {


	void Run()
	{
		// -----------------------------------------------------------------------------
		//                             GLFW Initialization
		// -----------------------------------------------------------------------------
		Screen screen("Graphics", 800, 600);

		// -----------------------------------------------------------------------------
		//                             Classes Initialization
		// -----------------------------------------------------------------------------
		Shader shader("../Graphics/shaders/Frag.glsl", "../Graphics/shaders/Vert.glsl");
		SceneCamera camera;
		GameTimer Timer;


		GuiSetup::OnAttach(screen.getWindow());

		//Model ourModel("../assets/models/backpack/backpack.obj");

		glm::vec4 clear_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

		// -----------------------------------------------------------------------------
		//                               Main Loop
		// -----------------------------------------------------------------------------

		//Quick Settings
		float sens = 0.1f;
		float rotation = 0.0f;
		glm::vec3 LightPos(4.0f, 2.0f, 3.0f);
		glm::vec3 Position2(0.0f, 0.0f, 0.0f);
		//To remove cursor from screen
		glfwSetInputMode(screen.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		while (!glfwWindowShouldClose(screen.getWindow()))
		{
			/* Render here */

			screen.Clear(clear_color);
			GuiSetup::Begin();
			glm::vec3 lightColor(1.0f,1.0f,1.0f);
			glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);


			// Object Rendering (Cube)
			//-----------------------
			shader.use();
			glm::mat4 model2 = glm::translate(glm::mat4(1.0f), Position2) * glm::rotate(glm::mat4(1.0f), /*static_cast<float>(glfwGetTime()) * */0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shader.setUniformMat4f("view", camera.getViewMatrix());
			shader.setUniformMat4f("projection", camera.getProjectionMatrix());
			shader.setUniformMat4f("model", model2);
			glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model2)));
			shader.setUniformMat4f("u_normalMatrix", normalMatrix);
			
			//TEXTURE BINDING (LIGHTING STUFF)
			//-------------------------------
			shader.setUniform3Float("u_camerapos", camera.getCameraPosition());
			glm::vec3 directionalLight(-1.0f, -1.0f, -1.0f);
			shader.setUniform3Float("u_light.direction", directionalLight);
			//POINT LIGHT CONFIG
			//------------------
			shader.setUniform3Float("u_PointLight.position", LightPos);
			shader.setUniformFloat("u_PointLight.constant", 1.0f);
			shader.setUniformFloat("u_PointLight.linear", 0.07f);
			shader.setUniformFloat("u_PointLight.quadratic", 0.017f);
			//shader.setUniform3Float("u_light.ambientStrength", 1.0f, 1.0f, 1.0f);
			//shader.setUniform3Float("u_light.diffuseStrength", 1.0f, 1.0f, 1.0f); // very light
			//shader.setUniform3Float("u_light.specularStrength", 1.0f, 1.0f, 1.0f);
			shader.setUniformFloat("u_material.shininess", 32);
			shader.setUniform3Float("u_viewdirection", camera.getViewDirection());
			shader.setUniform3Float("u_viewposition", camera.getCameraPosition());
			glm::vec3 ambientlight(0.1f, 0.1f, 0.1f);
			glm::vec3 diffuselight(0.8f, 0.6f, 0.7f);
			glm::vec3 specularlight(1.0f, 1.0f, 1.0f);
			shader.setUniform3Float("u_light.ambientStrength",ambientlight);
			shader.setUniform3Float("u_light.diffuseStrength",diffuselight); // darkened
			shader.setUniform3Float("u_light.specularStrength",specularlight);


			//ourModel.Draw(shader);
			//OBJECT TEMPORARY MOVEMENT
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
				LightPos.y += 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
				LightPos.y -= 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
				LightPos.x += 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
				LightPos.x -= 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_I) == GLFW_PRESS)
				Position2.y += 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_K) == GLFW_PRESS)
				Position2.y -= 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_L) == GLFW_PRESS)
				Position2.x -= 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_J) == GLFW_PRESS)
				Position2.x += 0.1f;


			// Get current mouse position
			double mouseX, mouseY;
			glfwGetCursorPos(screen.getWindow(), &mouseX, &mouseY);
			glm::vec2 newMousePosition(static_cast<float>(mouseX), static_cast<float>(mouseY));

			// Update camera orientation based on mouse		
			camera.MouseRotation(newMousePosition);
			// Update Keyboard Movement based on the input
			camera.ProcessKeyboardInput(screen.getWindow(), Timer.DeltaTime());


			ImGui::Begin("settings");


			ImGui::SliderFloat("Mouse Sensitivity", &sens, 0.0f, 1.0f);

			camera.setMouseSensitivity(sens);


			ImGui::Text("Background Color : ");

			ImGui::ColorEdit3("clear color", (float*)(&clear_color)); // Edit 3 floats representing a color

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();

			GuiSetup::RenderImGuiElements();

			//Updates the DeltaTime
			Timer.Tick();

			/* Swaps front and back buffers */
			screen.Update();

			/* poll for and process events */
			glfwPollEvents();
		}



		//Free all resources allocated by imgui
		//-------------------------------------
		GuiSetup::OnDetach();
	}
}