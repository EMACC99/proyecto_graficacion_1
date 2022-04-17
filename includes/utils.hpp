#pragma once
#include <QtOpenGL>
#include <QImage>


#include <string>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

#ifdef _WIN32
    #include <windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif
#include <glm/glm.hpp>
class Texture{

public:
    GLuint LoadTexture(const std::string &filename);
    void FreeTexture(GLuint texture);
};


// void load_obj(const char *filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements);