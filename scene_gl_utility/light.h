#ifndef _LIGHT_H_
#define _LIGHT_H_

struct Light {
    glm::vec4 pos, ambient, diffuse, specular;

    static void applyLight(GLenum lightId, const Light &light);
};

#endif // _LIGHT_H_
