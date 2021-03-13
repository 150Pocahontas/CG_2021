#ifndef GENERATOR_GENERATOR_H
#define GENERATOR_GENERATOR_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
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
vector<Point> cylinder(int s, float h, float r);


#endif
