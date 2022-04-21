#include "includes/scene.hpp"
#include "includes/utils.hpp"
#include "OBJ-Loader/Source/OBJ_Loader.h"
float teapot_rotation = 0.f;

void Scene::draw_room(const GLuint *texture){
    
    glPushMatrix();

        glTranslatef(0,0,-1);

        glEnable(GL_TEXTURE_2D);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, *texture);

        glBegin(GL_TRIANGLES);

            glNormal3f(0.f, 1.f, 0.f);

            glTexCoord2f(0.f, 1.f);
            glVertex3f(1.f, 1.f, -1.f);

            glTexCoord2f(0.f, 0.f);
            glVertex3f(-1.f, 1.f, -1.f);

            glTexCoord2f(1.f, 0.f);
            glVertex3f(-1.f, 1.f, 1.f);

            glTexCoord2f(0.f, 1.f);
            glVertex3f(1.f, 1.f, 1.f);

            glBindTexture(GL_TEXTURE_2D, *texture);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glEnd();

    glPopMatrix();
}


void Scene::draw_teapot(const GLdouble size){
    teapot_rotation += rotating_factor;
    glPushMatrix();
        glTranslatef(0.7f, 0.f, 0.f);
        glColor3f(1.f, .6f, 0.f);
        glRotatef(teapot_rotation, 1, 1, 1);
        glutSolidTeapot(size);
    glPopMatrix();
}



Model::Model(const std::string &filename){
    fs::path path = "assets/" + filename;
    path = fs::absolute(path);

    objl::Loader loader;
    loader.LoadFile(path.string());
    objl::Mesh mesh = loader.LoadedMeshes.back();

    for (unsigned long vertex = 0; vertex < mesh.Vertices.size(); ++vertex){
        vertexData.push_back(mesh.Vertices[vertex].Position.X);
        vertexData.push_back(mesh.Vertices[vertex].Position.Y);
        vertexData.push_back(mesh.Vertices[vertex].Position.Z);
    }
    
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);

    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    // glEnableVertexAttribArray(0);
}

void Model::Draw(){
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, 3 * sizeof(GLfloat), vertexData.data() + 3);
    glVertexPointer(3, GL_FLOAT, 3 * sizeof(GLfloat), vertexData.data());
    
    glPushMatrix();
        glScalef(.5f, .5f, .5f);
        glColor3f(1,1,1);
        glRotatef(rotation, 1,1,1);
        glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 3);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    rotation -= rotating_factor;
    
}
