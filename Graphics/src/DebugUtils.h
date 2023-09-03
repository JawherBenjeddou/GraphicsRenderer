#pragma once

#ifdef _DEBUG
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall())


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
static bool GLLogCall()
{
    while (GLenum error = glGetError())
    {
        std::cerr << "[OpenGL::ERROR] : " << error << std::endl;
        return false;
    }
    return true;
}
#else
    #define GLCall(x) x
#endif

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_FlipUVs)