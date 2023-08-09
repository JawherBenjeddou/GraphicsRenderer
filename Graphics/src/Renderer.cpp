#include "Renderer.h"

void Renderer::Draw(const VAO& vao, const EBO* ebo, Shader& shader)
{
    shader.use();
    vao.Bind();

    if (ebo != nullptr && ebo->isValid()) {
        ebo->Bind();
        GLCall(glDrawElements(GL_TRIANGLES, ebo->getCount(), GL_UNSIGNED_INT, 0));
    }
    else {
       // GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    }
}

void Renderer::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}


