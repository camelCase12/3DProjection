#include "ObjectWriter.h"
#include <iostream>
#include <fstream>

void writeFile(CShape shape, std::string file) {
	std::ofstream shapeWriter;
	shapeWriter.open(file);
	//shapeWriter.clear();
	
	int vertexCount = shape.vertices.size();
	int vertexConnectionsCount = shape.vertexConnections.size();

	shapeWriter << std::to_string(vertexCount) + "\n";
	shapeWriter << std::to_string(vertexConnectionsCount) + "\n";

	for (int i = 0; i < vertexCount; i++) {
		shapeWriter << shape.vertices.at(i).x << "," << shape.vertices.at(i).y << "," << shape.vertices.at(i).z << "\n";
	}

	for (int i = 0; i < vertexConnectionsCount; i++) {
		shapeWriter << shape.vertexConnections.at(i).x << "," << shape.vertexConnections.at(i).y << "," << shape.vertexConnections.at(i).z << "\n";
	}

	shapeWriter.close();
}

void createFile(std::string fileName) {
	std::ofstream outfile(fileName);
	outfile.close();
}