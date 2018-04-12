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
    double k;
    double l0;
    Point* m1;
    Point* m2;

    double currentLength();
    double currentForce();
};

struct Point {
    double mass;
    dvec3 position;
    dvec3 velocity;
    dvec3 acceleration;
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
