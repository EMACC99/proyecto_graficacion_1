#include "includes/scene.hpp"
#include "includes/utils.hpp"
#include "OBJ-Loader/Source/OBJ_Loader.h"

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

    glPopMatrix();
}


void Scene::draw_teapot(const GLdouble size){
    glTranslatef(0.f, 0.f, 0.f);
    glRotatef(.5f, 1, 1, 1);
    glColor3f(1.f, .6f, 0.f);
//    glScalef(1.f,1.f,1.f);
    glutSolidTeapot(size);
}



Model::Model(const std::string &filename){
    fs::path path = "assets/" + filename;
    path = fs::absolute(path);
    // load_obj(path.c_str(), this -> vertices, this -> normals, this -> elements);
    objl::Loader loader;
    loader.LoadFile(path.string());
    objl::Mesh mesh = loader.LoadedMeshes.back();

    for (int vertex = 0; vertex < mesh.Vertices.size(); ++vertex){
        vertexData.push_back(mesh.Vertices[vertex].Position.X);
        vertexData.push_back(mesh.Vertices[vertex].Position.Y);
        vertexData.push_back(mesh.Vertices[vertex].Position.Z);
    }
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
}

void Model::Draw(){
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr); //this causes a segfault, need to ask
}
// void Model::Draw(){
//     // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);
    
//     glEnableVertexAttribArray(attribute_v_coord);

//     glBindBuffer(GL_ARRAY_BUFFER, vbo_mesh_vertices);

//     glVertexAttribPointer(
//         attribute_v_coord,
//         4,
//         GL_FLOAT,
//         GL_FALSE,
//         0,
//         0
//     );
//     glEnableVertexAttribArray(attribute_v_normal);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo_mesh_normals);
//     glVertexAttribPointer(
//         attribute_v_normal, // attribute
//         3,                  // number of elements per vertex, here (x,y,z)
//         GL_FLOAT,           // the type of each element
//         GL_FALSE,           // take our values as-is
//         0,                  // no extra data between each position
//         0                   // offset of first element
//     );

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_mesh_elements);
//     int size;
//     glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);  
//     glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

// }
