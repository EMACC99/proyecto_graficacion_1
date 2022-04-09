#include "includes/scene.hpp"

void Cuarto::draw_floor(const GLuint *texture, const float &f){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glPushMatrix();


    for (float a = -10.f; a <= 170.f; a+= 10.f){
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(0.0 + a, 0.0, 10.0);
            glTexCoord2f(0.0, f);
            glVertex3f(0.0 + a, 0.0, 0.0);
            glTexCoord2f(f, f);
            glVertex3f(10.0 + a, 0.0, 0.0);
            glTexCoord2f(f, 0.0);
            glVertex3f(10.0 + a, 0.0, 10.0);
        glEnd();

    }
}