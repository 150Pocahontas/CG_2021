#include "Scene.h"

Scene::Scene(geoTransforms *obj) {
    mainGroup = obj;
}

void Scene::addLight(Light *l)
{
    glEnable(GL_LIGHT0 + (GLenum) lights.size());
    lights.push_back(l);
}

void Scene::applyLights()
{
    GLenum number = 0;
    for(Light *l : lights)
        l->apply(number++);
}

geoTransforms* Scene::getMainGroup() {
    return mainGroup;
}