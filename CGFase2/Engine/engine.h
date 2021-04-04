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

using namespace std;


int line = GL_FILL;
float alpha = 3.14f, beta = 0.0f; //angulos que serão usados para a orientação da camera
float mposX1, mposX2, mposY1, mposY2, mdeltX, mdeltY; //variaveis usadas para calcular posição e velocidade do rato
float movX = 0.0f, movY = 0.0f, movZ = 20.0f; //variáveis que indicam o movimento da camera

int readFile(string filename);
int readXML(string filename);
void keyboard (unsigned char k, int i, int j);
void specialKey(int k, int i, int j);
void wirePlane(float n);
void drawAndColor(void);
void renderScene(void);
void changeSize(int w, int h);
void mouvementguide();


#endif //ENGINE_ENGINE_H
