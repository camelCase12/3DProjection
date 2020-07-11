#pragma once
#include <cmath>
#include <vector>

#include "Vector3D.h"
#include "Vector2D.h"
#include "Camera.h"
class CShape
{
public:
	std::vector<Vector3D> vertices;
	std::vector<Vector3D> vertexConnections;
	std::vector<Vector2D> transformedPoints;
	Camera cam;
	std::vector<bool> frontQualifiers;

	bool useBehindCulling = true;
	bool useBehindRendering = true;
	bool drawVertices = true;
	bool drawMeshOutline = true;
	bool drawMesh = true;

	void transform(Camera camIn);

	Vector3D centroid();

	void render();

	CShape(std::vector<Vector3D> vertices, std::vector<Vector3D> vertexConnections);
};

