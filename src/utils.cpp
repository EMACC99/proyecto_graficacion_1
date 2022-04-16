#include "includes/utils.hpp"


GLuint Texture::LoadTexture(const std::string &filename){
    fs::path path = "assets/" + filename;
    path = fs::absolute(path);

    // QOpenGLTexture *m_texture = new QOpenGLTexture(QImage(path.c_str()));
    std::unique_ptr<QOpenGLTexture> m_texture( new QOpenGLTexture(QImage(path.c_str())));
    if (!m_texture -> isCreated()){
        std::cerr << "Failed to create texture" << std::endl;
        exit(EXIT_FAILURE);
    }


    m_texture -> setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    m_texture -> setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

    m_texture -> setMinificationFilter(QOpenGLTexture::Linear);
    m_texture -> setMagnificationFilter(QOpenGLTexture::Linear);

    m_texture -> bind();

    GLuint texture = m_texture -> textureId();

    return texture;

}

void load_obj(const char *filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements){
    std::ifstream in(filename, std::ios::in);
    if (!in){
        std::cerr << "Cannot open" << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while(getline(in, line)){
        if (line.substr(0,2) == "v "){
            std::istringstream s (line.substr(2));
            glm::vec4 v;
            s >> v.x;
            s >> v.y;
            s >> v.z;
            v.w = 1.f;
            vertices.emplace_back(v);
        }
        else if(line.substr(0,2) == "f " ){
            std::istringstream s(line.substr(2));
            GLushort a,b,c;
            s >> a;
            s >> b;
            s >> c;
            --a;
            --b;
            --c;
            elements.emplace_back(a);
            elements.emplace_back(b);
            elements.emplace_back(c);
        }
    }
    normals.resize(vertices.size(), glm::vec3(0.f,0.f,0.f));
    for (int i = 0; i < elements.size(); i+= 3){
        GLushort ia = elements[i];
        GLushort ib = elements[i + 1];
        GLushort ic = elements[i + 2];
        glm::vec3 normal = glm::normalize(glm::cross(
            glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
            glm::vec3(vertices[ic]) - glm::vec3(vertices[ia]))
        );
        normals[ia] = normals[ib] = normals[ic] = normal;
        
    }
}
