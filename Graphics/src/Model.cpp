#include "Model.h"


// Calls every Draw function in the Mesh class in each of the instances in the vector
void Model::Draw(Shader& shader) {
    for (const auto& mesh : m_Meshes) {
        mesh->Draw(shader);
    }
}

// Loads model path and pushes the meshes to the vector
void Model::LoadModel(const std::string& path) {
    Assimp::Importer import;
    const auto * scene = import.ReadFile(path, ASSIMP_LOAD_FLAGS);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << "\n";
        return; // Return false on error
    }

    m_Directory = path.substr(0, path.find_last_of('/'));
    auto* rootNode = scene->mRootNode;
    ProcessNode(rootNode, scene);

}

void Model::ProcessNode(aiNode* rootNode, const aiScene* scene) {
    // Process all the node’s meshes (if any)
    for (size_t i = 0; i < rootNode->mNumMeshes; i++) {
        auto* mesh = scene->mMeshes[rootNode->mMeshes[i]];
        std::shared_ptr<Mesh> meshData = ProcessMesh(mesh, scene);
        
        if (meshData) {
            m_Meshes.push_back(meshData);
        }
    }

    // Then the same for each of its children
    for (size_t i = 0; i < rootNode->mNumChildren; i++) {
        ProcessNode(rootNode->mChildren[i], scene);
    }
}

// Split ProcessMesh() function into multiple smaller functions for easier readability
std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    auto* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<VertexInfo> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;

    ExtractVertices(mesh, vertices);
    ExtractIndices(mesh, indices);

    // Extracting Textures with different types and populating the Textures Container
    ExtractTextures(material, mesh, aiTextureType_DIFFUSE, "texture_diffuse", textures);
    ExtractTextures(material, mesh, aiTextureType_SPECULAR, "texture_specular", textures);

    // Create the Mesh object using std::make_shared
    return std::make_shared<Mesh>(vertices, indices, textures);
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
			indices.push_back(face.mIndices[j]);

	}
}

// Extract texture data from the mesh and populate the textures vector.
void Model::ExtractTextures(aiMaterial* mat,aiMesh* mesh, aiTextureType type,std::string Typename, std::vector<Texture>& textures)
{
	
	for (size_t count = 0; count < mat->GetTextureCount(type); count++)
	{
		aiString str;
		mat->GetTexture(type, count, &str);
        std::string filename = m_Directory + '/' + std::string(str.C_Str());
		textures.push_back(std::move(Texture(filename.c_str(), Typename)));
	}
}