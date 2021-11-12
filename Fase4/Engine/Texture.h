#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Point.h"
#include "Transformations.h"

using namespace std;

class Texture{

    float diffuse[4];     // default: {0.8, 0.8, 0.8, 1};
    float ambient[4];     // default: {0.2, 0.2, 0.2, 1};
    float specular[4];     // default: {0, 0, 0, 1};
    float emission[4];     // default: {0, 0, 0, 1};

public:
    Texture();
    Texture(Transformations* d, Transformations* a, Transformations* s, Transformations* e);
    void draw();
    float* getDiffuse();
    float* getAmbient();
    float* getSpecular();
    float* getEmission();
};

#endif