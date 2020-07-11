#define _USE_MATH_DEFINES

#include "Camera.h"
#include <cmath>

void Camera::setOutwardPlaneVectors() {
	Vector3D leftNormal = getArbitraryDirectionalVector(theta + FOV / 2 + M_PI / 2,
														M_PI / 2);
	Vector3D topNormal = getArbitraryDirectionalVector(theta,
													   phi - FOV / 2 - M_PI / 2);
	Vector3D rightNormal = getArbitraryDirectionalVector(theta - FOV / 2 - M_PI / 2,
														 M_PI / 2);
	Vector3D bottomNormal = getArbitraryDirectionalVector(theta,
														  phi + FOV / 2 + M_PI / 2);
	outwardPlaneVectors[0] = leftNormal;
	outwardPlaneVectors[1] = topNormal;
	outwardPlaneVectors[2] = rightNormal;
	outwardPlaneVectors[3] = bottomNormal;
}

Vector3D Camera::getDirectionalVector() {
	double x = sin(phi) * cos(theta);
	double y = sin(phi) * sin(theta);
	double z = cos(phi);
	return Vector3D(x, y, z);
}

void Camera::applyMovement() {
	if (moveForward) {
		position.x += .03 * cos(theta);
		position.y += .03 * sin(theta);
	}
	if (moveLeft) {
		position.x -= .03 * sin(theta);
		position.y += .03 * cos(theta);
	}
	if (moveRight) {
		position.x += .03 * sin(theta);
		position.y -= .03 * cos(theta);
	}
	if (moveBackward) {
		position.x -= .03 * cos(theta);
		position.y -= .03 * sin(theta);
	}
	if (lookUp) {
		phi -= 0.01;
	}
	if (lookLeft) {
		theta += 0.01;
	}
	if (lookRight) {
		theta -= 0.01;
	}
	if (lookDown) {
		phi += 0.01;
	}
	if (moveUp) {
		position.z += 0.03;
	}
	if (moveDown) {
		position.z -= 0.03;
	}
}

Vector3D Camera::getArbitraryDirectionalVector(double theta1, double phi1) {
	double x = sin(phi1) * cos(theta1);
	double y = sin(phi1) * sin(theta1);
	double z = cos(phi1);
	return Vector3D(x, y, z);
}

Camera::Camera(double x, double y, double z, double theta, double phi, double FOV) {
	position = Vector3D(x, y, z);
	this->theta = theta;
	this->phi = phi;
	this->FOV = FOV;
}

Camera::Camera(double x, double y, double z, double theta, double phi) {
	position = Vector3D(x, y, z);
	this->theta = theta;
	this->phi = phi;
	this->FOV = M_PI;
}