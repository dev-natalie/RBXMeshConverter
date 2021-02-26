#pragma once

#include "OBJ_Loader.h"

class RBXMesh
{
private:
	struct MeshHeader
	{
		uint16_t headerSize;
		uint8_t vertexSize;
		uint8_t faceSize;
		uint32_t vertexCount;
		uint32_t faceCount;
	};
public:
	struct MeshVertex
	{
		float vx, vy, vz;
		float nx, ny, nz;
		float tu, tv, tw;
	};

	struct MeshFace
	{
		uint32_t a, b, c;
	};

	std::vector<MeshVertex> vertices;
	std::vector<MeshFace> faces;

	RBXMesh();
	RBXMesh(objl::Loader& obj);

	void Write(std::ostream& stream);
	void FromObj(objl::Loader& obj);
};
