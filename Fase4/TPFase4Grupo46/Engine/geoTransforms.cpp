#include "geoTransforms.h"
using namespace std;

geoTransforms::geoTransforms (){
  points;
  transformations;
  cor;
  child;
}

geoTransforms::geoTransforms (vector<Pt> p, vector<Transformations*> t, Color c, vector<geoTransforms*> chi){
  points = p;
  transformations = t;
  cor = c;
  child = chi;
}

vector<Pt> geoTransforms::getPoints(){

 return points;

}

float geoTransforms::getR1(){
 return cor.r1;
}

float geoTransforms::getG1(){
 return cor.g1;
}

float geoTransforms::getB1(){
 return cor.b1;
}

float geoTransforms::getR2(){
 return cor.r2;
}

float geoTransforms::getG2(){
 return cor.g2;
}

float geoTransforms::getB2(){
 return cor.b2;
}

void geoTransforms::setColor(float red1, float gre1, float blu1, float red2, float gre2, float blu2){
  cor.r1 = red1;
  cor.g1 = gre1;
  cor.b1 = blu1;
  cor.r2 = red2;
  cor.g2 = gre2;
  cor.b2 = blu2;
}

vector<Transformations*> geoTransforms :: getTransformations(){
  return transformations;
}

vector<geoTransforms*> geoTransforms :: getChild(){
  return child;
}


  void geoTransforms :: addPoint(float x, float y, float z){
    Pt p;
    p.x = x;
    p.y = y;
    p.z = z;
    this->points.push_back(p);
  }

 // adiciona uma transformação ao vetor das transformações
  void geoTransforms :: addTransformations(Transformations* t){
    transformations.push_back(t);
  }

 //adiciona um grupo filho ao vetor dos grupos filhos
  void geoTransforms :: addChild(geoTransforms* chi){
    this->child.push_back(chi);
  }


  void geoTransforms :: popPoints(){
    this->points.pop_back();
  }
 void geoTransforms :: popTransformations(){
   transformations.pop_back();
 }


void geoTransforms::setShapes(vector<Shape*> pt){
    shapes = pt;
}

vector<Shape*> geoTransforms::getShapes() {
    return shapes;
}