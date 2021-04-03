
#include "geoTransforms.h"
#include "Transformations.h"
#include <cstring>
using namespace std;

Transformations :: Transformations (){
  type;
  //angle;
  x;
  y;
  z;
}

Transformations :: Transformations (string t, float px, float py, float pz){
  type = t;
  //angle = a;
  x = px;
  y = py;
  z = pz;
}

void Transformations :: apply(){
  if (type == "translate"){
    glTranslatef(x,y,z);
  }/*
  if (type == "rotate"){
    glRotatef(angle,x,y,z);
  }
  if (type == "scale"){
    glScalef(x,y,z);
  }*/
}
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
