#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include<iostream>

#include "ImGuiLayer.h"

#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"




// settings
const uint32_t SCREEN_WIDTH = 800;
const uint32_t SCREEN_HEIGHT = 600;

int main(int argc, char* argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphics", NULL, NULL);
    if (!window)
    {
        std::cerr << " Window creation ERROR";
        glfwTerminate();
        return -1;
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

    Shader shader;

    float vertices[] = {
        // Position (x, y, z)      // Texture Coordinates (s, t)   // Color (r, g, b)
         0.5f,  0.5f, 0.0f,       1.0f, 0.0f,                   0.0f, 1.0f, 1.0f, // bottom right
        -0.5f,  0.5f, 0.0f,       0.0f, 0.0f,                  0.0f, 1.0f, 0.0f, // bottom left
        -0.5f, -0.5f, 0.0f,       0.0f, 1.0f,                  1.0f, 0.0f, 0.0f, // top left
         0.5f, -0.5f, 0.0f,       1.0f, 1.0f,                   0.0f, 0.0f, 1.0f // top right
    };

    unsigned int indices[] = { // note that we start from 0!
     0, 1, 3, // first triangle
     1, 2, 3 // second triangle
    };
    VAO vao;
    EBO ebo(indices, sizeof(indices), 6);
    VBO vbo(vertices, sizeof(vertices));
    // vertex attribute pointers for position (index 0)
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));


    // vertex attribute pointers for texture coordinates (index 2)
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float))));
    GLCall(glEnableVertexAttribArray(2));

    // vertex attribute pointers for color (index 1)
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(5 * sizeof(float))));
    GLCall(glEnableVertexAttribArray(1));
    glm::mat4 test = glm::mat4(1.0f);
    test = glm::translate(test, glm::vec3(1.0f, 1.0f, 1.0f));
    test = glm::rotate(test, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    test = glm::scale(test, glm::vec3(0.5,0.5,0.5));

    //// Print the translation matrix
    //for (int i = 0; i < 4; ++i) {
    //    for (int j = 0; j < 4; ++j) {
    //        std::cout << test[i][j] << " ";
    //    }
    //    std::cout << std::endl;
    //}

    Texture texture("../assets/textures/J.png");
    Texture texturesmile("../assets/textures/face.png");
    texturesmile.Bind(0);
    texture.Bind(1);
    shader.use();
    shader.setUniformInt("texture1", 0);
    shader.setUniformInt("texture2", 1);


    GuiSetup::OnAttach(window);


    

    float x = 0.0f, y = 0.0f, z = 0.0f;
    float x2 = 1.5f, y2 = 1.5f, z2 = 0.0f;
    float f = 0.5f;
    float RotationDegree = 0.0f;
    ImVec4 clear_color = ImVec4(0.39f, 0.22f, 0.39f, 1.00f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
        vao.Bind();
        Renderer::Clear();
        Renderer::Draw(vao, ebo, shader);

        GuiSetup::Begin();
        glm::mat4 translation = glm::mat4(1.0f);

        //// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {

            static int counter = 0;
            shader.setUniformFloat("visibility", f);

            ImGui::Begin("settings");
            ImGui::SliderFloat("visibility", &f, 0.0f, 1.0f);      
            
            ImGui::Text("Translation : ");
            ImGui::SliderFloat("X : ", &x, -1.0f, 1.0f);           
            ImGui::SliderFloat("Y : ", &y, -1.0f, 1.0f);            
            ImGui::SliderFloat("Z : ", &z, -1.0f, 1.0f);  
            // Check if "s" key is pressed
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                // Code to handle "s" key press
                x = x - 0.001;
                // This block will be executed while the "s" key is held down
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                // Code to handle "s" key press
                x = x + 0.001;
                // This block will be executed while the "s" key is held down
            }
            translation = glm::translate(translation, glm::vec3(x, y, z));
            ImGui::Text("Rotation : ");
            ImGui::SliderFloat("Degree : ", &RotationDegree, 0.0f, 360.0f);
            translation = glm::rotate(translation, glm::radians(RotationDegree), glm::vec3(0.0, 0.0, 1.0));
            ImGui::Text("Scaling : ");
            ImGui::SliderFloat("X2 : ", &x2, -1.0f, 1.0f);            
            ImGui::SliderFloat("Y2 : ", &y2, -1.0f, 1.0f);            
            ImGui::SliderFloat("Z2 : ", &z2, -1.0f, 1.0f);
            // Check if "s" key is pressed
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                // Code to handle "s" key press
                x2 = x2 -0.001;
                y2 = y2 -0.001;
                z2 = z2 -0.001;
                // This block will be executed while the "s" key is held down
            }
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                // Code to handle "s" key press
                x2 = x2 + 0.001;
                y2 = y2 + 0.001;
                z2 = z2 + 0.001;
                // This block will be executed while the "s" key is held down
            }
                translation = glm::scale(translation, glm::vec3(x2-0.01, y2-0.01, z2-0.01));

            shader.setUniformMat4f("transform", translation);
            ImGui::Text("Background Color : ");
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        

        GuiSetup::RenderImGuiElements();




        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* poll for and process events */
        glfwPollEvents();

    }


    //CLEANUP 
    GuiSetup::OnDetach();
    glfwTerminate();
    return 0;
}