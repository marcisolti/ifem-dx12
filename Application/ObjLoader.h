#pragma once

#include <Egg/Common.h>
#include <Egg/Math/Math.h>

#include <GG/Geometry.h>

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace Egg::Math;

struct Index
{
	uint32_t vert[3];
	uint32_t normal[3];
	uint32_t uv[3];
};

struct ObjMesh {
	std::vector<Float3>		vertices, normals;
	std::vector<Float2>		uv;
	std::vector<Index>      indices;
};

class ObjLoader {
public:
	ObjLoader() { }

	static GG::Geometry* parseFile(ID3D12Device* device, const std::string& path)
	{
		ObjMesh mesh;

		std::ifstream file(path);

		if (!file.is_open())
		{
			std::cout << "failed to open " << path << std::endl;
			std::exit(420);
		}
		else
		{
			std::cout << "opened " << path << std::endl;
		}

		for (std::string line; std::getline(file, line); )
			parse(line, mesh);

		std::vector<PNT_Vertex> vertices;
		std::vector<int>		indices;

		for (const auto& vx : mesh.vertices) {
			PNT_Vertex data;
			data.position = vx;
			vertices.push_back(data);
		}

		for (int i = 0; i < mesh.indices.size(); ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				uint32_t vIndex = mesh.indices[i].vert[j] - 1;
				uint32_t nIndex = mesh.indices[i].normal[j] - 1;
				uint32_t uvIndex = mesh.indices[i].uv[j] - 1;

				vertices[vIndex].normal = mesh.normals[nIndex];
				vertices[vIndex].tex = mesh.uv[uvIndex];

				indices.push_back(vIndex);
			}
		}

		GG::Geometry* geometry = new GG::Geometry(
			device,
			&(vertices.at(0)),
			(unsigned int)(vertices.size() * sizeof(PNT_Vertex)),
			(unsigned int)sizeof(PNT_Vertex),
			&(indices.at(0)),
			(unsigned int)(indices.size() * sizeof(unsigned int)),
			DXGI_FORMAT_R32_UINT
		);

		geometry->vertices = vertices;
		return geometry;
	}

private:

	static void parse(const std::string& line, ObjMesh& mesh)
	{
		std::istringstream stream{ line };

		char c;
		stream >> c;
		if (c == 'v')
		{
			stream >> c;
			if (c == 'n')
			{
				Float3 n;
				stream >> n.x >> n.y >> n.z;
				mesh.normals.push_back(n);
			}
			else if (c == 't')
			{
				Float2 uv;
				stream >> uv.x >> uv.y;
				mesh.uv.push_back(uv);
			}
			else
			{
				stream.putback(c);
				Float3 v;
				stream >> v.x >> v.y >> v.z;
				mesh.vertices.push_back(v);
			}
		}
		else if (c == 'f')
		{
			char c;
			Index i;
			stream >> i.vert[0] >> c >> i.uv[0] >> c >> i.normal[0];
			stream >> i.vert[1] >> c >> i.uv[1] >> c >> i.normal[1];
			stream >> i.vert[2] >> c >> i.uv[2] >> c >> i.normal[2];

			mesh.indices.push_back(i);
		}
	}

};