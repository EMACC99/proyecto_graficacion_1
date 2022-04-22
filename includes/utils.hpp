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
    static GLuint LoadTexture(const std::string &filename);
};