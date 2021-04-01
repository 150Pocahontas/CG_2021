#ifndef OBJECT3D_H
#define OBJECT3D_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

typedef struct point {
	float x;
	float y;
	float z;
}Point;

typedef struct translation{
	float x;
	float y;
	float z;
}Translation;

class Object3d
{

private:
vector<Point> points;
Translation tra;

public:
  Object3d();
  Object3d(vector<Point> pts, Translation t);
vector<Point> getPoints();
Translation getTranslation();
void addPoint(float x, float y, float z);
void popPoints();
void setPoints(vector<Point> v);
void setTranslation(Translation t);
};




#endif //OBJECT3D_H
