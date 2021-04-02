#ifndef ENGINE_GEOTRANSFORM_H
#define ENGINE_GEOTRANSFORM_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
using namespace std;

class Point {
    private:
        float x, y, z;

    public:
        Point();
        Point(float px, float py, float pz);
        float getX();
        float getY();
        float getZ();
};


class Shape {
    private:
        vector<Point*> points;

    public:
        Shape();
        Shape(vector<Point*> p);
        vector<Point*> getPoints();
        int getSize();
};

class Transformation {

    private:
        string type;
        float angle, x, y, z;

    public:
        Transformation();
        Transformation(string t, float a, float xx, float yy, float zz);
        string getType();
        void setType( string type);
        float getX();
        void setX(float x);
        float getY();
        void setY(float y);
        float getZ();
        void setZ(float z);
        float getAngle();
        void setAngle(float angle);
        void apply();
};
/*
class Tipo : public Transformation{
private :
    string tipo;
public:
    Tipo();
    void apply(int *linha);
     void setTipo(const string type);
};
*/
class Group {
    private:
        vector<Group*> groups;
        vector<Transformation*> trans;
        vector<Shape*> shapes;

    public:
        Group();
        void addGroup(Group* g);
        void addTransformation(Transformation* t);
        void setShapes(vector<Shape*> sh);
        vector<Group*> getGroups();
        vector<Transformation*> getTrans();
        vector<Shape*> getShapes();
};
#endif
