#pragma once
class Vector3D {
public:
	double x, y, z;

	double Magnitude();

	double dotProduct(Vector3D otherVector);

	Vector3D scalarMultiply(double scalar);
	Vector3D(double x, double y, double z);
	Vector3D();
};

