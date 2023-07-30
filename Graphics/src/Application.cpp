#include<iostream>
#include "Shader.h"
#include "GLFW/glfw3.h"







int main(int argc, char* argv[])
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cerr << " Error initializing glew";
    }


    Shader shader("src/Vert.glsl", "src/Frag.glsl");
    //OPENGL CURRENT VERSION
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "OpenGL version: " << version << std::endl;
    // Positions and Colors
    float positions[8] = {
        -0.5f, 0.5f,
         0.5f, 0.5f,
         0.5f, -0.5f,
         -0.5f, -0.5f
    };
    uint32_t indices[6] = {
          0,1,2,     //First Triangle
          2,3,0     //second Triangle
    };
    float colors[24] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    //GENERATE ARRAY OBJECT
    uint32_t VAO;

    uint32_t IndexBuffer;

    uint32_t buffer;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBindVertexArray(VAO);
    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
        GL_STATIC_DRAW);

    // Combine position and color data into a single buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(colors), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(colors), colors);

    // Vertex Attribute Pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(sizeof(float) * 8));

    // Enable Attribute Arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //UNBIND THE VERTEX ARRAY
    glBindVertexArray(0);




    glBindVertexArray(VAO);




  
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
       
        glBindVertexArray(VAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // Draw the triangle
        glBindVertexArray(0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}