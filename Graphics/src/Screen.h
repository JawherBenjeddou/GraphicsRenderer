#pragma once

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"


#include "glm/vec4.hpp"
#include "DebugUtils.h"
class Screen {

public:
    Screen(const char* title, int width, int height);

    ~Screen();

    void Clear(glm::vec4 color);

    void Update();

    int getWidth();

    int getHeight();

    GLFWwindow* getWindow();

private:
    void initGL();


private:
    const char* title;
    int width = 500, height = 600;
    GLFWwindow* window;
};