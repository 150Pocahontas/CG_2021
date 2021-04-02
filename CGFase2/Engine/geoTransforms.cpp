/**
 * @file geoTransform.cpp
 * @brief Ficheiro que contém a API relativa às estruturas de transformações geométricas..
 */
#include "geoTransforms.h"

Point::Point(){
	x = 0; y = 0; z = 0;
}

Point::Point(float px, float py, float pz){
	x = px; y = py; z = pz;
}

float Point::getX(){
	return x;
}

float Point::getY(){
	return y;
}

float Point::getZ(){
	return z;
}

//SHAPE
Shape :: Shape(){}

Shape :: Shape(vector<Point*> p){
    points = p;
}

vector<Point*> Shape :: getPoints() {
    return points;
}

int Shape::getSize(){
	return points.size();
}


 //Ações
Transformation :: Transformation(){
}

Transformation ::Transformation(string t, float a, float xx, float yy, float zz) {
    angle = a;
    type = t;   
    x = xx;
    y = yy;
    z = zz;
}

float Transformation :: getX() {
    return x;
}
void Transformation::setX(float x) {
    Transformation::x = x;
}
//
float Transformation :: getY() {
    return y;
}
void Transformation::setY(float y) {
    Transformation::y = y;
}
//
float Transformation :: getZ() {
    return z;
}
void Transformation::setZ(float z) {
    Transformation::z = z;
}

//
string Transformation :: getType() {
    return type;
}
void Transformation::setType(string type) {
    Transformation::type = type;
}
float Transformation :: getAngle() {
    return angle;
}
void Transformation::setAngle(float angle) {
    Transformation::angle = angle;
}

void Transformation::apply(){
   if(type == "translate"){
       glTranslatef(x,y,z);
   }
   else if(type == "rotate"){
       glRotatef(angle,x,y,z);
   }
   else if(type == "scale") {
       glScalef(x, y, z);
   }
   else if(type == "color"){
       float xx = x/255;
       float yy = y/255;
       float zz = z/255;
       glColor3f(xx,yy,zz);
   }
}



/*Tipo :: Tipo(){}
Tipo :: Tipo(string ti){
	tipo = ti;
}
void Tipo::setTipo(string tipo){
	Tipo :: tipo = tipo;
} 
void Tipo :: apply(int *linha){
	if(tipo == "P"){
    *linha=GL_POINT;

    }
    else if(tipo == "L"){
        *linha=GL_LINE;
    }

    else if(tipo == "F"){
        *linha=GL_FILL;
    }
}*/
//Grupos

Group :: Group(){
}

void Group :: addGroup(Group* g){
    groups.push_back(g);
}

void Group :: addTransformation(Transformation* t){
    trans.push_back(t);
}

void Group :: setShapes(vector<Shape*> sh){
    shapes = sh;
}

vector<Group*> Group :: getGroups(){
    return groups;
}

vector<Transformation*> Group :: getTrans(){
    return trans;
}


vector<Shape*> Group :: getShapes(){
    return shapes;
}