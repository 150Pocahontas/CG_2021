#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include "Light.h"
#include "geoTransforms.h"

using namespace std;

class Scene {
    private:
        vector<Light*> lights;
        geoTransforms *mainGroup;
    public:
    Scene(geoTransforms *obj);
    void addLight(Light *l);
    void applyLights();
    geoTransforms* getMainGroup();
};


#endif //ENGINE_SCENE_H