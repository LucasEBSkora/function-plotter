#include "Texture.hpp"

#include <GL/glew.h>

#include "GLErrorUtils.hpp"
#include "stb_image.h"

Texture::Texture(const std::string& path) 
  : m_rendererID{0},
    m_filePath{path},
    m_localBuffer{nullptr},
    m_Width{0}, 
    m_Height{0}, 
    mBPP{0} {

    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &mBPP, 4);
    
    GLcall(glGenTextures(1, &m_rendererID));
    GLcall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

    GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLcall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

    unbind();

    if(m_localBuffer)
      stbi_image_free(m_localBuffer);

}

Texture::~Texture() {
  GLcall(glDeleteTextures(1, &m_rendererID));
}

void Texture::bind(unsigned int slot) const {
  GLcall(glActiveTexture(GL_TEXTURE0 + slot));
  GLcall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

}

void Texture::unbind() const {
  GLcall(glBindTexture(GL_TEXTURE_2D, 0));
}

int Texture::getWidth() const {
  return m_Width;
}

int Texture::getHeight() const {
  return m_Height;
}