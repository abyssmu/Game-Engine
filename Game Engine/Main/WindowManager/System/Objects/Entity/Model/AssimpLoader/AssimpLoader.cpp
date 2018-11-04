#include "AssimpLoader.h"

bool AssimpLoader::LoadModel(
	ID3D11Device* device,
	char* filename,
	std::vector<Mesh*>& meshes,
	int& numMeshes)
{
	const auto scene = aiImportFile(
		filename,
		aiProcessPreset_TargetRealtime_MaxQuality);
	if (!scene)
	{
		return false;
	}

	numMeshes = scene->mNumMeshes;
	meshes.reserve(numMeshes);

	for (auto meshIdx = 0u; (int)meshIdx < numMeshes; ++meshIdx)
	{
		meshes.push_back(new Mesh);
		auto mesh = scene->mMeshes[meshIdx];

		if (!LoadVertices(meshes[meshIdx], mesh))
		{
			return false;
		}

		if (!LoadIndices(meshes[meshIdx], mesh))
		{
			return false;
		}

		meshes[meshIdx]->Initialize(device);
	}

	return true;
}

bool AssimpLoader::LoadIndices(
	Mesh* meshes,
	aiMesh* mesh)
{
	auto faces = mesh->mNumFaces;
	auto indices = std::vector<unsigned long>();

	indices.reserve(faces * 3u);
	for (auto faceIdx = 0u; faceIdx < faces; ++faceIdx)
	{
		indices.push_back(mesh->mFaces[faceIdx].mIndices[0u]);
		indices.push_back(mesh->mFaces[faceIdx].mIndices[1u]);
		indices.push_back(mesh->mFaces[faceIdx].mIndices[2u]);
	}

	meshes->SetIndexCount(faces * 3u);
	meshes->SetIndices(indices);

	return true;
}

bool AssimpLoader::LoadVertices(
	Mesh* meshes,
	aiMesh* mesh)
{
	auto verts = mesh->mNumVertices;
	auto vertices = std::vector<VertexColor*>();

	vertices.reserve(verts);
	for (auto vertIdx = 0u; vertIdx < verts; ++vertIdx)
	{
		auto vert = mesh->mVertices[vertIdx];

		auto hold = new VertexColor;
		hold->color[0] = 0.5;
		hold->color[1] = 0.5;
		hold->color[2] = 0.5;
		hold->color[3] = 1.0;

		hold->position[0] = vert.x;
		hold->position[1] = vert.y;
		hold->position[2] = vert.z;

		vertices.push_back(hold);
	}

	meshes->SetVertexCount(verts);
	meshes->SetVertices(vertices);

	return true;
}