#define _USE_MATH_DEFINES

#include "visualTransform.h"
#include <cmath>

bool visualTransform::isBehind(Camera c, Vector3D point) {
	Vector3D dirVector = c.getDirectionalVector();
	Vector3D relativeVector = relativize(c.position, point);
	double anglebetween = angleBetweenVectors(dirVector, relativeVector);
	if (anglebetween > M_PI / 2) {
		return true;
	}
	return false;
}

double visualTransform::angleBetweenVectors(Vector3D v1, Vector3D v2) {
	return acos(v1.dotProduct(v2) / (v1.Magnitude() * v2.Magnitude())); // Classic LinAlg formula, the dot product over the product of the magnitudes equals to the cos of the angle between.
}

Vector3D visualTransform::relativize(Vector3D zero, Vector3D relative) {
	return Vector3D(relative.x - zero.x, relative.y - zero.y, relative.z - zero.z); // Subtracts each component of the two vectors, zeroing out the relative with respect to the first
}

Vector2D visualTransform::orthographicTransform(Camera c, Vector3D point) {
	// First Relativize the point to be transformed with respect to the camera
	Vector3D relativePoint = visualTransform::relativize(c.position, point);
	// explanation of ortho-transform: a point (x1, y1, z1) around an origin-poisitioned camera with directional angles phi, theta
	// will have an orthographic projection (x2, y2) as follows:
	// x2 = x1*sin(theta) - y*cos(theta)
	// y2 = z1*sin(phi) - y1*cos(phi)*sin(theta) - x1*cos(phi)*cos(theta)
	// I came up with this formula independently (although after taking calc III and linalg), so it's one of my prouder points in this project
	double x2 = relativePoint.x * sin(c.theta) - relativePoint.y * cos(c.theta);
	double y2 = relativePoint.z * sin(c.phi) - relativePoint.y * cos(c.phi) * sin(c.theta) - relativePoint.x * cos(c.phi) * cos(c.theta);
	return Vector2D(x2, y2);
}

Vector3D visualTransform::projectVector(Vector3D a, Vector3D b) {
	// ((a . b) / (b . b)) * b // where . is dotproduct and * is scalar multiply
	double numeratorScalar = a.dotProduct(b);
	double denominatorScalar = b.dotProduct(b);
	double fullScalar = numeratorScalar / denominatorScalar;
	return b.scalarMultiply(fullScalar);
}

Vector2D visualTransform::perspectiveStretch(Vector2D ortho, Vector3D vectorProjection) {
	return ortho.scalarMultiply(1.0 / vectorProjection.Magnitude());
}

Vector2D visualTransform::transformPoint(Vector3D pointIn, Camera cam) {
	Vector3D relativePointIn = relativize(cam.position, pointIn); // Relativize the point in question to the camera
	Vector2D transformedPoint;
	Vector2D ortho = orthographicTransform(cam, pointIn); // Transform the point through the orthographic linear transformation
	Vector2D perspective = perspectiveStretch(ortho, projectVector(relativePointIn, cam.getDirectionalVector())); // Stretch the orthographic transformation to fit the perspective of the camera
	transformedPoint = perspective;
	return transformedPoint;
}