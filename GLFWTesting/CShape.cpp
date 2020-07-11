#include "CShape.h"
#include "visualTransform.h"
#include "CRender.h"
#include "frustumClipping.h"


void CShape::transform(Camera camIn) {
	this->cam = camIn;
	transformedPoints.clear();
	frontQualifiers.clear();
	for (int i = 0; i < vertices.size(); i++) {
		transformedPoints.push_back(visualTransform::transformPoint(vertices.at(i), camIn));
		if (visualTransform::isBehind(camIn, vertices[i])) {
			frontQualifiers.push_back(false);
		}
		else {
			frontQualifiers.push_back(true);
		}
	}
}

Vector3D CShape::centroid() {
	double xTotal = 0;
	double yTotal = 0;
	double zTotal = 0;
	double vertexCount = vertices.size();
	for (int i = 0; i < vertexCount; ++i) {
		xTotal += vertices[i].x;
		yTotal += vertices[i].y;
		zTotal += vertices[i].z;
	}
	return Vector3D(xTotal / vertexCount, yTotal / vertexCount, zTotal / vertexCount);
}

void CShape::render() {
	if (drawMeshOutline) {
		for (int i = 0; i < vertexConnections.size(); ++i) {
			Vector3D vertex1 = vertices.at(int(vertexConnections.at(i).x));
			Vector3D vertex2 = vertices.at(int(vertexConnections.at(i).y));
			Vector3D vertex3 = vertices.at(int(vertexConnections.at(i).z));
			Vector2D point1 = transformedPoints.at(int(vertexConnections.at(i).x));
			bool firstInFront = frontQualifiers.at(int(vertexConnections.at(i).x));
			Vector2D point2 = transformedPoints.at(int(vertexConnections.at(i).y));
			bool secondInFront = frontQualifiers.at(int(vertexConnections.at(i).y));
			Vector2D point3 = transformedPoints.at(int(vertexConnections.at(i).z));
			bool thirdInFront = frontQualifiers.at(int(vertexConnections.at(i).z));
            if ((firstInFront && secondInFront) || !useBehindCulling)
            {
                CRender::addLine(point1, point2);
            }
            else if (!firstInFront && secondInFront && useBehindRendering)
            {
                if (frustumClipping::isWithinFrustum(vertex2, cam) || frustumClipping::crossesFrustum(cam, vertex2, vertex1))
                {
                    Vector3D newPoint = frustumClipping::frustumClip(cam, vertex2, vertex1);
                    Vector2D transformedPoint = visualTransform::transformPoint(newPoint, cam);
                    CRender::addLine(transformedPoint, point2);
                }
                else
                {
                }
            }
            else if (firstInFront && !secondInFront && useBehindRendering)
            {
                if (frustumClipping::isWithinFrustum(vertex1, cam) || frustumClipping::crossesFrustum(cam, vertex1, vertex2))
                {
                    Vector3D newPoint = frustumClipping::frustumClip(cam, vertex1, vertex2);
                    Vector2D transformedPoint = visualTransform::transformPoint(newPoint, cam);
                    CRender::addLine(transformedPoint, point1);
                }
                else
                {
                }
            }
            if ((secondInFront && thirdInFront) || !useBehindCulling)
            {
                CRender::addLine(point2, point3);
            }
            else if (!secondInFront && thirdInFront && useBehindRendering)
            {
                if (frustumClipping::isWithinFrustum(vertex3, cam) || frustumClipping::crossesFrustum(cam, vertex3, vertex2))
                {
                    Vector3D newPoint = frustumClipping::frustumClip(cam, vertex3, vertex2);
                    Vector2D transformedPoint = visualTransform::transformPoint(newPoint, cam);
                    CRender::addLine(transformedPoint, point3);
                }
                else
                {
                }
            }
            else if (secondInFront && !thirdInFront && useBehindRendering)
            {
                if (frustumClipping::isWithinFrustum(vertex2, cam) || frustumClipping::crossesFrustum(cam, vertex2, vertex3))
                {
                    Vector3D newPoint = frustumClipping::frustumClip(cam, vertex2, vertex3);
                    Vector2D transformedPoint = visualTransform::transformPoint(newPoint, cam);
                    CRender::addLine(transformedPoint, point2);
                }
                else
                {
                }
            }
            if ((thirdInFront && firstInFront) || !useBehindCulling)
            {
                CRender::addLine(point3, point1);
            }
            else if (!thirdInFront && firstInFront && useBehindRendering)
            {
                if (frustumClipping::isWithinFrustum(vertex1, cam) || frustumClipping::crossesFrustum(cam, vertex1, vertex3))
                {
                    Vector3D newPoint = frustumClipping::frustumClip(cam, vertex1, vertex3);
                    Vector2D transformedPoint = visualTransform::transformPoint(newPoint, cam);
                    CRender::addLine(transformedPoint, point1);
                }
                else
                {
                }
            }
            else if (thirdInFront && !firstInFront && useBehindRendering)
            {
                if (frustumClipping::isWithinFrustum(vertex3, cam) || frustumClipping::crossesFrustum(cam, vertex3, vertex1))
                {
                    Vector3D newPoint = frustumClipping::frustumClip(cam, vertex3, vertex1);
                    Vector2D transformedPoint = visualTransform::transformPoint(newPoint, cam);
                    CRender::addLine(transformedPoint, point3);
                }
                else
                {
                }
            }
		}
	}
}

CShape::CShape(std::vector<Vector3D> vertices, std::vector<Vector3D> vertexConnections) {
	this->vertices = vertices;
	this->vertexConnections = vertexConnections;
}