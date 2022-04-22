#include "includes/utils.hpp"
#include "includes/gl_debug.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

GLuint Texture::LoadTexture(const std::string &filename){
    fs::path path = "assets/" + filename;
    path = fs::absolute(path);

    GLuint texture;
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data){
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return texture;
    }
    else{
        std::cerr << "Failed to load texture" << std::endl;
        stbi_image_free(data);
        exit(EXIT_FAILURE);
    }
}
