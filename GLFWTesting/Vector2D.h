#pragma once
class Vector2D
{
public:
	double x, y;

	double Magnitude();

	double dotProduct(Vector2D otherVector);

	Vector2D scalarMultiply(double scalar);

	Vector2D(double x, double y);
	Vector2D();
};

