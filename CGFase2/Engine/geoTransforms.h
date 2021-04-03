#ifndef   ENGINE_GEOTRANSFORMS_H
#define   ENGINE_GEOTRANSFORMS_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Transformations.h"

using namespace std;

typedef struct point{

  float x;
  float y;
  float z;

} Point;


class geoTransforms{

  private:

      vector<Point> points;
      vector<Transformations*> transformations;

  public:
    geoTransforms();
    geoTransforms(vector<Point> p, vector<Transformations*> t);
      vector<Point> getPoints();
      vector<Transformations*> getTransformations();
      void addPoint(float x, float y, float z);
      void addTransformations(string t, float px, float py, float pz, float a);
      void popPoints();
       void popTransformations();
};

#endif
