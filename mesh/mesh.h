#ifndef _MESH_H_
#define _MESH_H_

struct Material {
    glm::vec3 ambient = {0.2, 0.2, 0.2}, diffuse = {0.8, 0.8, 0.8}, specular = {0, 0, 0},
              emssion = {0, 0, 0.1};
    float Ns = 50.0, Ni = 1.0; // NOLINT: `Ns` for reflection factor, `Ni` for optical density
    int illumination;
    GLuint mapKa, mapKd, mapKs, mapNs;
    static void applyMaterial(const Material &mtl);
    static void clearMaterial();
};

struct Surface {
    int vertexId[3];
    int textureId[3];
    int normalId[3];
};

struct SurfaceGroup : public std::vector<Surface> {
    Material *pMtl = nullptr;
    bool smooth;
};

class Mesh {
private:
    using ParamMatcher =
        std::unordered_map<std::string_view, auto (*)(Mesh &m, std::istringstream &)->void>;
    const static ParamMatcher obj_param_matcher, mtl_param_matcher;
    std::unordered_map<std::string, Material> mtlPool_;
    static void fileParser_(std::filesystem::path const &path, Mesh &mesh,
                            ParamMatcher const &matcher);

public:
    std::vector<glm::vec3> vertices; // (x, y, z)
    std::vector<glm::vec3> texture;  // (u, v, w)
    std::vector<glm::vec3> normals;  // (x, y, z)
    std::vector<SurfaceGroup> surfaceGroups;

    static Mesh loadMesh(std::filesystem::path const &model); // path to model.{mtl, obj}
    static void renderMesh(const Mesh &mesh, float zoom);
};

#endif // _MESH_H_
