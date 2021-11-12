#ifndef   TRANSFORMATIONS_TRANSFORMATIONS_H
#define   TRANSFORMATIONS_TRANSFORMATIONS_H

#include <string>
#include <vector>
#include "point.h"


using namespace std;

class Transformations {
  private :

    string type; //string que indica o tipo da transformação (rotate, translate ou scale)
    float x, y, z; // coordenadas para cada transformação
    float angle; //coordenanda extra para a rotação (assume o valor 0 na translação e scale)
    vector<Point*> controlPoints;
    bool deriv;
    float time;
    vector<Point*> pointsCurve;
    float vetor[4]={1,0,0};

  public :
      Transformations();
      Transformations(string t, float px, float py, float pz, float a);
      Transformations(float ti, vector<Point*> cP, bool de, string t);
        string getType();
        float getAngle();
        float getX();
        float getY();
        float getZ();
        float getTime();
        float* getVetor();
        void normalize(float *a);
        void cross(float *a, float *b, float *res);
        void rotMatrix(float *r, float *x, float *y, float *z);
        void multMatrixVector(float *m, float *v, float *res);
        bool getDeriv();
        vector<Point*> getPointsCurve();
        void getCatmullRomPoint(float t, int *indexes, float *p, float *deriv);
        void getGlobalCatmullRomPoint(float gt, float *p, float *deriv);
     void setCatmullPoints();

};

#endif
