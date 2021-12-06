#include "light.h"

void Light::applyLight(GLenum lightId, const Light &light) {
    glLightfv(lightId, GL_POSITION, glm::value_ptr(light.pos));
    glLightfv(lightId, GL_AMBIENT, glm::value_ptr(light.ambient));
    glLightfv(lightId, GL_DIFFUSE, glm::value_ptr(light.diffuse));
    glLightfv(lightId, GL_SPECULAR, glm::value_ptr(light.specular));
    glEnable(lightId);
}
