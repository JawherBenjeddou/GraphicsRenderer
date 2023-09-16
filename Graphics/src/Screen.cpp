#include "screen.h"

Screen::Screen(std::string_view title, int width, int height):
    title(title.data()),
    width(width),
    height(height)
{
    if (!glfwInit())
        return;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
    if (!window)
    {
        std::cerr << " Window creation ERROR";
        glfwTerminate();
        return;
    }
    initGL();
}

Screen::~Screen() {
    glfwTerminate();
}

void Screen::initGL() {
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cerr << " Error initializing glew";
    }

    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    //glEnable(GL_CULL_FACE); //skipping the rendering of certain faces of 3D objects that are not visible
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //glDepthFunc(GL_ALWAYS);
   // glEnable(GL_BLEND);
    //glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glDepthMask(GL_FALSE);
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
} 

void Screen::Clear(glm::vec4& color) {
    glClearStencil(0);  //sets the clear value for the stencil buffer to zero.
    GLCall(glClearColor(color.x, color.y,color.z, color.w));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

void Screen::Update() {


    glfwSwapBuffers(window);
    //glStencilFunc(GL_LESS, 1, 0x00);
}

int Screen::getWidth() {
    return width;
}

int Screen::getHeight() {
    return height;
}

GLFWwindow* Screen::getWindow()
{
    return window;
}