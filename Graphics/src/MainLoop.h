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
		Screen screen("Graphics", SCREEN_WIDTH, SCREEN_HEIGHT);

		// -----------------------------------------------------------------------------
		//                             Classes Initialization
		// -----------------------------------------------------------------------------
		Shader shader("../Graphics/shaders/Frag.glsl", "../Graphics/shaders/Vert.glsl");
		
		SceneCamera camera;
		GameTimer Timer;
		

		GuiSetup::OnAttach(screen.getWindow());

		Model model("../assets/models/airplane/scene.gltf");

		glm::vec4 clear_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

		// -----------------------------------------------------------------------------
		//                               Main Loop
		// -----------------------------------------------------------------------------

		//Quick Settings
		float sens = 0.1f;
		float rotation = 0.0f;
		glm::vec3 LightPos(4.0f, 2.0f, 3.0f);
		//To remove cursor from screen
		glfwSetInputMode(screen.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		while (!glfwWindowShouldClose(screen.getWindow()))
		{
			/* Render here */

			screen.Clear(clear_color);
			GuiSetup::Begin();
			glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
			glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
			shader.use();
			//SHADER CONFIGS
			//TEXTURE BINDING (LIGHTING STUFF)
			//-------------------------------
			shader.setUniformValue<glm::vec3>("u_camerapos", camera.getCameraPosition());
			glm::vec3 directionalLight2(-1.0f, -1.0f, -1.0f);
			shader.setUniformValue<glm::vec3>("u_light.direction", directionalLight2);
			//POINT LIGHT CONFIG
			//------------------
			shader.setUniformValue<glm::vec3>("u_PointLight.position", LightPos);
			shader.setUniformValue<float>("u_PointLight.constant", 1.0f);
			shader.setUniformValue<float>("u_PointLight.linear", 0.07f);
			shader.setUniformValue<float>("u_PointLight.quadratic", 0.017f);
			//shader.setUniform3Float("u_light.ambientStrength", 1.0f, 1.0f, 1.0f);
			//shader.setUniform3Float("u_light.diffuseStrength", 1.0f, 1.0f, 1.0f); // very light
			//shader.setUniform3Float("u_light.specularStrength", 1.0f, 1.0f, 1.0f);
			shader.setUniformValue<float>("u_material.shininess", 32);
			shader.setUniformValue<glm::vec3>("u_viewdirection", camera.getViewDirection());
			shader.setUniformValue<glm::vec3>("u_viewposition", camera.getCameraPosition());
			glm::vec3 ambientlight(0.1f, 0.1f, 0.1f);
			glm::vec3 diffuselight(0.8f, 0.6f, 0.7f);
			glm::vec3 specularlight(1.0f, 1.0f, 1.0f);
			shader.setUniformValue<glm::vec3>("u_light.ambientStrength", ambientlight);
			shader.setUniformValue<glm::vec3>("u_light.diffuseStrength", diffuselight); // darkened
			shader.setUniformValue<glm::vec3>("u_light.specularStrength", specularlight);

		
			glm::mat4 modelMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, -3.0f, 1.0f));
			model.RenderModelWithOutline(shader,camera, modelMatrix,glm::vec3(0.0f,1.0f,0.0f));

		
			//-----------------------------------
			//ANOTHER OBJECT WOHOO
			shader.use();
			glm::mat4 modelY = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, -3.0f, 1.0f));
			shader.setUniformValue<glm::mat4>("view", camera.getViewMatrix());
			shader.setUniformValue<glm::mat4>("projection", camera.getProjectionMatrix());
			shader.setUniformValue<glm::mat4>("model", modelY);
			glm::mat3 normalMatrixSS = glm::transpose(glm::inverse(glm::mat3(modelY)));
			shader.setUniformValue<glm::mat4>("u_normalMatrix", normalMatrixSS);
			model.Draw(shader);
			//-----------------------------------

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