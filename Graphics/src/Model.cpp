#include "Model.h"

//Calls Every Draw function in the Mesh class in each of the instances in the vector
void Model::Draw(Shader& shader)
{
	for (size_t i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes[i].Draw(shader);
	}
}

//Loads model path and pushes the meshes to the vector
void Model::LoadModel(std::string path)
{
	Assimp::Importer import;
	const auto* scene = import.ReadFile(path,ASSIMP_LOAD_FLAGS);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << "\n";
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));
	auto* RootNode = scene->mRootNode;
	ProcessNode(RootNode, scene);
}

void Model::ProcessNode(aiNode* RootNode, const aiScene* scene)
{
	// process all the node’s meshes (if any)
	for (size_t i = 0; i < RootNode->mNumMeshes; i++)
	{
		auto* mesh = scene->mMeshes[RootNode->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}
	
	// then do the same for each of its children
	for (size_t i = 0; i < RootNode->mNumChildren; i++)
	{
		ProcessNode(RootNode->mChildren[i], scene);
	}
	
}


//TODO :  split ProcessMesh() function into multiple smaller functions for easier readability
Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<VertexInfo> Vertices;
	std::vector<uint32_t> Indices;
	std::vector<Texture> TextureContainer;
	


	//TODO : FIGURE OUT HOW TO ADD THE TEXTURES TO THE CLASS
	//Setting up the textures 
	

}

// Extract vertex data from the mesh and populate the vertices vector.
void Model::ExtractVertices(aiMesh* mesh, std::vector<VertexInfo>& vertices)
{
	//Setting up Vertices (Positins,Normals,TexCoords)
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		VertexInfo vertex;

		//direct assignment 
		vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		// Checking if the mesh has texture coordinates before accessing them
		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f); // Setting default texture coordinates if not available
		}

		vertices.push_back(vertex);
	}
	
}

// Extract index data from the mesh and populate the indices vector.
void Model::ExtractIndices(aiMesh* mesh, std::vector<uint32_t>& indices)
{
	//Setting up the indices
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (size_t j = 0; j < face.mNumIndices; j++)
			Indices.push_back(face.mIndices[j]);

	}
}

// Extract texture data from the mesh and populate the textures vector.
void Model::ExtractTextures(aiMesh* mesh, std::vector<Texture>& textures)
{
	
}