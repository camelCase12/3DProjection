#pragma once
#include <vector>
#include "Vector2D.h"

class CRender // contains a buffer of information to be drawn in the upcoming frame
{
public:
	static std::vector<Vector2D> lineStartVertices; // ArrayList like structure to store a dynamic set of lines
	static std::vector<Vector2D> lineEndVertices;
	static void clear();
	static void addLine(Vector2D startPoint, Vector2D endPoint);
};

