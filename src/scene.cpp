#include "includes/scene.hpp"
#include "includes/utils.hpp"

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


void Scene::draw_teapot(const GLdouble size){
    glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();  
    glTranslatef(0.f, 0.f, 0.f);
    glColor3f(.8f, .2f, .1f);

    glScalef(1.f,1.f,1.f);


    glutSolidTeapot(size);

    glFlush();
}



Model::Model(const char *filename){
    load_obj(filename, this -> vertices, this -> normals, this -> elements);   
    // glEnableVertexAttribArray(attribute_v_coord);
}

void Model::Draw(){
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(attribute_v_coord);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_mesh_vertices);

    glVertexAttribPointer(
        attribute_v_coord,
        4,
        GL_FLOAT,
        GL_FALSE,
        0,
        0
    );
    glEnableVertexAttribArray(attribute_v_normal);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_mesh_normals);
    glVertexAttribPointer(
        attribute_v_normal, // attribute
        3,                  // number of elements per vertex, here (x,y,z)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_mesh_elements);
    int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);  
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

}