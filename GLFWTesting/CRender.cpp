#include "CRender.h"

std::vector<Vector2D> CRender::lineEndVertices;
std::vector<Vector2D> CRender::lineStartVertices;

void CRender::clear() {
	lineStartVertices.clear();
	lineEndVertices.clear();
}

void CRender::addLine(Vector2D startPoint, Vector2D endPoint) {
	lineStartVertices.push_back(startPoint);
	lineEndVertices.push_back(endPoint);
}