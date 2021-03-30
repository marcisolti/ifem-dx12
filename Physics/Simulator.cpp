#include "Simulator.h"

#include "HyperelasticFEM.h"
HyperelasticFEM fem;

void Simulator::Update(RenderingSystem* renderer, float dt, bool load)
{
	fem.Step(load);

	// update renderable mesh
	//double scale = 10'000.0;
	double scale = 10.0;
	{
		T += dt;

		// get new pos from the displacements
		std::vector<Float3> positions{ initVertices.size(), { 0,0,0 } };
		for (uint32_t i = 0; i < initVertices.size(); ++i)
		{
			positions[i].x = initVertices[i].position.x + scale * fem.u(3 * i + 0);
			positions[i].y = initVertices[i].position.y + scale * fem.u(3 * i + 1);
			positions[i].z = initVertices[i].position.z + scale * fem.u(3 * i + 2);
			/*
			positions[i].x = fem.x(3*i+0);
			positions[i].y = fem.x(3*i+1);
			positions[i].z = fem.x(3*i+2);
			*/
		}

		// normal computation 
		std::vector<Float3> normals{ initVertices.size(), { 0,0,0 } };
		for (uint32_t i = 0; i < indices.size() / 3; i += 3)
		{

			//int i = 60;
			uint32_t index0 = indices[3 * i + 0];
			uint32_t index1 = indices[3 * i + 1];
			uint32_t index2 = indices[3 * i + 2];

			Float3 a = positions[index0];
			Float3 b = positions[index1];
			Float3 c = positions[index2];

			Float3 ba = b - a;
			Float3 ca = c - a;

			Float3 cross = ba.Cross(ca);
			cross *= 0.5 / cross.Length();
			normals[index0] += cross;
			normals[index1] += cross;
			normals[index2] += cross;

		}

		GG::Geometry::P objMesh = renderer->GetGeometry(id);
		// set data
		for (uint32_t i = 0; i < objMesh->vertices.size(); ++i)
		{
			objMesh->vertices[i].position = positions[i];
			objMesh->vertices[i].normal = normals[i];
		}

		objMesh->SetData(
			reinterpret_cast<const void*>(&(objMesh->vertices[0])),
			objMesh->vertices.size() * sizeof(PNT_Vertex)
		);
	}
}

void Simulator::AddDeformableMesh(
	RenderingSystem* renderer,
	PxSystem* physics,
	const std::string& id,
	ID3D12Device* device,
	const std::string& geoPath,
	const std::string& meshPath
) {
	if (!this->id.empty()) {
		std::cout << "Error! Only 1 deformable mesh allowed (rn)\n";
		std::exit(420);
	}
	else {
		this->id = id;
	}

	// load vega mesh
	{
		std::cout << "loading mesh " << meshPath << '\n';
		std::string path{ "../Media/vega/" };
		path += meshPath;

		VolumetricMesh* mesh = VolumetricMeshLoader::load(path.c_str());

		if (!mesh) {
			std::cout << "fail! terminating\n";
			std::exit(420);
		}
		else {
			std::cout << "success! num elements: "
				<< mesh->getNumElements()
				<< ";  num vertices: "
				<< mesh->getNumVertices() << ";\n";

			fem.Init(mesh);
		}
	}

	// load renderable mesh
	{
		std::vector<PNT_Vertex> vertices;

		ObjLoader loader;
		ObjMesh  mesh = loader.parseFile("../Media/vega/" + geoPath);

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
				uint32_t nIndex = mesh.indices[i].norm[j] - 1;
				uint32_t uvIndex = mesh.indices[i].uv[j] - 1;

				vertices[vIndex].normal = mesh.normals[nIndex];
				vertices[vIndex].tex = mesh.uv[uvIndex];

				indices.push_back(vIndex);
			}
		}

		GG::Geometry::P geometry = GG::Geometry::Create(
			device,
			&(vertices.at(0)),
			(unsigned int)(vertices.size() * sizeof(PNT_Vertex)),
			(unsigned int)sizeof(PNT_Vertex),
			&(indices.at(0)),
			(unsigned int)(indices.size() * sizeof(unsigned int)),
			DXGI_FORMAT_R32_UINT
		);

		initVertices = vertices;
		geometry->vertices = vertices;
		geometry->indices = indices;

		renderer->AddGeometry(device, id, geometry);
		renderer->AddTexture(device, id, "white.png");
		physics->AddRigidBody(id, PxTransform{ 0,0,0 }, PxSphereGeometry(1.f), true);
		physics->RotationModifier(id, {0,1,0}, 3.14156/2);
	}
}