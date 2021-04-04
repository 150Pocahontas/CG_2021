
#include "geoTransforms.h"
#include "Transformations.h"
#include <cstring>
using namespace std;

Transformations :: Transformations (){
  type;
  angle;
  x;
  y;
  z;
}

Transformations :: Transformations (string t, float px, float py, float pz, float a){
  type = t;
  angle = a;
  x = px;
  y = py;
  z = pz;
}


string Transformations :: getType() {
    return type;
}


float Transformations :: getX() {
    return x;
}

float Transformations :: getY() {
    return y;
}

float Transformations :: getZ() {
    return z;
}

float Transformations :: getAngle() {
    return angle;
}
