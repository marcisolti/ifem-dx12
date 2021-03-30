// literally the WORST obj parser/loader. period.
// necessary, because assimp optimizes the mesh
// by reordering the triangles' order
// making it unusable for deformable mesh updates
// pls like and subscribe
#pragma once

#include <Egg/Common.h>
#include <Egg/Math/Math.h>
using namespace Egg::Math;

#include <vector>
#include <chrono>
#include <array>
#include <iostream>
#include <fstream>


struct Index {
	std::array<unsigned int, 3> vert;
	std::array<unsigned int, 3> norm;
	std::array<unsigned int, 3> uv;
};

struct ObjMesh {
	std::vector<Float3> vertices, normals;
	std::vector<Float2> uv;
	std::vector<Index>      indices;
	std::vector<int>		facePtr;
	std::string				mtllib;
	std::vector<std::string> matlist;
};

class ObjLoader {
public:
	ObjLoader() :faceCounter{ 0 } { }

	ObjMesh  parseFile(std::string path)
	{

		std::ifstream file(path);

		if (!file.is_open())
		{
			ASSERT(false, "failed to open file ");
		}
		else
		{
			std::cout << "opened " << path << std::endl;
		}

		auto start = std::chrono::system_clock::now();

		ObjMesh  mesh;
		for (std::string line; std::getline(file, line); )
		{
			parse(line, mesh);
		}
		mesh.facePtr.push_back(faceCounter); // eg. what is this?

		auto end = std::chrono::system_clock::now();
		double time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

		std::cout << "successfully parsed " << path << std::endl;
		return mesh;
	}

private:
	int faceCounter;
	void parse(const std::string& line, ObjMesh& mesh) {
		char temp[8];

		if (line[0] == 'v')
		{
			if (line[1] == 'n')
			{
				Float3 n;
				sscanf(line.c_str(), "%s %f %f %f\n", &temp, &(n.x), &(n.y), &(n.z));
				mesh.normals.push_back(n);
				return;
			}
			else if (line[1] == ' ')
			{
				Float3 v;
				sscanf(line.c_str(), "%s %f %f %f\n", &temp, &(v.x), &(v.y), &(v.z));
				mesh.vertices.push_back(v);
				return;
			}
			else if (line[1] == 't')
			{
				Float2 uv;
				sscanf(line.c_str(), "%s %f %f\n", &temp, &(uv.x), &(uv.y));
				mesh.uv.push_back(uv);
			}
		}
		if (line[0] == 'f')
		{
			faceCounter++;
			Index i;
			sscanf(
				line.c_str(),
				"%s %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&temp,
				&i.vert[0], &i.uv[0], &i.norm[0],
				&i.vert[1], &i.uv[1], &i.norm[1],
				&i.vert[2], &i.uv[2], &i.norm[2]
			);
			mesh.indices.push_back(i);
			return;
		}
		if (line[0] == 'o') {
			std::cout << line << std::endl;
			mesh.facePtr.push_back(faceCounter);
			return;
		}
		/*
		if (line[0] == 'm') {
			char mtllib[256];
			sscanf_s(
				line.c_str(),
				"%s %s",
				&temp, &mtllib
			);

			mesh.mtllib = mtllib;
		}
		if (line[0] == 'u') {
			char mat[256];
			sscanf_s(
				line.c_str(),
				"%s %s",
				&temp, &mat
			);
			mesh.matlist.push_back(mat);
		}
		*/
	}
};