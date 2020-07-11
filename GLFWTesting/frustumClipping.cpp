#include "frustumClipping.h"
#include "visualTransform.h"
#include <cmath>

Vector3D frustumClipping::frustumClip(Camera c, Vector3D frontpoint, Vector3D backpoint) {

    Vector3D pointOnPlane = c.position;
    c.setOutwardPlaneVectors(); // potential optimization: this need only be called once per frame, but is probably called many times

    Vector3D pointOnLine = backpoint;
    Vector3D lineDefinition = visualTransform::relativize(frontpoint, backpoint);
    Vector3D intersections[] = { frustumClipping::intersectLineWithPlane(pointOnPlane, c.outwardPlaneVectors[0], pointOnLine, lineDefinition),
                                 frustumClipping::intersectLineWithPlane(pointOnPlane, c.outwardPlaneVectors[1], pointOnLine, lineDefinition),
                                 frustumClipping::intersectLineWithPlane(pointOnPlane, c.outwardPlaneVectors[2], pointOnLine, lineDefinition),
                                 frustumClipping::intersectLineWithPlane(pointOnPlane, c.outwardPlaneVectors[3], pointOnLine, lineDefinition)};
    Vector3D bestIntersection = intersections[0];
    for (int i = 0; i < sizeof(intersections); ++i) {
        if (greaterClip(c, intersections[i], bestIntersection, backpoint, frontpoint, i, i - 1)) {
            bestIntersection = intersections[i];
        }
    }
    return bestIntersection;
}

Vector3D frustumClipping::intersectLineWithPlane(Vector3D pointOnPlane, Vector3D planeNormal, Vector3D pointOnLine, Vector3D lineDefinition) {
    Vector3D planeLineDifference = visualTransform::relativize(pointOnLine, pointOnPlane);
    if ((lineDefinition.dotProduct(planeNormal)) == 0) {
        return Vector3D(0, 0, 0); // This implies that there is no intersection, may require custom programming, though returning a false value will work in most circumstances
    }
    double lineParameter = planeNormal.dotProduct(planeLineDifference) / (lineDefinition.dotProduct(planeNormal));
    Vector3D linePosition = lineDefinition.scalarMultiply(lineParameter);
    Vector3D intersection = Vector3D(linePosition.x + pointOnLine.x, linePosition.y + pointOnLine.y, linePosition.z + pointOnLine.z);
    return intersection;
}

bool frustumClipping::isWithinFrustum(Vector3D point1, Camera c) {
    if (!frustumClipping::isInFront(c, point1)) {
        return false;
    }

    Vector2D transform = visualTransform::transformPoint(point1, c);
    if (abs(transform.x) > 1) {
        return false;
    }
    if (abs(transform.y) > 1) {
        return false;
    }
    return false;
}

bool frustumClipping::greaterClip(Camera c, Vector3D point1, Vector3D point2, Vector3D backpoint, Vector3D frontpoint, int planeIndex1, int planeIndex2) {
	//omitted null checks, may need to hard program
	double lineLength = visualTransform::relativize(backpoint, frontpoint).Magnitude();

	double point1BackDistance = visualTransform::relativize(backpoint, point1).Magnitude();
	double point1FrontDistance = visualTransform::relativize(frontpoint, point1).Magnitude();
	double point1SumDistance = point1BackDistance + point1FrontDistance;
	double lineLengthError1 = abs(lineLength - point1SumDistance);

	double point2BackDistance = visualTransform::relativize(backpoint, point2).Magnitude();
	double point2FrontDistance = visualTransform::relativize(frontpoint, point2).Magnitude();
	double point2SumDistance = point2BackDistance + point2FrontDistance;
	double lineLengthError2 = abs(lineLength - point2SumDistance);

    if (lineLengthError1 >= 0.000001) // lineLengthError code is for determining whether the intersection point lies on the line in question
    {
        return false;
    }
    if (lineLengthError2 >= 0.000001)
    {
        return true;
    }
    if (frustumClipping::isInFront(c, point1))
    {
        if (!frustumClipping::isInFront(c, point2))
        {
            return true;
        }
        if (point1BackDistance < point2BackDistance)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool frustumClipping::crossesFrustum(Camera c, Vector3D frontpoint, Vector3D backpoint) {
    Vector3D pointOnPlane = c.position;
    c.setOutwardPlaneVectors();
    Vector3D pointOnLine = backpoint;
    Vector3D lineDefinition = visualTransform::relativize(backpoint, frontpoint);
    Vector3D intersections[] = { frustumClipping::intersectLineWithPlane(pointOnPlane, c.outwardPlaneVectors[0], pointOnLine, lineDefinition),
                                 frustumClipping::intersectLineWithPlane(pointOnPlane, c.outwardPlaneVectors[1], pointOnLine, lineDefinition),
                                 frustumClipping::intersectLineWithPlane(pointOnPlane, c.outwardPlaneVectors[2], pointOnLine, lineDefinition),
                                 frustumClipping::intersectLineWithPlane(pointOnPlane, c.outwardPlaneVectors[3], pointOnLine, lineDefinition)};
    bool isInFrustum = frustumClipping::isWithinFrustum(frontpoint, c);
    int frontFrustumCrosses = 0;
    for (int i = 0; i < sizeof(intersections); ++i) {
        double lineLength = visualTransform::relativize(backpoint, frontpoint).Magnitude();
        double pointBackDistance = visualTransform::relativize(backpoint, intersections[i]).Magnitude();
        double pointFrontDistance = visualTransform::relativize(frontpoint, intersections[i]).Magnitude();
        double pointSumDistance = pointBackDistance + pointFrontDistance;
        double lineLengthError = abs(lineLength - pointSumDistance);
        if (isInFront(c, intersections[i]) && lineLengthError < 0.000001) {
            frontFrustumCrosses++;
        }
    }
    if (frontFrustumCrosses >= 1) {
        return true;
    }
    return false;
}

bool frustumClipping::isInFront(Camera c, Vector3D v) {
	Vector3D outwardNearPlaneNormal = c.getDirectionalVector().scalarMultiply(-1);
	Vector3D pointRelativeToCamera = visualTransform::relativize(c.position, v);

	if (pointRelativeToCamera.dotProduct(outwardNearPlaneNormal) > 0) {
		return false;
	}
	return true;
}