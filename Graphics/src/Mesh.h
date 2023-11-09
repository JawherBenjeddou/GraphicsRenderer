#pragma once

#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "GL/glew.h"
#include "DebugUtils.h"
#include "SceneCamera.h"
#include "Texture.h"

#define MAX_BONE_INFLUENCE 4
#define MAX_BONE_WEIGHTS 0x7fffffff

struct VertexInfo {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;

	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;

	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];

};
// = [0.2f, 0.4f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f];


class Mesh {
public:
	
	Mesh(std::vector<VertexInfo> vertices, std::vector<uint32_t> indices, std::vector <Texture>& textures);
		
	void Draw(Shader& shader);

private:
	void SetupMesh();
private:
	// render data
	VAO m_VAO;
	VBO m_VBO;
	EBO m_EBO;

	// mesh data
	std::vector<VertexInfo> m_Vertices;
	std::vector<uint32_t> m_Indices;
	std::vector <Texture>& m_Textures;
};