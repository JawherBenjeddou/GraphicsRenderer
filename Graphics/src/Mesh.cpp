#include "Mesh.h"

Mesh::Mesh(std::vector<VertexInfo>& vertices, std::vector<uint32_t>& indices, std::vector<Texture>& textures)
	:m_Vertices(vertices),
	 m_Indices(indices),
	 m_Textures(textures)
{
	SetupMesh();
}

void Mesh::Draw(Shader& shader)
{

	uint32_t diffuseNr = 1;
	uint32_t specularNr = 1;
	
	for (int i = 0; i < m_Textures.size(); i++)
	{
		// retrieve texture number (the N in texture_diffuseN)
		m_Textures[i].Bind(i);
		std::string number;
		std::string name = m_Textures[i].getType();
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular")
		{	
			number = std::to_string(specularNr++);
		}

		shader.setUniformInt("u_material."+name+number, i); // ex : material.texutre_diffuseN;
	
	}

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

}


void Mesh::SetupMesh()	
{	
	m_VAO.Bind();
	m_VBO.BufferData(m_Vertices.size() * sizeof(VertexInfo), &m_Vertices[0]);
	m_EBO.BufferData(m_Indices.size() * sizeof(uint32_t), &m_Indices[0]);
	// vertex positions
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	// vertex normals
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)offsetof(VertexInfo, Normal)));
	GLCall(glEnableVertexAttribArray(1));
	// vertex texture coords
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)offsetof(VertexInfo, TexCoords)));
	GLCall(glEnableVertexAttribArray(2));
}
