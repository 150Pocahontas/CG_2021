#ifndef   ENGINE_GEOTRANSFORMS_H
#define   ENGINE_GEOTRANSFORMS_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Transformations.h"

using namespace std;

//struct que guarda coordenadas de um ponto
typedef struct point{

  float x;
  float y;
  float z;

} Point;

//struct que guarda as duas cores de cada planeta
typedef struct color{
  //cor 1
  float r1;
  float g1;
  float b1;
  // cor 2
  float r2;
  float g2;
  float b2;
} Color;

/*
classe que armazena as informações de um grupo/astro

ou seja nesta classe serão guardados:
  -todos os pontos de uma primitiva (lida de um ficheiro .3d) num vetor de "Point"s
  -as duas cores que serão usadas para desenhar a primitiva mencianada em cima (as cores que alternam entre os triangulos)
  -todas as translações, rotações e escalas que serão usadas para transformar o grupo num vetor de "Transformation"
  -todos os astros secundários que também sofrem as transformações mencionadas em cima, mas que possuem transformações, cores, primitivas e filhos próprios num vetor da mesma classe

*/
class geoTransforms{

  private:

      vector<Point> points; //conjunto dos pontos de uma primitiva
      vector<Transformations*> transformations; //conjunto das transformações que serão aplicadas ao grupo
      Color cor; //as duas cores da primitiva
      vector<geoTransforms*> child; //vetor que guarda os grupos filhos deste grupo

  public:
    geoTransforms();
    geoTransforms(vector<Point> p, vector<Transformations*> t, Color c, vector<geoTransforms*> chi);
    vector<Point> getPoints();
    vector<Transformations*> getTransformations();
    vector<geoTransforms*> getChild();
    void addPoint(float x, float y, float z);
    void addTransformations(string t, float px, float py, float pz, float a);
    void addChild(geoTransforms* chi);
    void popPoints();
    void popTransformations();
    float getR1();
    float getG1();
    float getB1();
    float getR2();
    float getG2();
    float getB2();
    void setColor(float red1, float gre1, float blu1, float red2, float gre2, float blu2);

};

#endif
