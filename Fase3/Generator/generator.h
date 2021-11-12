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
void wirePlane(float n);
vector<Point> cone( float raio, float altura, int fatias, int camadas);
vector<Point> box( float largura, float altura, float comprimento, int d);
vector<Point> sphere(float raio, int fatias, int camadas);
vector<Point> plane(float s);
vector<Point> torus(float radius, float width, int stack, int slice);
Point bezierPoint(float t, Point p0, Point p1, Point p2, Point p3);
vector<Point> createBezierSurf(int tess, vector<int> ind, vector<Point> ctrl, int ni, int nv);
vector<Point> teapot(int tess, string file);

#endif
