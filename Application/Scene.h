#pragma once

#include <vector>

struct Point3 {
	double x, y, z;
};

struct Point2 {
	double x, y;
};

struct Vertex {
	Point3 position, normal;
	Point2 uv;
};

struct Transform {
	Point3 position, eulerAngles, scale;
};

enum MaterialType
{
	ALBEDO,
	SHININESS,
	METALNESS
};

struct Material
{
	MaterialType type;
	std::string path;
};

struct Mesh
{
	Transform				transform;
	std::vector<Material>	materials;
	std::vector<Vertex>		vertices;
	std::vector<uint32_t>	indices;
};

struct Scene
{
	std::vector<Mesh> meshes;
};