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
		Screen screen("Graphics", 1200, 900);

		// -----------------------------------------------------------------------------
		//                             Classes Initialization
		// -----------------------------------------------------------------------------
		Shader shader("../Graphics/shaders/Frag.glsl", "../Graphics/shaders/Vert.glsl");
		Shader Lightshader("../Graphics/shaders/LightFrag.glsl", "../Graphics/shaders/LightVert.glsl");
		SceneCamera camera;
		GameTimer Timer;
	

		float Lightvertices[]{
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};
		float vertices[] = {
			// positions // normals // texture coords
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //bottom left
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, //bottom right
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, //top right
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, //top right
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top right
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //bottom left
			
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};
		//OBJECTS SHADER
		//--------------
		VAO vao;
		VBO vbo;
		vbo.BufferData(sizeof(vertices), vertices);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		vao.Unbind();
		vbo.Unbind();
		//LIGHT SHADER
		//------------ 
		VAO LightVAO; 
		VBO LightVBO;
		LightVBO.BufferData(sizeof(Lightvertices) , Lightvertices);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		LightVAO.Unbind();
		LightVBO.Unbind();


		Lightshader.use();
		Lightshader.setUniform3Float("lightColor", 1.0f, 1.0f, 1.0f);

		shader.use();
		shader.setUniform3Float("lightColor", 1.0f, 1.0f, 1.0f);
		shader.setUniform3Float("objectColor", 1.0f, 0.5f, 0.31f);
		
		
		GuiSetup::OnAttach(screen.getWindow());

		glm::vec4 clear_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

		// -----------------------------------------------------------------------------
		//                               Main Loop
		// -----------------------------------------------------------------------------
		Texture texture("../assets/textures/container2.png");
		Texture texture2("../assets/textures/container2_specular.png");
		texture.Bind(0);
		//texture2.Bind(1);
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
			glm::vec3 lightColor;
			lightColor.x = 1.0f;
			lightColor.y = 1.0f;
			lightColor.z = 1.0f;
			glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
			glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
			//glm::vec3 result = diffuseColor + ambientColor + lightColor;
			// Light Cube Rendering
			Lightshader.use();
			LightVAO.Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), LightPos) * glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			Lightshader.setUniformMat4f("view", camera.getViewMatrix());
			Lightshader.setUniformMat4f("projection", camera.getProjectionMatrix());
			Lightshader.setUniformMat4f("model", model);
			Lightshader.setUniform3Float("light.color", 1.0f, 1.0f, 1.0f);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			// Object Rendering (Cube)
			shader.use();
			vao.Bind();
			glm::mat4 model2 = glm::translate(glm::mat4(1.0f),Position2) * glm::rotate(glm::mat4(1.0f), /*static_cast<float>(glfwGetTime()) * */0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			shader.setUniform3Float("light.position", LightPos.x,LightPos.y,LightPos.z);
			shader.setUniform3Float("camerapos",camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);
			shader.setUniformMat4f("view", camera.getViewMatrix());
			shader.setUniformMat4f("projection", camera.getProjectionMatrix());
			shader.setUniformMat4f("model", model2);

			shader.setUniform3Float("material.ambient", 0.25f, 0.20725f, 0.20725f);

			//TEXTURE BINDING
			shader.setUniformInt("material.diffuseMAP",0);


			shader.setUniform3Float("material.specular", 0.296648f, 0.296648f, 0.296648f);
			shader.setUniformFloat("material.shininess", 32);
			
			shader.setUniform3Float("light.ambientStrength", 0.2f, 0.2f, 0.2f);
			shader.setUniform3Float("light.diffuseStrength", 0.7f, 0.5f, 0.5f); // darkened
			shader.setUniform3Float("light.specularStrength", 1.0f, 1.0f, 1.0f);
			//shader.setUniform3Float("light.ambientStrength", 1.0f, 1.0f, 1.0f);
			//shader.setUniform3Float("light.diffuseStrength", 1.0f, 1.0f, 1.0f); // very light
			//shader.setUniform3Float("light.specularStrength", 1.0f, 1.0f, 1.0f);

			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model2)));
			shader.setUniformMat4f("normalMatrix", normalMatrix);
			// Object Rendering (Ground)
			glm::mat4 modelground = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 3.0f)) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 1.0f, 10.0f));
			shader.setUniformMat4f("view", camera.getViewMatrix());
			shader.setUniformMat4f("projection", camera.getProjectionMatrix());
			shader.setUniformMat4f("model", modelground);
			shader.setUniform3Float("material.ambient", 0.05375f, 0.05f, 0.06625f);
			shader.setUniform3Float("material.specular", 0.332741f, 0.328634f, 0.346435f);
			shader.setUniformFloat("material.shininess", 38.4f);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		

		
			//OBJECT TEMPORARY MOVEMENT
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
				LightPos.y += 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
				LightPos.y -= 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
				LightPos.x -= 0.1f;
			if (glfwGetKey(screen.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
				LightPos.x += 0.1f;
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