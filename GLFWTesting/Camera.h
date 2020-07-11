#pragma once
#include <cmath>
#include "Vector3D.h"

class Camera
{
public:
	bool moveForward = false;
	bool moveBackward = false;
	bool moveRight = false;
	bool moveLeft = false;
	bool lookUp = false;
	bool lookDown = false;
	bool lookRight = false;
	bool lookLeft = false;
	bool moveUp = false;
	bool moveDown = false;
	Vector3D position; // Stores the position of the camera
	double phi; // The phi rotation of the camera's directional vector, from spherical coordinates
	double theta; // The theta rotation of the camera's directional vector, from spherical coordinates
	double FOV; // The field of vision of the camera
	Vector3D outwardPlaneVectors[4];
	void setOutwardPlaneVectors();

	void applyMovement();

	Vector3D getArbitraryDirectionalVector(double theta1, double phi1);
	Vector3D getDirectionalVector(); // Returns the normal vector in the direction the camera is looking

	Camera(double x, double y, double z, double theta, double phi, double FOV); // Sets all paramaters
	Camera(double x, double y, double z, double theta, double phi); // Defaults FOV to PI/2
	Camera() { };
};

