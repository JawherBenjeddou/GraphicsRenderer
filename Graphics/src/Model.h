#pragma once

#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb/stb_image.h"

#include "DebugUtils.h"

class Model
{
public:
	
	Model(char* path)
	{
		LoadModel(path);
	}

	void Draw(Shader& shader);

private:
	void LoadModel(const std::string& path);

	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	void ExtractVertices(aiMesh* mesh, std::vector<VertexInfo>& vertices);

	void ExtractIndices(aiMesh* mesh, std::vector<uint32_t>& indices);

	void ExtractTextures(aiMaterial* mat, aiMesh* mesh, aiTextureType type, std::string Typename, std::vector<Texture>& textures);

private:
	// model data
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;
	
};