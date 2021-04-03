#ifndef   ENGINE_TRANSFORMATIONS_H
#define   ENGINE_TRANSFORMATIONS_H
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

class Transformations {
  private :
    string type;
    float x, y, z;

  public :
      Transformations();
      Transformations(string t, float px, float py, float pz);
      void apply();

};

#endif
