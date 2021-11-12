#ifndef GENERATOR_GENERATOR_H
#define GENERATOR_GENERATOR_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
typedef struct point {
	float x;
	float y;
	float z;
} Point;


void writePointsFile(string filename, vector<Point> points);
void writePointNormalFile(string filename, vector<Point> points, vector<Point> normals);
void wirePlane(float n);
Point normalizeVec(point v);
vector<Point> cone( float raio, float altura, int fatias, int camadas);
vector<Point> box( float largura, float altura, float comprimento, int d);
vector<Point> spherePoints(float raio, int fatias, int camadas);
vector<Point> sphereNormals(float raio, int fatias, int camadas);
vector<Point> plane(float s);
vector<Point> torusPoints(float radius, float width, int stack, int slice);
vector<Point> torusNormals(float radius, float width, int stack, int slice);
Point bezierPoint(float t, Point p0, Point p1, Point p2, Point p3);
Point bezierTangent(float t, Point p0, Point p1, Point p2, Point p3);
Point vectorProduct(point u, point vector);
vector<Point> createBezierSurf(int tess, vector<int> ind, vector<Point> ctrl, int ni, int nv);
vector<Point> createBezierSurfNormals(int tess, vector<int> ind, vector<Point> ctrl, int ni);
vector<Point> teapotPoints(int tess, string file);
vector<Point> teapotNormals(int tess, string file);

#endif
