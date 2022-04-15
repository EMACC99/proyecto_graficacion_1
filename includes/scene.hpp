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
class Scene{

public: 
    static void draw_roof(const GLuint *texture, const float &f);
    static void draw_floor(const GLuint *texture, const float &f);
    static void draw_innerwall_1(const GLuint *texture);
    static void draw_innerwall_2(const GLuint *texture);
    static void draw_innerwall_3(const GLuint *texture);
    
    static void draw_teapot(const GLuint size = 1);
};
