#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "geoTransforms.h"

using namespace std;

int line = GL_LINE;
Group *scene;
vector<Point*> orbits;
void readRotate (Group* group, XMLElement* element);
void readTranslate (Group *group, XMLElement *element, vector<Point*> *orbits, int d);
void readScale (Group *group, XMLElement *element);
void readColour (Group *group, XMLElement *element);
void readModels (Group *group, XMLElement *element);
void readGroup (Group *group, XMLElement *gElement, vector<Point*> *orbits, int d);
void drawScene(Group* scene);

int readFile(string filename);
int readXML(string filename);
//void wirePlane(float n);
void renderScene(void);
void keyboard (unsigned char k, int i, int j);
void specialKey (int k, int i, int j);
void changeSize(int w, int h);
void mouvementguide();


#endif //ENGINE_ENGINE_H
