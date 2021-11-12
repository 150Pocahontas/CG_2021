#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H


#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "tinyxml2.h"
#include "point.h"
#include "shape.h"
#include "geoTransforms.h"
#include "Transformations.h"

using namespace std;
using namespace tinyxml2;


//int line = GL_FILL;
int line = GL_LINE;
float alpha = 3.14f, beta = 0.0f; //angulos que serão usados para a orientação da camera
float mposX1, mposX2, mposY1, mposY2, mdeltX, mdeltY; //variaveis usadas para calcular posição e velocidade do rato
float movX = 0.0f, movY = 0.0f, movZ = 20.0f; //variáveis que indicam o movimento da camera

float eTime = 0.0f, cTime = 0.0f;
int frame = 0, timebase = 0;
int stop;

int readFile(string filename);
//void readTranslate(geoTransforms *group, XMLElement *element);
//void readRotate (geoTransforms *group, XMLElement *element);
geoTransforms* readGroup(XMLElement* group);
int readXML(string filename);
void keyboard (unsigned char k, int i, int j);
void specialKey(int k, int i, int j);
void mouseActiveMovEvent(int x, int y);
void mousePassiveMovEvent(int x, int y);
/*void drawOrbits(Transformations *t);
void applyTransformation(Transformations *t);
void drawAndColor(geoTransforms* obj);
void fps();*/
void renderScene(void);
void changeSize(int w, int h);
void mouvementguide();


#endif //ENGINE_ENGINE_H
