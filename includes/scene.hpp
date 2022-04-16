#pragma once

#ifdef _WIN32
    #include <windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif
#include <vector>
#include <glm/glm.hpp>
class Scene{

public: 
    static void draw_roof(const GLuint *texture, const float &f);
    static void draw_floor(const GLuint *texture, const float &f);
    static void draw_innerwall_1(const GLuint *texture);
    static void draw_innerwall_2(const GLuint *texture);
    static void draw_innerwall_3(const GLuint *texture);
    
    static void draw_teapot(const GLdouble size = 0.5);
};

class Model{
public:
    Model(const char *filename);
    ~Model() = default;
    void Draw();
private:
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> normals;
    std::vector<GLushort> elements;
    GLuint attribute_v_coord, vbo_mesh_vertices, attribute_v_normal, vbo_mesh_normals, ibo_mesh_elements;

};