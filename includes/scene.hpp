#pragma once
// #define GL_GLEXT_PROTOTYPES 1

#include <vector>
#include <string>
#ifdef _WIN32
    #include <windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif
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
    Model(const std::string &filename);
    ~Model() = default;
    void Draw();
private:
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> normals;
    std::vector<GLushort> elements;
    GLuint VAO, VBO, EBO; //vertex array obj, vertex buffer obj, 
    std::vector<float> vertexData;


};
