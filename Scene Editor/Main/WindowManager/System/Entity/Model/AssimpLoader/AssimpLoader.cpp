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

	for (std::uint32_t meshIdx = 0u; (int)meshIdx < numMeshes; ++meshIdx)
	{
		//Create a new mesh
		meshes.push_back(new Mesh);

		//Get current mesh
		aiMesh* mesh = scene->mMeshes[meshIdx];

		if (!LoadVertices(meshes, mesh, meshIdx))
		{
			return false;
		}

		if (!LoadIndices(meshes, mesh, meshIdx))
		{
			return false;
		}

		//Initialize mesh
		meshes[meshIdx]->Initialize(device);
	}

	return true;
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Load indices
bool AssimpLoader::LoadIndices(std::vector<Mesh*>& meshes, aiMesh* mesh, std::uint32_t pos)
{
	unsigned int faces;
	std::vector<unsigned long> indices;

	//Get number of vertices and faces
	faces = mesh->mNumFaces;

	//Reserve space in indices
	indices.reserve(faces * 3u);
	for (std::uint32_t faceIdx = 0u; faceIdx < faces; ++faceIdx)
	{
		//Get all three indices of the face
		indices.push_back(mesh->mFaces[faceIdx].mIndices[0u]);
		indices.push_back(mesh->mFaces[faceIdx].mIndices[1u]);
		indices.push_back(mesh->mFaces[faceIdx].mIndices[2u]);
	}

	//Add index counts to mesh
	//Number of indices = 3 * face count
	meshes[pos]->SetIndexCount(faces * 3u);

	//Add indices to mesh
	meshes[pos]->SetIndices(indices);

	return true;
}

//Load vertices
bool AssimpLoader::LoadVertices(std::vector<Mesh*>& meshes, aiMesh* mesh, std::uint32_t pos)
{
	unsigned int verts = 0;
	std::vector<VertexColor*> vertices;

	//Get number of vertices
	verts = mesh->mNumVertices;

	//Reserve space in vertices
	vertices.reserve(verts);
	for (std::uint32_t vertIdx = 0u; vertIdx < verts; ++vertIdx)
	{
		//Get current vertex
		aiVector3D vert = mesh->mVertices[vertIdx];

		//Create VertexColor container and copy information
		VertexColor* hold = new VertexColor;
		hold->color[0] = 0.5;
		hold->color[1] = 0.5;
		hold->color[2] = 0.5;
		hold->color[3] = 1.0;

		hold->position[0] = vert.x;
		hold->position[1] = vert.y;
		hold->position[2] = vert.z;

		//Add holder vertex to vertices vector
		vertices.push_back(hold);
	}

	//Add vertex count to mesh
	meshes[pos]->SetVertexCount(verts);

	//Add vertices to mesh
	meshes[pos]->SetVertices(vertices);

	return true;
}