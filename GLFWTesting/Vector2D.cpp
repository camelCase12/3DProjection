#include "Vector2D.h"
#include <cmath>

double Vector2D::Magnitude() {
	return sqrt(x * x + y * y);
}

double Vector2D::dotProduct(Vector2D otherVector) {
	return x * otherVector.x + y * otherVector.y;
}

Vector2D Vector2D::scalarMultiply(double scalar) {
	return Vector2D(x * scalar, y * scalar);
}

Vector2D::Vector2D(double x, double y) {
	this->x = x;
	this->y = y;
}
Vector2D::Vector2D() { x = NULL; y = NULL; }