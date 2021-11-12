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
    string type; //string que indica o tipo da transformação (rotate, translate ou scale)
    float x, y, z; // coordenadas para cada transformação
    float angle; //coordenanda extra para a rotação (assume o valor 0 na translação e scale)

  public :
      Transformations();
      Transformations(string t, float px, float py, float pz, float a);
      //void apply();
      string getType();
        float getX();
        float getY();
        float getZ();
        float getAngle();

};

#endif
