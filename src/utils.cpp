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