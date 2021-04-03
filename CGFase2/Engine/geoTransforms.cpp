#include "geoTransforms.h"
using namespace std;

geoTransforms::geoTransforms (){
  points;
}

geoTransforms::geoTransforms (vector<Point> p){
  points = p;
}

vector<Point> geoTransforms::getPoints(){

 return points;

}


  void geoTransforms :: addPoint(float x, float y, float z){
    Point p;
    p.x = x;
    p.y = y;
    p.z = z;
    this->points.push_back(p);
  }

  void geoTransforms :: popPoints(){
    this->points.pop_back();
  }
