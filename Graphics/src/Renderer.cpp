#include "Renderer.h"

void Renderer::Draw(const VAO& vao, const EBO& ebo, Shader& shader) 
{
    shader.use();
    vao.Bind();
    ebo.Bind();

    //GLCall(glDrawArrays(GL_TRIANGLES,0,3));
    GLCall(glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0));

}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}


