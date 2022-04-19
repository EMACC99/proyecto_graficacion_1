#pragma once

#include <vector>
#include <string>
#ifdef _WIN32
    #include <windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else

    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif
#include <glm/glm.hpp>

constexpr float rotating_factor = 0.5f;
class Scene{

public: 
    static void draw_roof(const GLuint *texture, const float &f);
    static void draw_floor(const GLuint *texture, const float &f);
    
    static void draw_teapot(const GLdouble size = 0.5);
};

class Model{
public:
    Model(const std::string &filename);
    ~Model() = default;
    void Draw();
private:
    std::vector<GLfloat> vertexData;
    GLuint VAO, VBO, EBO; //vertex array obj, vertex buffer obj, 
    float rotation = 0 ;
};
