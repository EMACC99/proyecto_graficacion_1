#pragma once
#include <QtOpenGL>
#include <QImage>


#include <string>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

#ifdef _WIN32
    #include <windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

class Texture{

public:
    GLuint LoadTexture(const std::string &filename);
    void FreeTexture(GLuint texture);
};