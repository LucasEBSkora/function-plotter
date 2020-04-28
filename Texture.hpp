#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <string>


class Texture {

  private:
    unsigned int m_rendererID;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_Width, m_Height, mBPP;

  public:
    Texture(const std::string& path);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    int getWidth() const;
    int getHeight() const;

};

#endif