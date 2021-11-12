
#include "Transformations.h"
#include <GL/glut.h>

Transformations :: Transformations(){}

Transformations :: Transformations (string t, float a, float px, float py, float pz){
  type = t;
  angle = a;
  x = px;
  y = py;
  z = pz;
}

Transformations::Transformations(float ti, vector<Point*> cP, bool de, string t){
    time = ti;
    controlPoints = cP;
    setCatmullPoints();
    deriv = de;
    type = t;
}
float* Transformations::getVetor(){
    return vetor;
}

bool Transformations::getDeriv(){
    return deriv;
}

string Transformations::getType(){
    return type;
}

float Transformations::getAngle(){
    return angle;
}

float Transformations::getX(){
    return x;
}

float Transformations::getY(){
    return y;
}

float Transformations::getZ(){
    return z;
}

float Transformations::getTime(){
    return time;
}

vector<Point*> Transformations::getPointsCurve(){
    return pointsCurve;
}
void Transformations::rotMatrix(float *r, float *x, float *y, float *z){
    r[0] = x[0]; r[1] = x[1]; r[2] = x[2]; r[3] = 0;
    r[4] = y[0]; r[5] = y[1]; r[6] = y[2]; r[7] = 0;
    r[8] = z[0]; r[9] = z[1]; r[10] = z[2]; r[11] = 0;
    r[12] = 0; r[13] = 0; r[14] = 0; r[15] = 1;
}

//normalizar vetor
void Transformations::normalize(float *a) {
    float n = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/n;
    a[1] = a[1]/n;
    a[2] = a[2]/n;
}

void Transformations::cross(float *a, float *b, float *res)
{
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void Transformations::multMatrixVector(float *m, float *v, float *res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}

void Transformations::getCatmullRomPoint(float t, int *indexes, float *p, float *deriv) {
    float m[4][4] = { 
    { -0.5f, 1.5f, -1.5f, 0.5f },
    { 1.0f, -2.5f, 2.0f, -0.5f },
    { -0.5f, 0.0f, 0.5f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f } 
    };

    float px[4],py[4],pz[4];
    for(int i = 0; i < 4 ; i++){
        px[i] = controlPoints[indexes[i]]->getX();
        py[i] = controlPoints[indexes[i]]->getY();
        pz[i] = controlPoints[indexes[i]]->getZ();
    }

    // Compute A = M * P
    float a[4][4];
    multMatrixVector(*m, px, a[0]);
    multMatrixVector(*m, py, a[1]);
    multMatrixVector(*m, pz, a[2]);

    // Compute pos = T * A
    float T[4] = { t*t*t, t*t, t, 1};
    multMatrixVector(*a, T, p);

    // Compute deriv = T' * A
    float Tdev[4] = { 3*T[1] , 2*T[2], 1 , 0};
    multMatrixVector(*a, Tdev, deriv);
}

void Transformations::getGlobalCatmullRomPoint(float gt, float *p, float *deriv) {
    int num = controlPoints.size();
    float t = gt * num;
    int index = floor(t);

    t = t - index;

    int indexes[4];
    indexes[0] = (index + num - 1)  % num;
    indexes[1] = (indexes[0]+1)     % num;
    indexes[2] = (indexes[1]+1)     % num;
    indexes[3] = (indexes[2]+1)     % num;

    getCatmullRomPoint(t, indexes, p, deriv);
}

void Transformations::setCatmullPoints(){
    float ponto[4];
    float deriv[4];

    for(float i = 0; i < 1; i+=0.01)
    {
        getGlobalCatmullRomPoint(i, ponto, deriv);
        Point *p = new Point(ponto[0], ponto[1], ponto[2]);
        pointsCurve.push_back(p);
    }
}