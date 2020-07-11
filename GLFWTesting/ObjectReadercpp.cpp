#include "ObjectReader.h"
#include <fstream>
#include <iostream>

CShape loadFile(std::string file) {
	std::ifstream shapeLoader;
	shapeLoader.open(file);
	std::vector<std::string> output;
	std::string currentLine;
	while (std::getline(shapeLoader, currentLine)) {
		output.push_back(currentLine);
	}
	shapeLoader.close();
	//actual loading code

	std::vector<Vector3D> vertices;
	std::vector<Vector3D> vertexConnections;
	int vertexCount = stoi(output.at(0));
	int connectionCount = stoi(output.at(1));

	for (int i = 2; i < vertexCount + 2; i++) {
		std::string delimiter = ",";
		std::string currentLine = output.at(i);
		std::string xString = currentLine.substr(0, currentLine.find(delimiter));
		double x = stod(xString);
		currentLine = currentLine.substr(currentLine.find(delimiter) + 1, currentLine.size());
		double y = stod(currentLine.substr(0, currentLine.find(delimiter)));
		currentLine = currentLine.substr(currentLine.find(delimiter) + 1, currentLine.size());
		double z = stod(currentLine);
		vertices.push_back(Vector3D(x, y, z));
	}

	for (int i = vertexCount + 2; i < connectionCount + vertexCount + 2; i++) {
		std::string delimiter = ",";
		std::string currentLine = output.at(i);
		double x = stoi(currentLine.substr(0, currentLine.find(delimiter)));
		currentLine = currentLine.substr(currentLine.find(delimiter) + 1, currentLine.size());
		double y = stoi(currentLine.substr(0, currentLine.find(delimiter)));
		currentLine = currentLine.substr(currentLine.find(delimiter) + 1, currentLine.size());
		double z = stoi(currentLine);
		vertexConnections.push_back(Vector3D(x, y, z));
	}

	CShape loadedShape = CShape(vertices, vertexConnections);
	return loadedShape;
}