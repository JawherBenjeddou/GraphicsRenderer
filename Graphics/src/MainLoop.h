#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include<iostream>

#include "ImGuiLayer.h"

#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "SceneCamera.h"
// settings
static const uint32_t SCREEN_WIDTH = 800;
static const uint32_t SCREEN_HEIGHT = 600;


float DeltaTime = 0.0f; // Time between current frame and last frame
float LastFrame = 0.0f; // Time of last frame



namespace Graphics {


    void Run()
    {
        // -----------------------------------------------------------------------------
        //                             GLFW Initialization
        // -----------------------------------------------------------------------------
        if (!glfwInit())
            return ;
        /* Create a windowed mode window and its OpenGL context */
        auto window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphics", NULL, NULL);
        if (!window)
        {
            std::cerr << " Window creation ERROR";
            glfwTerminate();
            return ;
        }
        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        if (glewInit() != GLEW_OK)
        {
            std::cerr << " Error initializing glew";
        }


        //OPENGL CURRENT VERSION
        const unsigned char* version = glGetString(GL_VERSION);
        std::cout << "OpenGL version: " << version << std::endl;
        
        
        
        //CLASSES INSTANCES
        Shader shader;
        SceneCamera camera;



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


        GuiSetup::OnAttach(window);



        glm::vec3 cubePositions[] =
        {
         glm::vec3(0.0f, 0.0f, -5.0f),
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
        ImVec4 clear_color = ImVec4(0.39f, 0.22f, 0.39f, 1.00f);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // -----------------------------------------------------------------------------
        //                               Main Loop
        // -----------------------------------------------------------------------------
        

        
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */

            GLCall(glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            vao.Bind();
            Renderer::Clear();
            Renderer::Draw(vao, nullptr, shader);
            GuiSetup::Begin();

            //SPAWN MORE CUBES AND ROTATE THEM
            for (size_t i = 0; i < 10; i++)
            {

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
                shader.setUniformMat4f("model", model);
                GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
            }

            //// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {

                camera.processKeyboardInput(window, DeltaTime);

                glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);

                shader.setUniformMat4f("view", camera.getViewMatrix());
                shader.setUniformMat4f("projection", projection);

                ImGui::Begin("settings");
                ImGui::SliderFloat("visibility", &f, 0.0f, 1.0f);


                shader.setUniformFloat("visibility", f);

                ImGui::Text("Background Color : ");
                ImGui::ColorEdit3("clear color",(float*)(&clear_color)); // Edit 3 floats representing a color
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                ImGui::End();
            }


            GuiSetup::RenderImGuiElements();


            float currentFrame = static_cast<float>(glfwGetTime());
            DeltaTime = currentFrame - LastFrame;
            LastFrame = currentFrame;
            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* poll for and process events */
            glfwPollEvents();
            //CALCULATING TIME BETWEEN EACH FRAMES
        }


        //CLEANUP 
        GuiSetup::OnDetach();
        glfwTerminate();
    }
}


