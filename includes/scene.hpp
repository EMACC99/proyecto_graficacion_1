#pragma once

#ifdef _WIN32
    #include <windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif
class Cuarto{

public: 
    void draw_roof(const GLuint *texture, const float &f);
    void draw_floor(const GLuint *texture, const float &f);
    void draw_innerwall_1(const GLuint *texture);
    void draw_innerwall_2(const GLuint *texture);
    void draw_innerwall_3(const GLuint *texture);
    
};