
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

/*
void Transformations :: apply(){
  if (type == "translate"){
    glTranslatef(this->x,this->y,this->z);
  }
  if (type == "rotate"){
    glRotatef(angle,x,y,z);
  }
  if (type == "scale"){
    glScalef(x,y,z);
  }*/

/*
Transformations :: setX (float x){
  Transformations :: x = x;
}
Transformations :: setY (float y){
  Transformations :: x = x;
}
Transformations :: setX (float x){
  Transformations :: x = x;
}
*/
