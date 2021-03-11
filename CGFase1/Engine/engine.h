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

typedef struct point {
	float x;
	float y;
	float z;
}Point;

int line = GL_LINE;
vector<Point> points;
//variáveis de translação
float px = 0.0f, py= 0.0f, pz= 0.0f;
//variável para a rotação dos objetos
float ry = 0.0f;
//variável para escala
float scale = 1.0f; 
float alpha = 0.7f, beta = 0.3f, radius = 10.0f, step = 0.08f;

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