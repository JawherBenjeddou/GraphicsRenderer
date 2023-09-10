#include "Model.h"


// Calls every Draw function in the Mesh class in each of the instances in the vector
void Model::Draw(Shader& shader) {
    for (auto& mesh : m_Meshes) {
        mesh->Draw(shader);
    }
}

// Loads model path and pushes the meshes to the vector
void Model::LoadModel(std::string_view path) {
    Assimp::Importer import;
    const auto * scene = import.ReadFile(path.data(), ASSIMP_LOAD_FLAGS);
    
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
        m_Meshes.push_back(ProcessMesh(mesh,scene));
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
    ExtractVertices(mesh, vertices);
    ExtractIndices(mesh, indices);

    for (size_t i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
    {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, i, &str);
        Texture* Texture_ins = new Texture(str.C_Str(), m_Directory, "texture_diffuse");
        m_Textures.push_back(Texture_ins);
    }
    for (size_t i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); i++)
    {
        aiString str;
        material->GetTexture(aiTextureType_SPECULAR, i, &str);
        Texture* Texture_ins = new Texture(str.C_Str(), m_Directory, "texture_specular");
        m_Textures.push_back(Texture_ins);
    }


   /* auto extractedTextures = ExtractTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(),std::make_move_iterator(extractedTextures.begin()),std::make_move_iterator(extractedTextures.end()));*/
    //ExtractTextures(material, aiTextureType_SPECULAR, textures, "texture_specular");
    
    // Create the Mesh object using std::make_shared
    return std::make_shared<Mesh>(vertices, indices, m_Textures);
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
		
        if (mesh->HasNormals())
        {
            vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        }
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

std::vector <std::shared_ptr<Texture>> Model::ExtractTextures(aiMaterial* mat, aiTextureType type, std::string_view typeName)
{
    std::vector <std::shared_ptr<Texture>> T;
    for (size_t i = 0; i < mat->GetTextureCount(type); i++)
    {
        std::cout << "i = " << i << std::endl;
        aiString str;
        mat->GetTexture(type, i, &str);
        std::shared_ptr<Texture> Texture_ins = std::make_shared<Texture>(str.C_Str(), m_Directory, typeName);
        T.push_back(Texture_ins);
    }
    return T;
}