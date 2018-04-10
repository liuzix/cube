//
// Created by Zixiong Liu on 4/9/18.
//

#ifndef CUBE_CUBE_H
#define CUBE_CUBE_H

#include <vector>
#include <list>
#include "glcommon.h"

using namespace std;
using namespace glm;

struct Point;

struct Spring {
    float k;
    float l0;
    Point* m1;
    Point* m2;

    float currentLength();
    float currentForce();
};

struct Point {
    float mass;
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    vector<Spring*> springs;
};


class Cube {
private:
    vector<Point> points;
    list<Spring> springs;
    static vector<GLint> triangularize();
public:
    Cube();
    void update();

    friend class Drawer;
};


#endif //CUBE_CUBE_H
