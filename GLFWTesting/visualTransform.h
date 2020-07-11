#pragma once
#include "Camera.h"
#include "Vector3D.h"
#include "Vector2D.h"

class visualTransform // Static collection of critical tools for performing the perspective transformation
{
public:

	static bool isBehind(Camera c, Vector3D point); // Returns the true/false value indicating whether a given point is behind the camera's normal plane

	static double angleBetweenVectors(Vector3D v1, Vector3D v2); // Returns the angular difference between two vectors in 3D space

	static Vector3D relativize(Vector3D zero, Vector3D relative); // Returns the difference of one vector relative to another

	static Vector2D orthographicTransform(Camera c, Vector3D point); // Big idea of the project: produces an orthographic projection of 3D space according to the camera's orientation.
																		 // Specifically, this returns the 2D charted position where the 3D point ends up in the projection.
	static Vector3D projectVector(Vector3D a, Vector3D b); // Generic linear algebra operation, the projection of vector a onto vector b. Used for adjusting orthographic projections via FOV perspective

	static Vector2D perspectiveStretch(Vector2D ortho, Vector3D vectorProjection); // Adjusted orthographic to perspective based on the length of the acquired vector projection

	static Vector2D transformPoint(Vector3D pointIn, Camera cam); // Consolidated function for applying a perspective transformation on a point according to a camera's parameters
};

