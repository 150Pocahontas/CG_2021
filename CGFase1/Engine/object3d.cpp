#include <stdlib.h>
#include "object3d.h"

using namespace std;

Object3d::Object3d(){
  points;
  tra;
}

Object3d::Object3d(vector<Point> pts, Translation t){
  points = pts;
  tra = t;
}


vector<Point> Object3d::getPoints()
{
  return this->points;
}

void Object3d::setPoints(vector<Point> v)
{
  this->points = v;
}

Translation Object3d::getTranslation()
{
  return this->tra;
}

void Object3d::setTranslation(Translation t)
{
  this->tra = t;
}

void Object3d::addPoint(float x, float y, float z){

  Point p;

  p.x = x;
  p.y = y;
  p.z = z;

  this->points.push_back(p);

}

void Object3d::popPoints()
{
  this->points.pop_back();
}
