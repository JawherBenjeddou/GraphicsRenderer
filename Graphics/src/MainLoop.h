#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include<iostream>

#include "ImGuiLayer.h"

#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "SceneCamera.h"
#include "GameTimer.h"
#include "Screen.h"



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
        Shader shader;
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


        Texture texture("../assets/textures/J.png");
        Texture texturesmile("../assets/textures/face.png");
        texturesmile.Bind(0);
        texture.Bind(1);
        shader.use();
        shader.setUniformInt("texture1", 0);
        shader.setUniformInt("texture2", 1);


        GuiSetup::OnAttach(screen.getWindow());



        glm::vec3 cubePositions[] =
        {
         glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3(2.0f, 5.0f, -15.0f),
         glm::vec3(-1.5f, -2.2f, -2.5f),
         glm::vec3(-3.8f, -2.0f, -12.3f),
         glm::vec3(2.4f, -0.4f, -3.5f),
         glm::vec3(-1.7f, 3.0f, -7.5f),
         glm::vec3(1.3f, -2.0f, -2.5f),
         glm::vec3(1.5f, 2.0f, -2.5f),
         glm::vec3(1.5f, 0.2f, -1.5f),
         glm::vec3(-1.3f, 1.0f, -1.5f)
        };
       
        float f = 1.0f;
        glm::vec4 clear_color = glm::vec4(0.16f, 0.03f, 0.00f, 0.70f);

        // -----------------------------------------------------------------------------
        //                               Main Loop
        // -----------------------------------------------------------------------------

        float sens = 0.1f;
        float rotation = 0.0f;
        glfwSetInputMode(screen.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        while (!glfwWindowShouldClose(screen.getWindow()))
        {
            /* Render here */
    
            screen.Clear(clear_color);
            vao.Bind();
            GuiSetup::Begin();

            ////SPAWN MORE CUBES AND ROTATE THEM
            for (size_t i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]) * glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(0.0f, 0.0f, 1.0f)) ;
                shader.setUniformMat4f("model", model);
                GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

            }
            // Get current mouse position
            double mouseX, mouseY;
            glfwGetCursorPos(screen.getWindow(), &mouseX, &mouseY);
            glm::vec2 newMousePosition(static_cast<float>(mouseX), static_cast<float>(mouseY));

            // Update camera orientation based on mouse input
            camera.MouseRotation(newMousePosition);

            //// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {

                camera.ProcessKeyboardInput(screen.getWindow(), Timer.DeltaTime());

                shader.setUniformMat4f("view", camera.getViewMatrix());
                shader.setUniformMat4f("projection", camera.getProjectionMatrix());

                ImGui::Begin("settings");
                ImGui::SliderFloat("visibility", &f, 0.0f, 1.0f);
                ImGui::SliderFloat("Mouse Sensitivity", &sens, 0.0f, 1.0f);
                camera.setMouseSensitivity(sens);
                shader.setUniformFloat("visibility", f);

                ImGui::Text("Background Color : ");
                ImGui::ColorEdit3("clear color", (float*)(&clear_color)); // Edit 3 floats representing a color
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                ImGui::End();
            }


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