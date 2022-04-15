#include "includes/scene.hpp"

void Scene::draw_floor(const GLuint *texture, const float &f){
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


void Scene::draw_teapot(const GLuint size){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 
    glTranslatef(0.f, 0.f,-4.5f);
    glColor3f(.8f, .2f, .1f);

    glScalef(1.f,1.f,1.f);


    glutSolidTeapot(size);

    glFlush();
}