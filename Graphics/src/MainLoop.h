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

#include <Windows.h>
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
		Shader Lightshader("../Graphics/shaders/LightFrag.glsl", "../Graphics/shaders/LightVert.glsl");
		SceneCamera camera;
		GameTimer Timer;


		float vertices[] = {
		 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		 -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		 -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
		};
		float text[] = {
			// Texture Coordinates (s, t) 
		   1.0f, 0.0f,
		   0.0f, 0.0f,
		   0.0f, 1.0f,
		   1.0f, 1.0f,
		};

		VAO LightVAO;
		VBO LightVBO;

		LightVBO.BufferData(sizeof(vertices) + sizeof(text), nullptr);

		// Upload vertex data
		LightVBO.BufferSubData(0, sizeof(vertices), vertices);

		// Upload texture coordinate data
		LightVBO.BufferSubData(sizeof(vertices), sizeof(text), text);

		// Set up attribute pointers for vertex positions and texture coordinates
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		LightVAO.Unbind();
		LightVBO.Unbind();

		VAO vao;
		VBO vbo;

		vbo.BufferData(sizeof(vertices) + sizeof(text), nullptr);

		// Upload vertex data
		vbo.BufferSubData(0, sizeof(vertices), vertices);

		// Upload texture coordinate data
		vbo.BufferSubData(sizeof(vertices), sizeof(text), text);

		// Set up attribute pointers for vertex positions and texture coordinates
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		vao.Unbind();
		vbo.Unbind();










		Lightshader.use();
		Lightshader.setUniform3Float("lightColor", 1.0f, 1.0f, 1.0f);
		shader.use();
		shader.setUniform3Float("lightColor", 1.0f, 1.0f, 1.0f);
		shader.setUniform3Float("objectColor", 1.0f, 0.5f, 0.31f);

		GuiSetup::OnAttach(screen.getWindow());

		float f = 1.0f;
		glm::vec4 clear_color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);




		// -----------------------------------------------------------------------------
		//                               Main Loop
		// -----------------------------------------------------------------------------
	


		//Quick Settings
		float sens = 0.1f;
		float rotation = 0.0f;

		//To remove cursor from screen
		glfwSetInputMode(screen.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		while (!glfwWindowShouldClose(screen.getWindow()))
		{
			/* Render here */

			screen.Clear(clear_color);

			GuiSetup::Begin();


			// Object Rendering
			shader.use();
			vao.Bind();
			glm::mat4 model2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shader.setUniformMat4f("view", camera.getViewMatrix());
			shader.setUniformMat4f("projection", camera.getProjectionMatrix());
			shader.setUniformMat4f("model", model2);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));



			// Light Cube Rendering
			Lightshader.use();
			LightVAO.Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 2.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			Lightshader.setUniformMat4f("view", camera.getViewMatrix());
			Lightshader.setUniformMat4f("projection", camera.getProjectionMatrix());
			Lightshader.setUniformMat4f("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));


			// Get current mouse position
			double mouseX, mouseY;
			glfwGetCursorPos(screen.getWindow(), &mouseX, &mouseY);
			glm::vec2 newMousePosition(static_cast<float>(mouseX), static_cast<float>(mouseY));

			// Update camera orientation based on mouse		
			camera.MouseRotation(newMousePosition);
			// Update Keyboard Movement based on the input
			camera.ProcessKeyboardInput(screen.getWindow(), Timer.DeltaTime());



			ImGui::Begin("settings");

			ImGui::SliderFloat("visibility", &f, 0.0f, 1.0f);

			ImGui::SliderFloat("Mouse Sensitivity", &sens, 0.0f, 1.0f);

			camera.setMouseSensitivity(sens);

			Lightshader.setUniformFloat("visibility", f);

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
		//CLEANUP 
		GuiSetup::OnDetach();
	}
}