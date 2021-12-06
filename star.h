#ifndef _STAR_H_
#define _STAR_H_

#include "mesh.h"

const GLfloat center = -15;

struct Star {

    GLfloat year = 0, day = 0, radius;
    GLfloat yearStep, dayStep;

    Material mtl;

    glm::vec3 rotate, spin;
    glm::vec3 offset;

    bool isTorus = false;
    GLdouble inner = 0, outer = 0;

    std::vector<Star> satellite = {};

    Star(GLfloat radius, GLfloat yearStep, GLfloat dayStep, const Material &mtl, glm::vec3 offset,
         glm::vec3 rotate = {0.0, 0.5, 0.5}, glm::vec3 spin = {0.0, 1.0, 0.0})
        : radius(radius), yearStep(yearStep), dayStep(dayStep), mtl(mtl), rotate(rotate),
          spin(spin), offset(offset) {}
    void bindSatellite(std::initializer_list<Star> satellites);
    void bindTorus(GLdouble inner, GLdouble outer);
    void display() const;
    void rotateAndSpin();
    void drawOrbit() const;
};

#endif // _STAR_H_
