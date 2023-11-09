#pragma once

#include <iostream>
#include<memory>
#include <map>
#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb/stb_image.h"

#include "DebugUtils.h"


struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;

};

class Model
{
public:
	
	Model(const char* path)
	{
		LoadModel(path);
	}

	void Draw(Shader& shader);

	void RenderModelWithOutline(Shader& shader,SceneCamera& camera,glm::mat4 modelMatrix,glm::vec3 outlinecolor);

	auto& GetBoneInfoMap() { return m_BoneInfoMap; }

	int& GetBoneCount() { return m_BoneCounter; }

	void SetVertexBoneDataToDefault(VertexInfo& vertex);

	void SetVertexBoneData(VertexInfo& vertex, int boneID, float weight);

	//void ExtractBoneWeightForVertices(std::vector<BoneInfo>& vertices, aiMesh* mesh, const aiScene* scene);

private:
	void LoadModel(std::string_view path);

	void ProcessNode(aiNode* node, const aiScene* scene);

	std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);

	void ExtractVertices(aiMesh* mesh, std::vector<VertexInfo>& vertices);

	void ExtractIndices(aiMesh* mesh, std::vector<uint32_t>& indices);
	
	void ExtractTextures(aiMaterial* mat, std::vector <Texture>& texturescontainer, aiTextureType type, std::string_view typeName);

private:
	// model data
	std::vector<std::shared_ptr<Mesh>> m_Meshes;
	std::string m_Directory;
	int m_BoneCounter = 0;
	std::map<std::string, BoneInfo> m_BoneInfoMap;
	std::vector <Texture> m_Textures;
};