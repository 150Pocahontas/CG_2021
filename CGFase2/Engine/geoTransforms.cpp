#include "geoTransforms.h"
using namespace std;

geoTransforms::geoTransforms (){
  points;
  transformations;
}

geoTransforms::geoTransforms (vector<Point> p, vector<Transformations*> t){
  points = p;
  transformations = t;
}

vector<Point> geoTransforms::getPoints(){

 return points;

}
vector<Transformations*> geoTransforms :: getTransformations(){
  return transformations;
}


  void geoTransforms :: addPoint(float x, float y, float z){
    Point p;
    p.x = x;
    p.y = y;
    p.z = z;
    this->points.push_back(p);
  }

  void geoTransforms :: addTransformations(string t, float px, float py, float pz, float a){

    Transformations* trans =  new Transformations(t,px,py,pz,a);
    transformations.push_back(trans);
  }

  void geoTransforms :: popPoints(){
    this->points.pop_back();
  }
 void geoTransforms :: popTransformations(){
   transformations.pop_back();
 }
