//AssimpLoader class
//Interface to assimp library

#include "AssimpLoader.h"

//Default constructor
AssimpLoader::AssimpLoader()
{}

//Default copy constructor
AssimpLoader::AssimpLoader(const AssimpLoader& other)
{}

//Default destructor
AssimpLoader::~AssimpLoader()
{}

//Load model from file
bool AssimpLoader::LoadModel(ID3D11Device* device, char* filename,
							std::vector<Mesh*>& meshes, int& numMeshes)
{
	//Create scene from file
	//Captures all meshes in scene
	const aiScene* scene = aiImportFile(filename,
		aiProcessPreset_TargetRealtime_MaxQuality);
	if (!scene)
	{
		return false;
	}

	//Get number of meshes in scene
	numMeshes = scene->mNumMeshes;

	//Reserve space in meshes
	meshes.reserve(numMeshes);

	for (std::uint32_t meshIdx = 0u; meshIdx < numMeshes; ++meshIdx)
	{
		//Create a new mesh
		meshes.push_back(new Mesh);

		//Get current mesh
		aiMesh* mesh = scene->mMeshes[meshIdx];
		std::vector<unsigned long> indices;
		std::vector<VertexTypeColor*> vertices;

		unsigned int verts, faces;

		//Get number of vertices and faces
		verts = mesh->mNumVertices;
		faces = mesh->mNumFaces;

		//Add verts and inds counts to mesh
		//Number of indices = 3 * face count
		meshes[meshIdx]->SetIndexCount(faces * 3u);
		meshes[meshIdx]->SetVertexCount(verts);

		//Reserve space in vertices
		vertices.reserve(verts);
		for (std::uint32_t vertIdx = 0u; vertIdx < verts; ++vertIdx)
		{
			//Get current vertex
			aiVector3D vert = mesh->mVertices[vertIdx];
			
			//Create VertexTypeColor container and copy information
			VertexTypeColor* hold = new VertexTypeColor;
			hold->color[0] = 0.5f;
			hold->color[1] = 0.5f;
			hold->color[2] = 0.5f;
			hold->color[3] = 1.0f;

			hold->position[0] = vert.x;
			hold->position[1] = vert.y;
			hold->position[2] = vert.z;

			//Add holder vertex to vertices vector
			vertices.push_back(hold);
		}

		//Reserve space in indices
		indices.reserve(faces * 3u);
		for (std::uint32_t faceIdx = 0u; faceIdx < faces; ++faceIdx)
		{
			//Get all three indices of the face
			indices.push_back(mesh->mFaces[faceIdx].mIndices[0u]);
			indices.push_back(mesh->mFaces[faceIdx].mIndices[1u]);
			indices.push_back(mesh->mFaces[faceIdx].mIndices[2u]);
		}

		//Add indices and vertices to mesh
		meshes[meshIdx]->SetIndices(indices);
		meshes[meshIdx]->SetVertices(vertices);

		//Initialize mesh
		meshes[meshIdx]->Initialize(device);
	}

	return true;
}