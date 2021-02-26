#include "RBXMesh.h"

RBXMesh::RBXMesh()
{
}

RBXMesh::RBXMesh(objl::Loader& obj)
{
	FromObj(obj);
}

void RBXMesh::Write(std::ostream& stream)
{
	MeshHeader header
	{
		sizeof(MeshHeader),
		sizeof(MeshVertex),
		sizeof(MeshFace),
		(uint32_t)vertices.size(),
		(uint32_t)faces.size()
	};

	stream << "version 2.00" << std::endl;
	stream.write((char*)&header, sizeof(MeshHeader));
	stream.write((char*)vertices.data(), (std::streamsize)vertices.size() * sizeof(MeshVertex));
	stream.write((char*)faces.data(), (std::streamsize)faces.size() * sizeof(MeshFace));
}

void RBXMesh::FromObj(objl::Loader& obj)
{
	for (auto& vertex : obj.LoadedVertices)
	{
		vertices.push_back(
			MeshVertex
			{
				vertex.Position.X,
				vertex.Position.Y,
				vertex.Position.Z,

				vertex.Normal.X,
				vertex.Normal.Y,
				vertex.Normal.Z,

				vertex.TextureCoordinate.X,
				1.f - vertex.TextureCoordinate.Y, // This is flipped apparently...
				0.f
			}
		);
	}

	for (auto it = obj.LoadedIndices.begin(); it != obj.LoadedIndices.end(); it += 3)
	{
		faces.push_back(
			MeshFace
			{
				*it,
				*(it + 1),
				*(it + 2)
			}
		);
	}
}
