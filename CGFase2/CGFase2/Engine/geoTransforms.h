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

using namespace std;

typedef struct point{

  float x;
  float y;
  float z;

} Point;

/*
class Transformation{
  private :
  string type;
//  float angle;
  float x,y,z;

  public :
  Transformation();
  Transformation(string t, float a, float px, float py, float pz);
  string getType();
//  float getAngle();
  float getX();
  float getY();
  float getZ();
}
*/

class geoTransforms{

  private:


      vector<Point> points;
    //  vector<Transformation>

  public:
    geoTransforms();
    geoTransforms(vector<Point> p);
      vector<Point> getPoints();
      void addPoint(float x, float y, float z);
      void popPoints();
};

#endif
